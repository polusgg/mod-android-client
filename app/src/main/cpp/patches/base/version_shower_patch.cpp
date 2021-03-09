#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "version_shower_patch.h"

using namespace patches::base::version_shower_patch;

namespace patches { namespace base { namespace version_shower_patch
{
    void (*orig_versionshower_start)(app::VersionShower *_this, MethodInfo *method);

    void versionshower_start(app::VersionShower *_this, MethodInfo *method) {
        orig_versionshower_start(_this, method);

        _this->text->Text = app::String_Concat_4(_this->text->Text, (app::String *) il2cpp_string_new("\nPolusGG Modded"), nullptr);
    }

    void (*orig_pingtracker_update)(app::PingTracker *_this, MethodInfo *method);

    void pingtracker_update(app::PingTracker *_this, MethodInfo *method) {
        orig_pingtracker_update(_this, method);

        auto ping_tracker_go = app::Component_get_gameObject((app::Component *) _this, nullptr);
        app::GameObject_SetActive(ping_tracker_go, true, nullptr);
        _this->text->Text = (app::String *) il2cpp_string_new("\n[a103fcFF]PolusGG Modded");
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

