#pragma once
#include <sys/types.h>
#include <string>

namespace services {
    class AssetBundleManager {
    public:
        static AssetBundleManager& getInstance()
        {
            // Guaranteed to be destroyed.
            static AssetBundleManager instance;
            // Instantiated on first use.
            return instance;
        }
    private:
        AssetBundleManager() {}

    public:
        AssetBundleManager(AssetBundleManager const&) = delete;
        void operator = (AssetBundleManager const&) = delete;

        void *get_asset_from_id(uint asset_id) {};
        void *download_asset(uint asset_id, std::string resource_location, std::string md5hash) {};
    };
}