#pragma once
#include "framework/il2cpp-appdata.h"
#include "framework/il2cpp-helpers.h"

namespace patches { namespace set_string {

    enum string_location {
        GameCode,
        GamePlayerCount,
        TaskText,
        RoomTracker,
        PingTracker,
        TaskCompletion,
        GameOptions
    };

    inline app::String* game_player_count = (app::String *) il2cpp_string_new("__unset");
    inline app::String* task_text = (app::String *) il2cpp_string_new("__unset");
    inline app::String* room_tracker = (app::String *) il2cpp_string_new("__unset");
    inline app::String* ping_tracker = (app::String *) il2cpp_string_new("[a103fcFF]PolusGG Modded");
    inline app::String* game_options = (app::String *) il2cpp_string_new("__unset");

    void patch();
} }