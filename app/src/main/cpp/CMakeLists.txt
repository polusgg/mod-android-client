# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
project(PGGAndroidNativeMod)

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        pggandroidnative

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        main.cpp
        custom_objects/inner_net/inner_net_obj_types.h
        custom_objects/inner_net/InnerNetObj.cpp
        custom_objects/inner_net/InnerNetObj.h
        custom_objects/inner_net/spawn_entity_types.h
        patches/patch_manager.cpp
        patches/patch_manager.h
        patches/base/version_shower_patch.cpp
        patches/base/version_shower_patch.h
        patches/game_data/rpc_handler.cpp
        patches/game_data/rpc_handler.h
        patches/game_data/rpc_types.h
#        patches/game_transition_screen/end_screen.cpp
#        patches/game_transition_screen/end_screen.h
#        patches/game_transition_screen/start_screen.cpp
#        patches/game_transition_screen/start_screen.h
        patches/lobby_behaviour/rpc_handler.cpp
        patches/lobby_behaviour/rpc_handler.h
        patches/lobby_behaviour/rpc_types.h
        patches/player_control/remove_murder_check.cpp
        patches/player_control/remove_murder_check.h
        patches/player_control/rpc_handler.cpp
        patches/player_control/rpc_handler.h
        patches/player_control/rpc_types.h
        patches/root_packet/game_data/spawn_packet_handler.cpp
        patches/root_packet/game_data/spawn_packet_handler.h
        patches/root_packet/root_packet_handler.cpp
        patches/root_packet/root_packet_handler.h
        patches/root_packet/root_packet_types.h
        services/AssetBundleManager.h
        services/InnerNetObjManager.cpp
        services/InnerNetObjManager.h
        util/construct_color.cpp
        util/construct_color.h
        util/helpers.cpp
        util/helpers.h
        util/logger.h
        il2cpp-headers/framework/il2cpp-init.cpp
        il2cpp-headers/framework/il2cpp-helpers.cpp
        )



# Include il2cpp-headers
include_directories(
        il2cpp-headers
)



# Include Dobby Library
set(DobbyHome ${PROJECT_SOURCE_DIR}/../../../../Dobby)
include_directories(
        ${DobbyHome}/include
        ${DobbyHome}/builtin-plugin
        ${DobbyHome}/builtin-plugin/SymbolResolver
        ${DobbyHome}/builtin-plugin/AndroidRestriction
        ${DobbyHome}/external/logging
)

add_library( dobby
        SHARED
        IMPORTED )

set_target_properties( # Specifies the target library.
        dobby

        # Specifies the parameter you want to define.
        PROPERTIES IMPORTED_LOCATION

        # Provides the path to the library you want to import.
        ${DobbyHome}/auto-build-output/android/${ANDROID_ABI}/libdobby.so )



# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        pggandroidnative

        dobby

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )
