#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "../../util/logger.h"
#include "remove_murder_check.h"

namespace patches { namespace player_control { namespace remove_murder_check
{
    void (*orig_function)(
            app::PlayerControl * _this,
            app::PlayerControl * HNOEFAFMPDG,
            MethodInfo * method);

    void detoured_function(
            app::PlayerControl * _this,
            app::PlayerControl * HNOEFAFMPDG,
            MethodInfo * method)
    {
        auto player_info = app::PlayerControl_get_Data(_this, nullptr);

        bool orig_impostor = player_info->DODNEPODPBP;
        bool orig_dead = player_info->JJCBCHPJBAN;

        player_info->DODNEPODPBP = true;
        player_info->JJCBCHPJBAN = false;

        orig_function(_this, HNOEFAFMPDG, method);

        player_info->DODNEPODPBP = orig_impostor;
        player_info->JJCBCHPJBAN = orig_dead;
    }

    void patch() {
        DobbyHook(
                (void *) app::PlayerControl_MurderPlayer,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }
