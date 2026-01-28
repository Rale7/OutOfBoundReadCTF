#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <memory>
#include <string>

#include "controllers/handlers.h"
#include "router/router.h"
#include "utils/http_parser.h"

void init_files() {
  char buffer[1024];
  FILE *level7, *level8, *level9;
  level7 = fopen("level7_export.json", "r");
  level8 = fopen("level8_export.json", "w");
  level9 = fopen("level9_export.json", "w");

  if (level7 && level8) {
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), level7);
    fwrite(buffer, 1, bytesRead - 31, level8);
    fwrite(buffer, 1, bytesRead - 31, level9);
  }

  fclose(level7);
  fclose(level8);
  fclose(level9);
}

int main() {
  init_files();

  int server_fd, server_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // Inicijalizacija routera
  Router router;
  router.addRoute("/", HttpRequestMethod::GET, Handlers::handleHome);
  router.addRoute("/", HttpRequestMethod::OPTIONS, Handlers::handleOptions);
  router.addRoute("/about", HttpRequestMethod::GET, Handlers::handleAbout);
  router.addRoute("/about", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/api", HttpRequestMethod::GET, Handlers::handleApi);
  router.addRoute("/api", HttpRequestMethod::OPTIONS, Handlers::handleOptions);
  router.addRoute("/getAccounts", HttpRequestMethod::GET,
                  Handlers::getAccounts);
  router.addRoute("/getAccounts", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/login", HttpRequestMethod::POST, Handlers::login);
  router.addRoute("/login", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/getAccountByIndex/:index", HttpRequestMethod::GET,
                  Handlers::getSingleAccount);
  router.addRoute("/getAccountByIndex/:index", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/changeAccount", HttpRequestMethod::POST,
                  Handlers::changeAccount);
  router.addRoute("/changeAccount", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/exportFromFile/:size", HttpRequestMethod::GET,
                  Handlers::exportFromFile);
  router.addRoute("/exportFromFile/:size", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);
  router.addRoute("/importToFile", HttpRequestMethod::POST,
                  Handlers::importToFile);
  router.addRoute("/importToFile", HttpRequestMethod::OPTIONS,
                  Handlers::handleOptions);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Socket failed");
    return -1;
  }

  // Omogući ponovno korišćenje adrese
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
      0) {
    perror("setsockopt failed");
    return -1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);
  int status = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
  if (status < 0) {
    perror("Bind failed");
    return -1;
  }

  status = listen(server_fd, 3);
  if (status < 0) {
    perror("Listen failed");
    return -1;
  }
  printf("Server listening on port 8080\n");

  while (1) {
    server_socket =
        accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    std::string buffer;
    char chunk[1024] = "  p2H6m7KvxAAMf5XbRWV1YffjgOMEFS";
    char secret[1024] = "4H91sgkzIoF66ftI6p3vrhED9sbRN9";
    ssize_t bytes_read = read(server_socket, chunk, sizeof(chunk));
    buffer += std::string(chunk);

    printf("=== Primljen zahtev ===\n%s\n", buffer.c_str());

    std::string response;
    try {
      HttpRequest request = HttpParser::parse(buffer);
      response = router.handleRequest(request);
    } catch (HttpParseException ex) {
      printf("Parse error: %s\n", ex.what());
      response = Handlers::handleBadRequest(buffer);
    }
    // Ruting i obrada zahteva

    send(server_socket, response.c_str(), response.length(), 0);
    close(server_socket);
  }

  return 0;
}