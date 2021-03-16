#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "framework/il2cpp-helpers.h"
#include "rpc_handler.h"
#include "rpc_types.h"
#include "../../util/logger.h"

namespace patches { namespace lobby_behaviour { namespace rpc_handler
{
    void (*orig_function)(
            app::LobbyBehaviour * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void detoured_function(
            app::LobbyBehaviour * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method)
    {
        switch (auto call_id = (patches::lobby_behaviour::rpc_types) MMLACCAPBPM) {
            case patches::lobby_behaviour::rpc_types::SetString: {
                auto string_boxed = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                auto location = app::MessageReader_ReadByte(ODDHFPNFBFN, nullptr);

                auto game_start_manager = app::DestroyableSingleton_1_GameStartManager__get_Instance(
                    *app::DestroyableSingleton_1_GameStartManager__get_InstanceExists__MethodInfo
                );
                game_start_manager->GameRoomName->Text = string_boxed;

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
                (void *) app::LobbyBehaviour_HandleRpc,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

} } }


