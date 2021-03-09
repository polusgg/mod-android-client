#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "end_screen.h"

namespace patches { namespace game_end_screen
{
    void (*orig_set_everything_up)(
            app::EndGameManager * _this,
            MethodInfo * method);

    void (*orig_show_buttons)(
            app::EndGameManager * _this,
            MethodInfo * method);

    app::List_1_MGGNLBPLMAI_* get_custom_team() {
        auto game_data = (*app::GameData__TypeInfo)->static_fields->Instance;

        auto winners = (app::List_1_MGGNLBPLMAI_ *) il2cpp_object_new(
                (Il2CppClass *) *app::List_1_MGGNLBPLMAI___TypeInfo);
        app::List_1_MGGNLBPLMAI___ctor(winners, *app::List_1_MGGNLBPLMAI___ctor__MethodInfo);

        for (int i = 0; i < your_team->bounds->length; i++) {
            auto player_id = your_team->vector[i];
            auto player_data = app::GameData_GetPlayerById(game_data, player_id, nullptr);

            auto winner = (app::MGGNLBPLMAI *) il2cpp_object_new(
                    (Il2CppClass *) *app::MGGNLBPLMAI__TypeInfo);
            app::MGGNLBPLMAI__ctor_1(winner, player_data, nullptr);

            app::List_1_MGGNLBPLMAI__Add(
                    winners,
                    winner,
                    *app::List_1_MGGNLBPLMAI__Add__MethodInfo
            );
        }

        return winners;
    }

    void set_everything_up(
            app::EndGameManager * _this,
            MethodInfo * method)
    {
        if (your_team != nullptr) {
            auto winners = get_custom_team();
            (*app::FPAJLCHJHJD__TypeInfo)->static_fields->HIHJGNDGEGO = winners;
        }

        orig_set_everything_up(_this, method);
        _this->WinText->Text = title_text;
        _this->WinText->Color = background_color->fields;

        auto material = app::Renderer_get_material((app::Renderer *) _this->BackgroundBar, nullptr);
        app::Material_SetColor(
                material,
                (app::String *) il2cpp_string_new("_Color"),
                background_color->fields, nullptr
        );
    }

    void show_buttons(
            app::EndGameManager * _this,
            MethodInfo * method)
    {
        orig_show_buttons(_this, method);
        auto play_again_game_obj = app::Component_get_gameObject((app::Component *) _this->PlayAgainButton, nullptr);
        app::GameObject_SetActive(play_again_game_obj, should_display_playagain, nullptr);

        auto exit_button_game_obj = app::Component_get_gameObject((app::Component *) _this->ExitButton, nullptr);
        app::GameObject_SetActive(exit_button_game_obj, should_display_quit, nullptr);
    }

    void patch() {
        DobbyHook(
                (void *) app::EndGameManager_IDIJEDGIJPK,
                (void *) set_everything_up,
                (void **) &orig_set_everything_up
        );
        DobbyHook(
                (void *) app::EndGameManager_JODGIEHMFJM,
                (void *) show_buttons,
                (void **) &orig_show_buttons
        );
    }
} }