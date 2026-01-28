#include "handlers.h"

#include <iostream>
#include <memory>
#include <unordered_map>

#include "../services/level10.h"
#include "../services/level4.h"
#include "../services/level5.h"
#include "../services/level6.h"
#include "../services/level7.h"
#include "../services/level8.h"
#include "../services/level9.h"
#include "../services/login.h"
#include "../utils/auth_parser.h"

static std::unordered_map<std::string, std::unique_ptr<Level1Service>>&
getServiceMap() {
  static std::unordered_map<std::string, std::unique_ptr<Level1Service>>
      serviceMap;
  static bool initialized = false;

  if (!initialized) {
    serviceMap["user1"] = std::make_unique<Level1Service>();
    serviceMap["user2"] = std::make_unique<Level2Service>();
    serviceMap["user3"] = std::make_unique<Level3Service>();
    serviceMap["user4"] = std::make_unique<Level4Service>();
    serviceMap["user5"] = std::make_unique<Level5Service>();
    serviceMap["user6"] = std::make_unique<Level6Service>();
    serviceMap["user7"] = std::make_unique<Level7Service>();
    serviceMap["user8"] = std::make_unique<Level8Service>();
    serviceMap["user9"] = std::make_unique<Level9Service>();
    serviceMap["user10"] = std::make_unique<Level10Service>();
    initialized = true;
  }

  return serviceMap;
}

std::string errorResponse(const std::string& message) {
  std::string error_body = "{\"error\":\"" + message + "\"}";
  std::string response =
      "HTTP/1.1 401 Unauthorized\r\n"
      "Content-Type: application/json\r\n"
      "Access-Control-Allow-Origin: *\r\n"
      "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      "Access-Control-Allow-Headers: Content-Type, Authorization\r\n"
      "WWW-Authenticate: Basic realm=\"API\"\r\n" +
      std::string("Content-Length: ") + std::to_string(error_body.size()) +
      "\r\n"
      "\r\n" +
      error_body;
  return response;
}

std::string okayJsonResponse(const std::string& body) {
  std::string response =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/json\r\n"
      "Access-Control-Allow-Origin: *\r\n"
      "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      "Access-Control-Allow-Headers: Content-Type, Authorization\r\n" +
      std::string("Content-Length: ") + std::to_string(body.size()) +
      "\r\n"
      "\r\n" +
      body;
  return response;
}

std::string okayTextResponse(const std::string& body) {
  std::string response =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/plain\r\n"
      "Access-Control-Allow-Origin: *\r\n"
      "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      "Access-Control-Allow-Headers: Content-Type, Authorization\r\n" +
      std::string("Content-Length: ") + std::to_string(body.size()) +
      "\r\n"
      "\r\n" +
      body;
  return response;
}

std::string Handlers::handleHome(const HttpRequest& /* request */) {
  std::string response =
      okayJsonResponse("{\"message\":\"Welcome to the API Server!\"}");
  return response;
}

std::string Handlers::handleAbout(const HttpRequest& /* request */) {
  std::string response =
      okayJsonResponse("{\"message\":\"About page content\"}");
  return response;
}

std::string Handlers::handleApi(const HttpRequest& /* request */) {
  std::string response = okayJsonResponse("{\"status\":\"ok\"}");
  return response;
}

std::string Handlers::login(const HttpRequest& request) {
  // Extract username and password from request body (JSON format)
  std::string username = "";
  std::string password = "";

  const std::string& body = request.body;

  // Simple JSON parsing for {"username":"value","password":"value"}
  size_t usernamePos = body.find("\"username\"");
  if (usernamePos != std::string::npos) {
    size_t valueStart = body.find("\"", usernamePos + 10);
    if (valueStart != std::string::npos) {
      valueStart++;  // Skip opening quote
      size_t valueEnd = body.find("\"", valueStart);
      if (valueEnd != std::string::npos) {
        username = body.substr(valueStart, valueEnd - valueStart);
      }
    }
  }

  size_t passwordPos = body.find("\"password\"");
  if (passwordPos != std::string::npos) {
    size_t valueStart = body.find("\"", passwordPos + 10);
    if (valueStart != std::string::npos) {
      valueStart++;  // Skip opening quote
      size_t valueEnd = body.find("\"", valueStart);
      if (valueEnd != std::string::npos) {
        password = body.substr(valueStart, valueEnd - valueStart);
      }
    }
  }

  int loginResult = login::login_service(username, password);
  std::string response_body;
  if (loginResult == 1) {
    response_body = "{\"login\":\"success\"}";
  } else {
    response_body = "{\"login\":\"failure\"}";
  }

  std::string response = okayJsonResponse(response_body);
  return response;
}

