// API service for making REST API calls to Django backend

const API_BASE = '/api';

// Get CSRF token from cookie
function getCsrfToken() {
  const name = 'csrftoken';
  let cookieValue = null;
  if (document.cookie && document.cookie !== '') {
    const cookies = document.cookie.split(';');
    for (let i = 0; i < cookies.length; i++) {
      const cookie = cookies[i].trim();
      if (cookie.substring(0, name.length + 1) === (name + '=')) {
        cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
        break;
      }
    }
  }
  return cookieValue;
}

// Base fetch function with credentials and CSRF token
async function apiFetch(endpoint, options = {}) {
  const url = `${API_BASE}${endpoint}`;
  
  const config = {
    ...options,
    credentials: 'include',
    headers: {
      'Content-Type': 'application/json',
      'X-CSRFToken': getCsrfToken(),
      ...options.headers,
    },
  };
  
  const response = await fetch(url, config);
  
  // Handle non-JSON responses
  const contentType = response.headers.get('content-type');
  if (!contentType || !contentType.includes('application/json')) {
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    return { success: true };
  }
  
  const data = await response.json();
  
  if (!response.ok) {
    throw new Error(data.error || data.detail || 'An error occurred');
  }
  
  return data;
}

// Auth API calls
export const authApi = {
  // Get CSRF token
  getCsrf: () => apiFetch('/auth/csrf/'),
  
  // Get current user
  getCurrentUser: () => apiFetch('/auth/user/'),
  
  // Login
  login: (username, password) => apiFetch('/auth/login/', {
    method: 'POST',
    body: JSON.stringify({ username, password }),
  }),
  
  // Register
  register: (username, password, passwordConfirm) => apiFetch('/auth/register/', {
    method: 'POST',
    body: JSON.stringify({ 
      username, 
      password, 
      password_confirm: passwordConfirm 
    }),
  }),
  
  // Logout
  logout: () => apiFetch('/auth/logout/', {
    method: 'POST',
  }),
};

// Game API calls
export const gameApi = {
  // Get lobby data
  getLobby: () => apiFetch('/lobby/'),
  
  // Get game details
  getGame: (gameId) => apiFetch(`/games/${gameId}/`),
  
  // Get game history
  getHistory: () => apiFetch('/games/history/'),
};

// Content API calls
export const contentApi = {
  // Get rules
  getRules: () => apiFetch('/rules/'),
  
  // Get about
  getAbout: () => apiFetch('/about/'),
};

export default {
  auth: authApi,
  game: gameApi,
  content: contentApi,
};

