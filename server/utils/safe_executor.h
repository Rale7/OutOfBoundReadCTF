#ifndef SAFE_EXECUTOR_H
#define SAFE_EXECUTOR_H

#include <functional>
#include <string>

#include "../utils/http_request.h"

class SafeExecutor {
 public:
  // Execute a handler function safely, catching crashes and returning 500 on
  // failure
  static std::string executeHandler(std::function<std::string()> handler);

  // Generate a 500 Internal Server Error response
  static std::string generate500Response(
      const std::string& error_message = "Internal Server Error");

 private:
  static void setupSignalHandlers();
  static void signalHandler(int signal);
  static bool crash_occurred;
};

#endif