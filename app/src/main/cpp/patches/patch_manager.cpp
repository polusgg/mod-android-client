#include "patch_manager.h"
#include "../util/logger.h"

#include "base/version_shower_patch.h"
#include "game_data/rpc_handler.h"
#include "lobby_behaviour/rpc_handler.h"
#include "player_control/rpc_handler.h"
#include "root_packet/root_packet_handler.h"

using namespace patches;

void patch_all() {
    LOGI("Patching libil2cpp.so...");

    base::version_shower_patch::patch();
    game_data::rpc_handler::patch();
    lobby_behaviour::rpc_handler::patch();
    player_control::rpc_handler::patch();
    root_packet::root_packet_handler::patch();
}