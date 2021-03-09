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
            case patches::lobby_behaviour::rpc_types::SetCode: {
                auto game_code = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                auto translation_controller = app::DestroyableSingleton_1_TranslationController__get_Instance(
                    *app::DestroyableSingleton_1_TranslationController__get_Instance__MethodInfo
                );
                auto translated_string = app::TranslationController_GetString_2(
                        translation_controller,
                        app::StringNames__Enum::RoomCode,
                        app::Array_Empty(*app::Array_Empty__MethodInfo),
                        nullptr);

                auto new_game_code = il2cppi_to_string(translated_string) + "\r\n" + il2cppi_to_string(game_code);
                LOGI("Visually changing the game code to: %s", new_game_code.c_str());

                auto game_start_manager = app::DestroyableSingleton_1_GameStartManager__get_Instance(
                    *app::DestroyableSingleton_1_GameStartManager__get_InstanceExists__MethodInfo
                );
                game_start_manager->GameRoomName->Text = (app::String *) (il2cpp_string_new(new_game_code.c_str()));

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


