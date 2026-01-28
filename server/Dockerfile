# Use Ubuntu as base image for C++ development
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
  g++ \
  make \
  && rm -rf /var/lib/apt/lists/*

# Create working directory
WORKDIR /app

# Copy source code and build files
COPY . .

# Create output directories and build the application
RUN make all

# Expose port 8080
EXPOSE 8080

# Run the application from the bin directory
CMD ["./out/bin/web-server"]