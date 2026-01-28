# Use Node.js official image
FROM node:18-alpine

# Set working directory
WORKDIR /app

# Copy package.json and package-lock.json (if available)
COPY package*.json ./

# Install dependencies
RUN npm install

# Install Angular CLI globally
RUN npm install -g @angular/cli

# Copy the rest of the application
COPY . .

# Expose port 4200
EXPOSE 4200

# Start the Angular development server
CMD ["ng", "serve", "--host", "0.0.0.0", "--port", "4200"]