#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "version_shower_patch.h"
#include "../set_string/set_string.h"

using namespace patches::base::version_shower_patch;

namespace patches { namespace base { namespace version_shower_patch
{
    void (*orig_versionshower_start)(app::VersionShower *_this, MethodInfo *method);

    void versionshower_start(app::VersionShower *_this, MethodInfo *method) {
        orig_versionshower_start(_this, method);

        _this->text->Text = (app::String *) il2cpp_string_new("[FF7E7EFF] Among Us (2021.4.2a)\n [B77EFFFF]PolusGG Modded")
    }

    void (*orig_pingtracker_update)(app::PingTracker *_this, MethodInfo *method);

    void pingtracker_update(app::PingTracker *_this, MethodInfo *method) {
        orig_pingtracker_update(_this, method);

        auto ping_tracker_go = app::Component_get_gameObject((app::Component *) _this, nullptr);
        app::GameObject_SetActive(ping_tracker_go, true, nullptr);

        if (il2cppi_to_string(set_string::ping_tracker) != "__unset") {
            _this->text->Text = set_string::ping_tracker;
        }
    }


    void patch() {
        DobbyHook(
                (void *) app::VersionShower_Start,
                (void *) versionshower_start,
                (void **) &orig_versionshower_start
        );
        DobbyHook(
                (void *) app::PingTracker_Update,
                (void *) pingtracker_update,
                (void **) &orig_pingtracker_update
        );
    }

} } }

