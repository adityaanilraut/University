#!/bin/sh

# Run database migrations
python manage.py migrate --noinput

# Collect static files
python manage.py collectstatic --noinput

# Start Daphne server (supports both HTTP and WebSocket)
daphne -b 0.0.0.0 -p 80 chess_project.asgi:application
