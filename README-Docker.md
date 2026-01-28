# Dockerized Application

This application consists of a C++ server and an Angular client, both containerized with Docker.

## Prerequisites

- Docker
- Docker Compose

## Services

- **Server**: C++ HTTP server running on port 8080
- **Client**: Angular application running on port 4200

## Getting Started

### 1. Build and Run with Docker Compose

```bash
# Build and start all services
docker-compose up --build

# Or run in detached mode (background)
docker-compose up --build -d
```

### 2. Access the Application

- **Angular Client**: http://localhost:4200
- **C++ Server**: http://localhost:8080

### 3. Development Mode

The client service includes volume mounting for hot-reload development. When you make changes to the Angular source code, the changes will be reflected automatically.

### 4. Stop the Application

```bash
# Stop all services
docker-compose down

# Stop and remove volumes
docker-compose down -v
```

## Individual Service Management

### Build Individual Services

```bash
# Build only the server
docker-compose build server

# Build only the client
docker-compose build client
```

### Run Individual Services

```bash
# Run only the server
docker-compose up server

# Run only the client
docker-compose up client
```

## Production Deployment

For production deployment, you may want to:

1. Remove the volume mounting in the client service
2. Build the Angular application for production
3. Serve the built files with a production web server

### Production Client Dockerfile

Create a separate `Dockerfile.prod` for the client:

```dockerfile
# Build stage
FROM node:18-alpine as build

WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
RUN npm run build

# Production stage
FROM nginx:alpine
COPY --from=build /app/dist/client /usr/share/nginx/html
COPY nginx.conf /etc/nginx/nginx.conf
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

## Troubleshooting

### Port Conflicts

If you have services running on ports 4200 or 8080, you can modify the port mappings in `docker-compose.yml`:

```yaml
ports:
  - "3000:4200"  # Map to port 3000 instead of 4200
  - "8081:8080"  # Map to port 8081 instead of 8080
```

### Container Logs

```bash
# View logs for all services
docker-compose logs

# View logs for specific service
docker-compose logs server
docker-compose logs client

# Follow logs in real-time
docker-compose logs -f
```

### Rebuild After Changes

```bash
# Rebuild specific service
docker-compose build --no-cache server

# Rebuild all services
docker-compose build --no-cache
```

## Network Configuration

Both services are connected via a custom Docker network (`app-network`). The client can communicate with the server using the service name `server` as the hostname.

Example: If the Angular client needs to make HTTP requests to the server, use:
```typescript
const serverUrl = 'http://server:8080/api/endpoint';
```

## File Structure

```
/
├── client/
│   ├── Dockerfile
│   ├── .dockerignore
│   └── [Angular application files]
├── server/
│   ├── Dockerfile
│   ├── .dockerignore
│   └── [C++ application files]
└── docker-compose.yml
```