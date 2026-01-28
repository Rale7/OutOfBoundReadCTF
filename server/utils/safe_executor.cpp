#include "safe_executor.h"

#include <csetjmp>
#include <csignal>
#include <iostream>

bool SafeExecutor::crash_occurred = false;
static jmp_buf jump_buffer;
static bool signal_handler_active = false;

void SafeExecutor::signalHandler(int signal) {
  if (!signal_handler_active) return;

  std::cout << "CTF Challenge triggered signal: " << signal << std::endl;
  crash_occurred = true;
  longjmp(jump_buffer, signal);
}

void SafeExecutor::setupSignalHandlers() {
  signal(SIGSEGV, signalHandler);
  signal(SIGBUS, signalHandler);
  signal(SIGFPE, signalHandler);
  signal(SIGABRT, signalHandler);
}

std::string SafeExecutor::executeHandler(std::function<std::string()> handler) {
  try {
    setupSignalHandlers();
    crash_occurred = false;
    signal_handler_active = true;

    int signal_received = setjmp(jump_buffer);
    if (signal_received != 0) {
      signal_handler_active = false;
      std::cout << "Handler crashed with signal: " << signal_received
                << std::endl;
      return generate500Response(
          "Memory access violation in CTF challenge (signal " +
          std::to_string(signal_received) + ")");
    }

    std::string result = handler();

    signal_handler_active = false;
    return result;

  } catch (const std::exception& e) {
    signal_handler_active = false;
    std::cout << "Handler threw exception: " << e.what() << std::endl;
    return generate500Response("Exception in CTF challenge: " +
                               std::string(e.what()));
  }
}

std::string SafeExecutor::generate500Response(
    const std::string& error_message) {
  std::string body = "{\"error\":\"" + error_message + "\",\"code\":500}";
  std::string response =
      "HTTP/1.1 500 Internal Server Error\r\n"
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