#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "il2cpp-appdata.h"

// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str);

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String* str);

// Helper function to check if a metadata usage pointer is initialized
template<typename T> bool il2cppi_is_initialized(T* metadataItem) {
#if __IL2CPP_METADATA_VERISON < 270
    return *metadataItem != 0;
#else
    // Metadata >=27 (Unity 2020.2)
    return !((uintptr_t) *metadataItem & 1);
#endif
}

// Helper function to convert a pointer to hex
template<typename T> std::string to_hex_string(T i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}