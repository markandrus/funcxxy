#include <iostream>

#include <funcxxy/funcxxy.h>
#include <rapidjson/document.h>

using namespace funcxxy;
using namespace rapidjson;

static Validation<int> getInt(const GenericValue<UTF8<char>>& value) {
  return value.IsInt()
      ? Valid(value.GetInt())
      : Invalid<int>("Expected an int");
}

static Validation<std::string> getString(const GenericValue<UTF8<char>>& value) {
  return value.IsString()
      ? Valid(std::string(value.GetString()))
      : Invalid<std::string>("Expected a string");
}

static std::string duplicate(const std::string message, const int times) {
  std::string duplicated;
  for (int i = 0; 0 < times && i < times; i++) {
    duplicated += message + "\n";
  }
  return duplicated;
}

int main() {
  Document document;
  document.Parse(R"({"message":"Hello, World!","times":10})");
  return (
    curry(duplicate)
      % getString(document["message"])
      * getInt(document["times"])
  ).FromValidation<int>([](const Errors errors) {
    for (const auto &error : errors) {
      std::cerr << " - " << error << std::endl;
    }
    return 1;
  }, [](const std::string duplicated) {
    std::cout << duplicated;
    return 0;
  });
}
