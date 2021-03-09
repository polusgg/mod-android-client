#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "start_screen.h"

namespace patches { namespace game_start_screen
{
    void (*orig_begin_crewmate)(
            app::IntroCutscene * _this,
            app::List_1_PlayerControl_ GCJGFDNHKDA,
            MethodInfo * method);

    void (*orig_begin_impostor)(
            app::IntroCutscene * _this,
            app::List_1_PlayerControl_ GCJGFDNHKDA,
            MethodInfo * method);

    app::List_1_PlayerControl_* get_custom_team() {
        auto game_data = (*app::GameData__TypeInfo)->static_fields->Instance;

        auto player_controls = (app::List_1_PlayerControl_ *) il2cpp_object_new(
                (Il2CppClass *) *app::List_1_PlayerControl___TypeInfo);
        app::List_1_PlayerControl___ctor(player_controls, *app::List_1_PlayerControl___ctor__MethodInfo);

        for (int i = 0; i < your_team->bounds->length; i++) {
            auto player_id = your_team->vector[i];
            auto player_data = app::GameData_GetPlayerById(game_data, player_id, nullptr);
            app::List_1_PlayerControl__Add(
                    player_controls,
                    player_data->CMEFOJJGDPF,
                    *app::List_1_PlayerControl__Add__MethodInfo
            );
        }

        return player_controls;
    }

    void begin_crewmate(
            app::IntroCutscene * _this,
            app::List_1_PlayerControl_ GCJGFDNHKDA,
            MethodInfo * method)
    {
        auto player_controls = &GCJGFDNHKDA;
        if (your_team != nullptr) {
            player_controls = get_custom_team();
        }

        orig_begin_crewmate(_this, *player_controls, method);

        auto impostor_text_game_obj = app::Component_get_gameObject((app::Component *) _this->ImpostorText, nullptr);
        app::GameObject_SetActive(impostor_text_game_obj, true, nullptr);
        _this->Title->Text = title_text;
        _this->Title->Color = background_color->fields;
        _this->ImpostorText->Text = subtitle_text;

        auto material = app::Renderer_get_material((app::Renderer *) _this->BackgroundBar, nullptr);
        app::Material_SetColor(
                material,
                (app::String *) il2cpp_string_new("_Color"),
                background_color->fields, nullptr
        );
    }

    void begin_impostor(
            app::IntroCutscene * _this,
            app::List_1_PlayerControl_ GCJGFDNHKDA,
            MethodInfo * method)
    {
        auto player_controls = &GCJGFDNHKDA;
        if (your_team != nullptr) {
            player_controls = get_custom_team();
        }

        orig_begin_impostor(_this, *player_controls, method);

        app::GameObject_SetActive((app::GameObject *) (_this->ImpostorText), true, nullptr);
        _this->Title->Text = title_text;
        _this->Title->Color = background_color->fields;
        _this->ImpostorText->Text = subtitle_text;
    }

    void patch() {
        DobbyHook(
                (void *) app::IntroCutscene_MPPDNDNKJOL,
                (void *) begin_crewmate,
                (void **) &orig_begin_crewmate
        );
        DobbyHook(
                (void *) app::IntroCutscene_HJCAJHNEEIP,
                (void *) begin_impostor,
                (void **) &orig_begin_impostor
        );
    }
} }