#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

class Serializable {
 public:
  virtual ~Serializable() = default;

  virtual std::string serialize() const = 0;
  virtual void deserialize(const std::string& data) = 0;

  std::string extractJsonStringValue(const std::string& json,
                                     const std::string& key) {
    std::string needle = "\"" + key + "\"";
    std::size_t keyPos = json.find(needle);
    if (keyPos == std::string::npos) return "";

    std::size_t colonPos = json.find(':', keyPos);
    if (colonPos == std::string::npos) return "";

    std::size_t quoteStart = json.find('"', colonPos + 1);
    if (quoteStart == std::string::npos) return "";

    std::size_t quoteEnd = json.find('"', quoteStart + 1);
    if (quoteEnd == std::string::npos) return "";

    return json.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
  }
};

#endif