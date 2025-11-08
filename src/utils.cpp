#include "utils.hpp"
#include <string>

namespace Utils {
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return start == std::string::npos ? "" : str.substr(start, end - start + 1);
}
}  // namespace Utils