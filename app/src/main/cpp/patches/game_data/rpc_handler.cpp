#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "rpc_handler.h"
#include "rpc_types.h"

namespace patches { namespace game_data { namespace rpc_handler
{
    void (*orig_function)(
            app::GameData * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void detoured_function(
            app::GameData * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method)
    {
        switch (auto call_id = (patches::game_data::rpc_types) MMLACCAPBPM) {
            case patches::game_data::rpc_types::ChatVisibility: {
                auto is_chat_visible = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);

                auto hud_manager = app::DestroyableSingleton_1_HudManager__get_Instance(
                    *app::DestroyableSingleton_1_HudManager__get_InstanceExists__MethodInfo
                );
                app::ChatController_SetVisible(hud_manager->Chat, is_chat_visible, nullptr);

                break;
            }
            default: {
                orig_function(_this, MMLACCAPBPM, ODDHFPNFBFN, method);
                break;
            }
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::GameData_HandleRpc,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

} } }
