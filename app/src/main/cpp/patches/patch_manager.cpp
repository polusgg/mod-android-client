#include "patch_manager.h"
#include "../util/logger.h"

#include "base/version_shower_patch.h"
#include "game_data/rpc_handler.h"
//#include "game_transition_screen/end_screen.h"
//#include "game_transition_screen/start_screen.h"
#include "lobby_behaviour/rpc_handler.h"
#include "player_control/remove_murder_check.h"
#include "player_control/rpc_handler.h"
#include "root_packet/game_data/spawn_packet_handler.h"
#include "root_packet/root_packet_handler.h"

using namespace patches;

void patch_all() {
    LOGI("Patching libil2cpp.so...");

    base::version_shower_patch::patch();
    game_data::rpc_handler::patch();
//    game_end_screen::patch();
//    game_start_screen::patch();
    lobby_behaviour::rpc_handler::patch();
    player_control::rpc_handler::patch();
    player_control::remove_murder_check::patch();
    root_packet::game_data::patch();
    root_packet::root_packet_handler::patch();
}