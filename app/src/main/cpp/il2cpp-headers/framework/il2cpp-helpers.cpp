#include "il2cpp-helpers.h"
#include <codecvt>

// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString *str) {
    std::u16string u16(reinterpret_cast<const char16_t *>(str->chars));
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String *str) {
    return il2cppi_to_string(reinterpret_cast<Il2CppString *>(str));
}