std::string Handlers::getAccounts(const HttpRequest& request) {
  // Parse Basic Authentication
  AuthCredentials creds = AuthParser::parseBasicAuth(request);

  if (!creds.valid) {
    return errorResponse("Invalid or missing authorization");
  }
  std::string response_body = getServiceMap().at(creds.username)->getAccounts();
  std::string response = okayJsonResponse(response_body);
  return response;
}

std::string Handlers::getSingleAccount(const HttpRequest& request) {
  int index = request.params.at("index").empty()
                  ? 0
                  : std::stoi(request.params.at("index"));

  AuthCredentials creds = AuthParser::parseBasicAuth(request);
  if (!creds.valid) {
    return errorResponse("Invalid or missing authorization");
  }
  std::string response_body =
      getServiceMap().at(creds.username)->getAccount(index);
  std::string response = okayJsonResponse(response_body);
  return response;
}

std::string Handlers::changeAccount(const HttpRequest& request) {
  AuthCredentials creds = AuthParser::parseBasicAuth(request);
  if (!creds.valid) {
    return errorResponse("Invalid or missing authorization");
  }

  // Expecting JSON body with account details
  std::string body = request.body;

  Account1 account;
  account.deserialize(body);

  getServiceMap().at(creds.username)->changeAccount(account);

  std::string response = okayJsonResponse("{\"status\":\"account changed\"}");
  return response;
}

std::string Handlers::exportFromFile(const HttpRequest& request) {
  AuthCredentials creds = AuthParser::parseBasicAuth(request);
  if (!creds.valid) {
    return errorResponse("Invalid or missing authorization");
  }

  // Expecting JSON body with size detail
  std::string body = request.body;

  size_t size = request.params.at("size").empty()
                    ? 0
                    : std::stoi(request.params.at("size"));

  std::string response_body =
      getServiceMap().at(creds.username)->exportFromFile(size);
  std::string response = okayTextResponse(response_body);
  return response;
}

std::string Handlers::importToFile(const HttpRequest& request) {
  AuthCredentials creds = AuthParser::parseBasicAuth(request);
  if (!creds.valid) {
    return errorResponse("Invalid or missing authorization");
  }

  // Expecting JSON body with data detail
  std::string body = request.body;

  // For simplicity, we assume the entire body is the data to import
  const char* data = body.c_str();
  size_t size = body.size();

  getServiceMap().at(creds.username)->importToFile(data, size);

  std::string response =
      okayJsonResponse("{\"status\":\"imported successfully\"}");
  return response;
}

std::string Handlers::handleOptions(const HttpRequest& /* request */) {
  std::string response =
      "HTTP/1.1 204 No Content\r\n"
      "Access-Control-Allow-Origin: *\r\n"
      "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      "Access-Control-Allow-Headers: Content-Type, Authorization\r\n"
      "Access-Control-Max-Age: 3600\r\n"
      "\r\n";
  return response;
}

std::string Handlers::handleBadRequest(const std::string& message) {
  std::string response_body = "{\"request\":\"" + message + "\"}";
  std::string response =
      "HTTP/1.1 400 Bad Request\r\n"
      "Content-Type: application/json\r\n"
      "Access-Control-Allow-Origin: *\r\n"
      "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
      "Access-Control-Allow-Headers: Content-Type, Authorization\r\n" +
      std::string("Content-Length: ") + std::to_string(response_body.size()) +
      "\r\n"
      "\r\n" +
      response_body;
  return response;
}
