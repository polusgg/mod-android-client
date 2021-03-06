#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "framework/il2cpp-helpers.h"
#include "root_packet_handler.h"
#include "root_packet_types.h"
#include "../../services/AssetBundleManager.h"
#include "../../util/construct_color.h"
#include "../game_transition_screen/start_screen.h"
#include "../game_transition_screen/end_screen.h"

namespace patches { namespace root_packet { namespace root_packet_handler
{
    void (*orig_function)(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            app::SendOption__Enum KJJKMAEPHIK,
            MethodInfo * method);

    void patch() {
        DobbyHook(
                (void *) app::InnerNetClient_LFJJNNAMHEP,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

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
            default: {
                orig_function(_this, ODDHFPNFBFN, KJJKMAEPHIK, method);
                break;
            }
        }
    }

} } }