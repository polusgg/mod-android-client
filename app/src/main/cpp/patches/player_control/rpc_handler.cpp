#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "rpc_handler.h"
#include "rpc_types.h"
#include "../../services/AssetBundleManager.h"

namespace patches { namespace player_control { namespace rpc_handler
{
    void (*orig_function)(
        app::PlayerControl * _this,
        uint8_t MMLACCAPBPM,
        app::MessageReader * ODDHFPNFBFN,
        MethodInfo * method);

    void detoured_function(
            app::PlayerControl * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method)
    {
        switch (auto call_id = (patches::player_control::rpc_types) MMLACCAPBPM) {
            case patches::player_control::rpc_types::SetRole: {
                auto player_info = app::PlayerControl_get_Data(_this, nullptr);
                auto is_impostor = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);

                player_info->DODNEPODPBP = is_impostor;

                break;
            }
            case patches::player_control::rpc_types::CloseHud: {
                auto minigame = (*app::Minigame__TypeInfo)->static_fields->Instance;
                auto map = (*app::MapBehaviour__TypeInfo)->static_fields->Instance;

                try {
                    app::Minigame_Close_1(minigame, nullptr);
                    app::MapBehaviour_Close(map, nullptr);
                } catch (Il2CppExceptionWrapper& e) {}

                break;
            }
            case patches::player_control::rpc_types::Revive: {
                app::PlayerControl_Revive(_this, nullptr);

                break;
            }
            case patches::player_control::rpc_types::PlaySound: {
                auto asset_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto audio_clip = services::AssetBundleManager::getInstance().get_asset_from_id(asset_id);

                // Volume from 0-100
                auto volume_byte = app::MessageReader_ReadByte(ODDHFPNFBFN, nullptr);

                // Scale it to float value between 0 and 1
                auto volume = (float) volume_byte / 100;

                auto sound_manager = app::SoundManager_get_Instance(nullptr);
                app::SoundManager_PlaySound(sound_manager, (app::AudioClip *) audio_clip, false, volume, nullptr);

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
                (void *) app::PlayerControl_HandleRpc,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

} } }
