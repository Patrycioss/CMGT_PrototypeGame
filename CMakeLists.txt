cmake_minimum_required(VERSION 3.23)
project(SFMLPEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_subdirectory(random)
add_subdirectory(SFML-3.6.x)

add_executable(SFMLPEngine
        src/main.cpp
        src/Engine/Sprite.cpp src/Engine/Sprite.hpp
        src/Engine/EventSystem/EventManager.cpp src/Engine/EventSystem/EventManager.hpp
        src/Engine/EventSystem/EventHandler.cpp src/Engine/EventSystem/EventHandler.hpp
        src/Engine/Rectangle.hpp src/Engine/GameObject.cpp src/Engine/GameObject.hpp
        src/Engine/GameObject.cpp src/Engine/GameObject.hpp
        src/Engine/ResourceManager.cpp src/Engine/ResourceManager.hpp src/Engine/Scene.cpp
        src/Engine/Scene.hpp src/Engine/Game.cpp src/Engine/Game.hpp src/CMGT_PrototypeGame.cpp
        src/CMGT_PrototypeGame.hpp
        src/Engine/AnimationSprite.cpp src/Engine/AnimationSprite.hpp
        src/MainMenu/MainMenu.cpp src/MainMenu/MainMenu.hpp
        src/UserData/ScoreLoader.cpp src/UserData/ScoreLoader.hpp src/MainMenu/ScoreViewer.cpp
        src/MainMenu/ScoreViewer.hpp src/MainMenu/ScoreCard.cpp src/MainMenu/ScoreCard.hpp
        src/Character/Character.cpp src/Character/Character.hpp
        src/Engine/Button.cpp src/Engine/Button.hpp
        src/Arena/Arena.cpp src/Arena/Arena.hpp
        src/CharacterSelect/Selection.cpp src/CharacterSelect/Selection.hpp src/CharacterSelect/TextInput.cpp src/CharacterSelect/TextInput.hpp
        src/Utility/Tweening/TweenManager.cpp
        src/Utility/Tweening/TweenManager.hpp src/Utility/Tweening/Tween.cpp src/Utility/Tweening/Tween.hpp
        src/Utility/Tweening/RectangleShapeSizeTween.cpp src/Utility/Tweening/RectangleShapeSizeTween.hpp
        src/Utility/Tweening/RectPosTween.cpp src/Utility/Tweening/RectPosTween.hpp src/Character/Attributes.hpp
        src/Character/Wellness.hpp src/Arena/OutputLog.cpp src/Arena/OutputLog.hpp src/Utility/Timers/Timer.cpp
        src/Utility/Timers/Timer.hpp src/Utility/Timers/TimerManager.cpp src/Utility/Timers/TimerManager.hpp src/Utility/Tweening/SpritePosTween.cpp
        src/Utility/Tweening/SpritePosTween.hpp src/Arena/ConstantManager.hpp src/UserData/SaveLoader.cpp src/UserData/SaveLoader.hpp
        src/Audio/Jukebox.cpp src/Audio/Jukebox.hpp)

target_link_libraries(SFMLPEngine PRIVATE effolkronium_random)
target_link_libraries(SFMLPEngine PRIVATE sfml-system sfml-graphics sfml-audio)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})


target_compile_features(SFMLPEngine PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SFMLPEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SFMLPEngine> $<TARGET_FILE_DIR:SFMLPEngine> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SFMLPEngine)