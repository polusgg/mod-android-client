#pragma once
#include "sys/types.h"
#include "framework/il2cpp-appdata.h"

namespace patches { namespace game_end_screen {
    inline app::String* title_text;
    inline app::String* subtitle_text;

    inline app::Color__Boxed* background_color;

    inline app::Byte__Array* your_team;

    inline bool should_display_quit;
    inline bool should_display_playagain;

    void patch();
} }