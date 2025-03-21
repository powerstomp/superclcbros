cmake_minimum_required(VERSION 3.15)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

project(superclcbros
	VERSION 0
	LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(superclcbros
	src/main.cpp

	src/Game.cpp
	src/GameState.cpp
	src/Settings.cpp

	src/State/StateMenu.cpp
	src/State/StateStart.cpp
	src/State/StateSettings.cpp
	src/State/StatePlay.cpp
	src/State/StateSelectStage.cpp
	src/State/StateSelectPlayer.cpp

	src/Entity/EntityManager.cpp
	src/Entity/EntityFactory.cpp
	src/Entity/PhysicsEngine.cpp
	src/Entity/Entity.cpp

	src/Entity/Player/Player.cpp
	src/Entity/Player/Mario.cpp
	src/Entity/Player/Luigi.cpp

	src/Entity/Enemy/Enemy.cpp
	src/Entity/Enemy/Goomba.cpp
	src/Entity/Enemy/Piranha.cpp

	src/Entity/Misc/Flag.cpp

	src/Entity/Pickup/PickupItem.cpp
	src/Entity/Pickup/CoinItem.cpp
	src/Entity/Pickup/OneUpItem.cpp
	src/Entity/Pickup/LuckyBlock.cpp
	src/Entity/Pickup/MushroomItem.cpp

	src/Entity/Controller/PlayerController.cpp
	src/Entity/Controller/SimpleAIController.cpp

	src/Entity/TileMap/TileMap.cpp

	src/Entity/Animation/Animation.cpp
	src/Entity/Animation/AnimationManager.cpp

	src/Entity/Animation/AnimationHandler.cpp
	src/Entity/Animation/IdleAnimationHandler.cpp
	src/Entity/Animation/JumpAnimationHandler.cpp
	src/Entity/Animation/WalkAnimationHandler.cpp
	src/Entity/Animation/DeadAnimationHandler.cpp

	src/Utility/SoundManager.cpp
	src/Utility/CSVMapLoader.cpp

	src/Keyboard/Keyboard.cpp)

target_link_libraries(superclcbros PRIVATE
	sfml-graphics
	sfml-audio)
target_compile_features(superclcbros PRIVATE cxx_std_17)

if(WIN32)
	add_custom_command(
		TARGET superclcbros
		COMMENT "Copy OpenAL DLL"
		PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:superclcbros>
		VERBATIM)
endif()

add_custom_command(
	TARGET superclcbros
	COMMENT "Copy assets"
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
	VERBATIM)
