#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "set_string.h"
#include "framework/il2cpp-appdata.h"
#include "framework/il2cpp-helpers.h"

namespace patches { namespace set_string
{
    void (*orig_game_start_manager_update)(
            app::GameStartManager * _this,
            MethodInfo * method);

    void (*orig_roomtracker_fixedupdate)(
            app::RoomTracker * _this,
            MethodInfo * method);

    app::String* (*orig_gameoptionsdata_tohudstring)(
            app::HJIEMIFIFNK * _this,
            int32_t GIKFMIFOBDM,
            MethodInfo * method);

    void (*orig_hudmanager_update)(
            app::HudManager * _this,
            MethodInfo * method);


    void game_start_manager_update(
        app::GameStartManager * _this,
        MethodInfo * method)
    {
        orig_game_start_manager_update(_this, method);
        if (il2cppi_to_string(game_player_count) != "__unset") {
            _this->PlayerCounter->Text = game_player_count;
        }
    }

    void roomtracker_fixedupdate (
        app::RoomTracker * _this,
        MethodInfo * method
    ) {
        orig_roomtracker_fixedupdate(_this, method);

        if (il2cppi_to_string(room_tracker) != "__unset") {
            _this->text->Text = room_tracker;
        }
    };

    app::String* gameoptionsdata_tohudstring(
        app::HJIEMIFIFNK * _this,
        int32_t GIKFMIFOBDM,
        MethodInfo * method
    ) {
        if (il2cppi_to_string(game_options) == "__unset") {
            return orig_gameoptionsdata_tohudstring(_this, GIKFMIFOBDM, method);
        } else {
            return game_options;
        }
    }

    void hudmanager_update(
        app::HudManager * _this,
        MethodInfo * method
    ) {
        orig_hudmanager_update(_this, method);

        if (il2cppi_to_string(task_text) != "__unset") {
            _this->TaskText->Text = task_text;
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::GameStartManager_Update,
                (void *) game_start_manager_update,
                (void **) &orig_game_start_manager_update
        );
        DobbyHook(
                (void *) app::RoomTracker_FixedUpdate,
                (void *) roomtracker_fixedupdate,
                (void **) &orig_roomtracker_fixedupdate
        );
        DobbyHook(
                (void *) app::HJIEMIFIFNK_BMGJFOLFFEI,
                (void *) gameoptionsdata_tohudstring,
                (void **) &orig_gameoptionsdata_tohudstring
        );
        DobbyHook(
                (void *) app::HudManager_Update,
                (void *) hudmanager_update,
                (void **) &orig_hudmanager_update
        );
    }
} }