// WebSocket service for real-time game and lobby updates

class WebSocketService {
  constructor() {
    this.ws = null;
    this.reconnectAttempts = 0;
    this.maxReconnectAttempts = 5;
    this.reconnectDelay = 3000;
    this.listeners = new Map();
    this.isConnecting = false;
    this.shouldReconnect = true;
  }

  // Get WebSocket URL based on current location
  getWsUrl(path) {
    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    
    // In development, React runs on port 3000 but Django runs on port 8000
    // Check if we're on the React dev server and redirect to Django backend
    let host = window.location.host;
    if (host.includes('localhost:3000') || host.includes('127.0.0.1:3000')) {
      host = host.replace(':3000', ':8000');
    }
    
    return `${protocol}//${host}/ws${path}`;
  }

  // Connect to WebSocket
  connect(path, onMessage, onOpen, onClose, onError) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      return;
    }

    if (this.isConnecting) {
      return;
    }

    this.isConnecting = true;
    this.shouldReconnect = true;
    const url = this.getWsUrl(path);

    try {
      this.ws = new WebSocket(url);

      this.ws.onopen = () => {
        console.log('WebSocket connected:', path);
        this.isConnecting = false;
        this.reconnectAttempts = 0;
        if (onOpen) onOpen();
      };

      this.ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (onMessage) onMessage(data);
        } catch (e) {
          console.error('Failed to parse WebSocket message:', e);
        }
      };

      this.ws.onclose = (event) => {
        console.log('WebSocket disconnected:', path, event.code);
        this.isConnecting = false;
        if (onClose) onClose(event);
        
        // Attempt to reconnect
        if (this.shouldReconnect && this.reconnectAttempts < this.maxReconnectAttempts) {
          this.reconnectAttempts++;
          console.log(`Reconnecting... Attempt ${this.reconnectAttempts}`);
          setTimeout(() => {
            this.connect(path, onMessage, onOpen, onClose, onError);
          }, this.reconnectDelay);
        }
      };

      this.ws.onerror = (error) => {
        console.error('WebSocket error:', error);
        this.isConnecting = false;
        if (onError) onError(error);
      };
    } catch (error) {
      console.error('Failed to create WebSocket:', error);
      this.isConnecting = false;
      if (onError) onError(error);
    }
  }

  // Send message through WebSocket
  send(data) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      this.ws.send(JSON.stringify(data));
      return true;
    }
    console.warn('WebSocket is not connected');
    return false;
  }

  // Disconnect WebSocket
  disconnect() {
    this.shouldReconnect = false;
    if (this.ws) {
      this.ws.close();
      this.ws = null;
    }
  }

  // Check if connected
  isConnected() {
    return this.ws && this.ws.readyState === WebSocket.OPEN;
  }
}

// Game WebSocket class
export class GameWebSocket {
  constructor(gameId) {
    this.gameId = gameId;
    this.service = new WebSocketService();
    this.onGameStateUpdate = null;
    this.onError = null;
  }

  connect(onGameState, onError) {
    this.onGameStateUpdate = onGameState;
    this.onError = onError;

    this.service.connect(
      `/game/${this.gameId}/`,
      (data) => this.handleMessage(data),
      () => console.log('Game WebSocket connected'),
      () => console.log('Game WebSocket disconnected'),
      // Don't show toast for WebSocket connection errors - they fire during normal navigation
      () => console.log('Game WebSocket error (ignored)')
    );
  }

  handleMessage(data) {
    if (data.type === 'game_state' && this.onGameStateUpdate) {
      this.onGameStateUpdate(data.data);
    } else if (data.type === 'error' && this.onError) {
      this.onError(new Error(data.message));
    }
  }

  sendMove(fromSquare, toSquare) {
    return this.service.send({
      type: 'new_move',
      from_square: fromSquare,
      to_square: toSquare,
    });
  }

  sendResign() {
    return this.service.send({
      type: 'game_action',
      action: 'resign',
    });
  }

  disconnect() {
    this.service.disconnect();
  }
}

// Lobby WebSocket class
export class LobbyWebSocket {
  constructor() {
    this.service = new WebSocketService();
    this.onLobbyUpdate = null;
    this.onNewGame = null;
    this.onChallengeSent = null;
    this.onError = null;
  }

  connect(callbacks) {
    this.onLobbyUpdate = callbacks.onLobbyUpdate;
    this.onNewGame = callbacks.onNewGame;
    this.onChallengeSent = callbacks.onChallengeSent;
    this.onError = callbacks.onError;

    this.service.connect(
      '/lobby/',
      (data) => this.handleMessage(data),
      () => console.log('Lobby WebSocket connected'),
      () => console.log('Lobby WebSocket disconnected'),
      // Don't show toast for WebSocket connection errors - they fire during normal navigation
      () => console.log('Lobby WebSocket error (ignored)')
    );
  }

  handleMessage(data) {
    switch (data.type) {
      case 'lobby_data':
        if (this.onLobbyUpdate) {
          this.onLobbyUpdate(data.data);
        }
        break;
      case 'new_game':
        if (this.onNewGame) {
          this.onNewGame(data.game_id);
        }
        break;
      case 'challenge_sent':
        if (this.onChallengeSent) {
          this.onChallengeSent(data.message);
        }
        break;
      case 'challenge_response':
        if (this.onChallengeSent) {
          this.onChallengeSent(data.message);
        }
        break;
      case 'error':
        if (this.onError) {
          this.onError(new Error(data.message));
        }
        break;
      default:
        console.log('Unknown message type:', data.type);
    }
  }

  sendChallenge(playerId) {
    return this.service.send({
      type: 'send_challenge',
      opponent_id: playerId,
    });
  }

  respondChallenge(challengeId, response) {
    return this.service.send({
      type: 'respond_challenge',
      challenge_id: challengeId,
      response: response, // 'accept' or 'decline'
    });
  }

  requestUpdate() {
    return this.service.send({
      type: 'request_lobby_update',
    });
  }

  disconnect() {
    this.service.disconnect();
  }
}

export default WebSocketService;

