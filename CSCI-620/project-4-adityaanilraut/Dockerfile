# Stage 1: Build React frontend
FROM node:18-alpine AS frontend-builder

WORKDIR /app/frontend

# Copy package files
COPY frontend/package*.json ./

# Install dependencies
RUN npm install

# Copy frontend source
COPY frontend/ ./

# Build React app
RUN npm run build

# Stage 2: Python/Django backend
FROM python:3.12.6

WORKDIR /app

# Copy requirements and install Python dependencies
COPY requirements.txt ./
RUN pip3 install --no-cache-dir -r requirements.txt

# Copy Django project
COPY chess_game/ ./chess_game/
COPY chess_project/ ./chess_project/
COPY manage.py ./
COPY docker_run_server.sh ./

# Copy React build from frontend stage
COPY --from=frontend-builder /app/frontend/build ./frontend/build

# Create static directory and copy any existing static files
COPY static/ ./static/

# Make the run script executable
RUN chmod +x docker_run_server.sh

# Expose port
EXPOSE 80

# Run the application
ENTRYPOINT ["./docker_run_server.sh"]
