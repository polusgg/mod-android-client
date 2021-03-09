#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "../../util/logger.h"
#include "shipstatus_begin.h"

namespace patches { namespace lifecycle { namespace shipstatus_begin
{
    void (*orig_function)(
            app::ShipStatus * _this,
            MethodInfo * method);

    void detoured_function(
            app::ShipStatus * _this,
            MethodInfo * method)
    {
        orig_function(_this, method);
        auto hud_manager = app::DestroyableSingleton_1_HudManager__get_Instance(
                *app::DestroyableSingleton_1_HudManager__get_InstanceExists__MethodInfo
        );

        app::ChatController_SetVisible(hud_manager->Chat, true, nullptr);
    }

    void patch() {
        DobbyHook(
                (void *) app::ShipStatus_Start,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }