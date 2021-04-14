#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "framework/il2cpp-helpers.h"
#include "root_packet_handler.h"
#include "root_packet_types.h"
#include "../../services/AssetBundleManager.h"
#include "../../services/InnerNetObjManager.h"
#include "../../util/construct_type.h"
#include "../../util/message_extensions.h"
#include "../game_transition_screen/start_screen.h"
#include "../game_transition_screen/end_screen.h"
#include "../set_string/set_string.h"

namespace patches { namespace root_packet { namespace root_packet_handler
{
    void (*orig_function)(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            app::SendOption__Enum KJJKMAEPHIK,
            MethodInfo * method);

    void detoured_function(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            app::SendOption__Enum KJJKMAEPHIK,
            MethodInfo * method)
    {
        switch (auto tag = (patches::root_packet::root_packet_types) ODDHFPNFBFN->Tag) {
            case patches::root_packet::root_packet_types::FetchResource: {
                auto asset_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto resource_location = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                auto md5hash = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);

                services::AssetBundleManager::getInstance().download_asset(
                        asset_id,
                        il2cppi_to_string(resource_location),
                        il2cppi_to_string(md5hash)
                );

                break;
            }
            case patches::root_packet::root_packet_types::DisplayGameStartScreen: {
                patches::game_start_screen::title_text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                patches::game_start_screen::subtitle_text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);

                patches::game_start_screen::background_color = MessageReader_ReadColor(ODDHFPNFBFN);

                patches::game_start_screen::your_team = app::MessageReader_ReadBytesAndSize(ODDHFPNFBFN, nullptr);

                break;
            }
            case patches::root_packet::root_packet_types::OverwriteGameOver: {
                patches::game_end_screen::title_text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                patches::game_end_screen::subtitle_text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);

                patches::game_end_screen::background_color = MessageReader_ReadColor(ODDHFPNFBFN);;

                patches::game_end_screen::your_team = app::MessageReader_ReadBytesAndSize(ODDHFPNFBFN, nullptr);

                patches::game_end_screen::should_display_quit = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);
                patches::game_end_screen::should_display_playagain = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);

                break;

            }
            case patches::root_packet::root_packet_types::SetString: {
                auto location = app::MessageReader_ReadByte(ODDHFPNFBFN, nullptr);

                switch ((patches::set_string::string_location) location) {
                    case patches::set_string::string_location::GameCode: {
                        auto game_start_manager = app::DestroyableSingleton_1_GameStartManager__get_Instance(
                            *app::DestroyableSingleton_1_GameStartManager__get_Instance__MethodInfo
                        );
                        game_start_manager->GameRoomName->Text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::GamePlayerCount: {
                        patches::set_string::game_player_count = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::TaskText: {
                        patches::set_string::task_text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::RoomTracker: {
                        patches::set_string::room_tracker = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::PingTracker: {
                        patches::set_string::ping_tracker = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::GameOptions: {
                        patches::set_string::game_options = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        break;
                    }
                    case patches::set_string::string_location::TaskCompletion: {
                        auto title_text = app::GameObject_Find((app::String *) il2cpp_string_new("/Main Camera/Hud/TaskStuff/ProgressTracker/TitleText"), nullptr);

                        if (title_text != nullptr) {
                            auto text_renderer = app::GameObject_GetComponent(title_text, get_type((Il2CppClass *) *app::TextRenderer_c__TypeInfo), nullptr);
                            ((app::TextRenderer *) text_renderer)->Text = app::MessageReader_ReadString(ODDHFPNFBFN, nullptr);
                        }
                        break;
                    }
                }
                break;
            }
            case patches::root_packet::root_packet_types::DeclareHat: {
                auto hat_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto front_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto back_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto floor_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto climb_id = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto hat_shader = app::MessageReader_ReadPackedUInt32(ODDHFPNFBFN, nullptr);
                auto offset = MessageReader_ReadVector2(ODDHFPNFBFN);
                auto bounces = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);
                auto hasBack = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);
                auto accessible = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);

                auto front_sprite = services::AssetBundleManager::getInstance().get_asset_from_id(front_id);
                auto back_sprite = services::AssetBundleManager::getInstance().get_asset_from_id(back_id);
                auto floor_sprite = services::AssetBundleManager::getInstance().get_asset_from_id(floor_id);
                auto climb_sprite = services::AssetBundleManager::getInstance().get_asset_from_id(climb_id);

                auto hat = (app::HatBehaviour *) il2cpp_object_new((Il2CppClass *) *app::HatBehaviour__TypeInfo);
                app::HatBehaviour__ctor(hat, nullptr);

                if (!hasBack) {
                    hat->MainImage = (app::Sprite *) front_sprite;
                } else {
                    hat->BackImage = (app::Sprite *) back_sprite;
                }
                hat->FloorImage = (app::Sprite *) floor_sprite;


                hat->Free = true;
                if (!accessible) {
                    hat->LimitedYear = 1900;
                }
                hat->ChipOffset = offset->fields;

                //TODO: HatBehaviour inversion of boolean
                hat->NoBounce = !bounces;
                hat->InFront = !hasBack;

                auto hat_manager = app::DestroyableSingleton_1_HatManager__get_Instance(
                        *app::DestroyableSingleton_1_HatManager__get_Instance__MethodInfo
                );

                //TODO: Vtable invoke List<HatBehaviour>.Add()
                auto add_methodinfo = hat_manager->AllHats->klass->vtable.Add.method;
                il2cpp_runtime_invoke(il2cpp_object_get_virtual_method((Il2CppObject *) hat_manager, add_methodinfo), hat_manager, (void **) &hat, nullptr);
                break;
            }
            case patches::root_packet::root_packet_types::EndGame: {
                services::InnerNetObjManager::getInstance().destroy();
                orig_function(_this, ODDHFPNFBFN, KJJKMAEPHIK, method);
                break;
            }
            default: {
                orig_function(_this, ODDHFPNFBFN, KJJKMAEPHIK, method);
                break;
            }
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::InnerNetClient_LFJJNNAMHEP,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

} } }