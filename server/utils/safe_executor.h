#ifndef SAFE_EXECUTOR_H
#define SAFE_EXECUTOR_H

#include <functional>
#include <string>

#include "../utils/http_request.h"

class SafeExecutor {
 public:
  static std::string executeHandler(std::function<std::string()> handler);

  static std::string generate500Response(
      const std::string& error_message = "Internal Server Error");

 private:
  static void setupSignalHandlers();
  static void signalHandler(int signal);
  static bool crash_occurred;
};

#endif