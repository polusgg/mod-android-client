#include "framework/il2cpp-appdata.h"
#include "framework/il2cpp-helpers.h"
#include <dobby.h>
#include "../../util/logger.h"
#include "chat_command_patch.h"

namespace patches { namespace player_control { namespace chat_command
{
    void (*orig_function)(
            app::PlayerControl * _this,
            app::String * BPPNGLNCFAL,
            MethodInfo * method);

    void detoured_function(
            app::PlayerControl * _this,
            app::String * BPPNGLNCFAL,
            MethodInfo * method)
    {
        orig_function(_this, BPPNGLNCFAL, method);

        auto chat_msg = il2cppi_to_string(BPPNGLNCFAL);

        if (chat_msg.find("/button")) {
            auto hud_manager = app::DestroyableSingleton_1_HudManager__get_Instance(
                    *app::DestroyableSingleton_1_HudManager__get_Instance__MethodInfo
            );
            auto hud_manager_transform = app::Component_get_transform((app::Component *) hud_manager, nullptr);

            auto button = (app::KillButtonManager *) app::Object_1_Instantiate_3((app::Object *) hud_manager->KillButton, *app::Object_1_Instantiate_3__MethodInfo);
            auto button_transform = app::Component_get_transform((app::Component *) button, nullptr);
            app::Transform_set_parent(button_transform, hud_manager_transform, nullptr);

            auto report_button_transform = app::Component_get_transform((app::Component *) hud_manager->ReportButton, nullptr);
            auto report_pos = app::Transform_get_localPosition(report_button_transform, nullptr);

            app::Vector3 button_local_pos;
            button_local_pos.x = report_pos.x;
            button_local_pos.y = report_pos.y + 1.25;
            button_local_pos.z = report_pos.z;

            app::Transform_set_localPosition(button_transform, button_local_pos, nullptr);
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::PlayerControl_RpcSendChat,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }