// Helper functions

#include <string>
#include <cinttypes>
#include "helpers.h"
#include "logger.h"

uintptr_t get_library_address(const char* library_name) {
    uintptr_t base_address = 0;

    char buffer[1024];
    FILE *fp = fopen("/proc/self/maps", "re");

    if (!fp) {
        LOGW("[-] Could not open /proc/self/maps to scan for loaded libraries");
        return 0;
    }

    while(fgets(buffer, sizeof(buffer), fp)) {
        if(strstr(buffer, library_name)) {
            base_address = std::stoul(buffer, nullptr, 16);
            LOGI("[+] Found %s library loaded at address: 0x%016" PRIxPTR "\n", library_name, base_address);
            break;
        }
    }

    fclose(fp);
    return base_address;
}

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address() {
	if (il2cpp_base_address == 0) {
		il2cpp_base_address = get_library_address("libil2cpp.so");
		return il2cpp_base_address;
    } else {
		return il2cpp_base_address;
	}
}

