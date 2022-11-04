cmake_minimum_required(VERSION 3.23)
project(SFMLPEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_subdirectory(random)
add_subdirectory(SFML-3.6.x)

add_executable(SFMLPEngine
        CMGT_PrototypeGame/main.cpp
        SFMLPE/Core/Sprite.cpp SFMLPE/Core/Sprite.hpp
        SFMLPE/Core/EventSystem/EventManager.cpp SFMLPE/Core/EventSystem/EventManager.hpp 
        SFMLPE/Core/EventSystem/EventHandler.cpp SFMLPE/Core/EventSystem/EventHandler.hpp 
        SFMLPE/Core/Rectangle.hpp SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp
        SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp
        SFMLPE/Core/ResourceManager.cpp SFMLPE/Core/ResourceManager.hpp SFMLPE/Core/Scene.cpp 
        SFMLPE/Core/Scene.hpp SFMLPE/Core/Game.cpp SFMLPE/Core/Game.hpp CMGT_PrototypeGame/CMGT_PrototypeGame.cpp 
        CMGT_PrototypeGame/CMGT_PrototypeGame.hpp SFMLPE/SFMLPE.hpp CMGT_PrototypeGame/Utility/InputHelper.cpp 
        CMGT_PrototypeGame/Utility/InputHelper.hpp SFMLPE/Core/AnimationSprite.cpp SFMLPE/Core/AnimationSprite.hpp
        CMGT_PrototypeGame/Screens/MainMenu.cpp CMGT_PrototypeGame/Screens/MainMenu.hpp 
        CMGT_PrototypeGame/ScoreManager.cpp CMGT_PrototypeGame/ScoreManager.hpp CMGT_PrototypeGame/MainMenu/ScoreViewer.cpp 
        CMGT_PrototypeGame/MainMenu/ScoreViewer.hpp CMGT_PrototypeGame/MainMenu/ScoreCard.cpp CMGT_PrototypeGame/MainMenu/ScoreCard.hpp 
        CMGT_PrototypeGame/Fighting/Character.cpp CMGT_PrototypeGame/Fighting/Character.hpp
        CMGT_PrototypeGame/Button.cpp CMGT_PrototypeGame/Button.hpp CMGT_PrototypeGame/Fighting/FightManager.cpp 
        CMGT_PrototypeGame/Fighting/FightManager.hpp CMGT_PrototypeGame/Fighting/Arena.cpp CMGT_PrototypeGame/Fighting/Arena.hpp 
        CMGT_PrototypeGame/Selection.cpp CMGT_PrototypeGame/Selection.hpp CMGT_PrototypeGame/TextInput.cpp CMGT_PrototypeGame/TextInput.hpp 
        CMGT_PrototypeGame/Fighting/Enemy.cpp CMGT_PrototypeGame/Fighting/Enemy.hpp CMGT_PrototypeGame/Tweening/TweenManager.cpp 
        CMGT_PrototypeGame/Tweening/TweenManager.hpp CMGT_PrototypeGame/Tweening/Tween.cpp CMGT_PrototypeGame/Tweening/Tween.hpp 
        CMGT_PrototypeGame/Tweening/RectangleShapeSizeTween.cpp CMGT_PrototypeGame/Tweening/RectangleShapeSizeTween.hpp 
        CMGT_PrototypeGame/Tweening/RectPosTween.cpp CMGT_PrototypeGame/Tweening/RectPosTween.hpp CMGT_PrototypeGame/Attributes.hpp CMGT_PrototypeGame/Wellness.hpp)

target_link_libraries(SFMLPEngine PRIVATE effolkronium_random)
target_link_libraries(SFMLPEngine PRIVATE sfml-system sfml-graphics sfml-audio)

target_compile_features(SFMLPEngine PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SFMLPEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SFMLPEngine> $<TARGET_FILE_DIR:SFMLPEngine> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SFMLPEngine)
