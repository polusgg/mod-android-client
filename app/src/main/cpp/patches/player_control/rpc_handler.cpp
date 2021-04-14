#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "rpc_handler.h"
#include "rpc_types.h"
#include "../../services/AssetBundleManager.h"
#include "../../util/message_extensions.h"
#include "../../util/renderer_extensions.h"

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

                //TODO: Data.IsImpostor
                if (is_impostor && !player_info->DODNEPODPBP) {
                    // Change crewmate into impostor
                    auto hud_manager = app::DestroyableSingleton_1_HudManager__get_Instance(
                            *app::DestroyableSingleton_1_HudManager__get_Instance__MethodInfo
                    );

                    app::GameObject_SetActive(
                        app::Component_get_gameObject(
                            (app::Component *) hud_manager->KillButton, nullptr), true, nullptr
                    );
                    app::PlayerControl_SetKillTimer(_this->klass->static_fields->LocalPlayer, 10, nullptr);

                   app::List_1_PlayerTask__Insert_(
                        _this->myTasks,
                        0,
                        *app::List_1_PlayerTask__Insert__MethodInfo
                    );

                    auto all_players = (*app::GameData__TypeInfo)->static_fields->Instance->AllPlayers;

                    for (int i = 0; i < all_players->_size; i++) {
                        app::GameData_LFILBENDJJI* player_data = all_players->_items->vector[i];

                        //TODO: Data.IsImpostor
                        if (player_data->DODNEPODPBP) {
                            player_data->CMEFOJJGDPF->nameText->Color = (*app::LDIKEAJCMNK__TypeInfo)->static_fields->COJODPMDAFN;
                        }
                    }
                } else if (!is_impostor && player_info->DODNEPODPBP) {
                    auto hud_manager = app::DestroyableSingleton_1_HudManager__get_Instance(
                            *app::DestroyableSingleton_1_HudManager__get_Instance__MethodInfo
                    );

                    app::GameObject_SetActive(
                            app::Component_get_gameObject(
                                    (app::Component *) hud_manager->KillButton, nullptr), false, nullptr
                    );

                    // Change impostor into crewmate
                    app::List_1_PlayerTask__RemoveAt(
                        _this->myTasks,
                        0,
                        *app::List_1_PlayerTask__RemoveAt__MethodInfo
                    );

                    auto all_players = (*app::GameData__TypeInfo)->static_fields->Instance->AllPlayers;

                    for (int i = 0; i < all_players->_size; i++) {
                        app::GameData_LFILBENDJJI* player_data = all_players->_items->vector[i];

                        player_data->CMEFOJJGDPF->nameText->Color = (*app::LDIKEAJCMNK__TypeInfo)->static_fields->MINIGFDKGJD;
                    }
                }
                //TODO: Data.IsImpostor
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
            case patches::player_control::rpc_types::SetOutline: {
                auto hasOutline = app::MessageReader_ReadBoolean(ODDHFPNFBFN, nullptr);
                auto color = MessageReader_ReadColor(ODDHFPNFBFN);

                auto material = app::Renderer_get_material((app::Renderer *) _this->CNJCCNHODBO, nullptr);
                app::Material_SetFloat(material, (app::String *) il2cpp_string_new("_Outline"), (float) hasOutline, nullptr);
                app::Material_SetColor(material, (app::String *) il2cpp_string_new("_OutlineColor"), color->fields, nullptr);
                break;
            }
            case patches::player_control::rpc_types::SetOpacity: {
                auto new_alpha = app::MessageReader_ReadByte(ODDHFPNFBFN, nullptr) / 255;
                SpriteRenderer_SetAlpha(_this->CNJCCNHODBO, new_alpha);
                SpriteRenderer_SetAlpha(_this->HatRenderer->BackLayer, new_alpha);
                SpriteRenderer_SetAlpha(_this->HatRenderer->FrontLayer, new_alpha);
                SpriteRenderer_SetAlpha(_this->CurrentPet->rend, new_alpha);
                SpriteRenderer_SetAlpha(_this->CurrentPet->shadowRend, new_alpha);
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
