cmake_minimum_required(VERSION 3.19)
project(SFMLPEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(SFML)
add_executable(SFMLPEngine
        CMGT_PrototypeGame/main.cpp
        SFMLPE/Core/Sprite.cpp SFMLPE/Core/Sprite.hpp
        SFMLPE/Core/EventSystem/EventManager.cpp SFMLPE/Core/EventSystem/EventManager.hpp 
        SFMLPE/Core/EventSystem/EventHandler.cpp SFMLPE/Core/EventSystem/EventHandler.hpp 
        SFMLPE/Core/Rectangle.hpp SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp 
        SFMLPE/Core/Rectangle.cpp SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp
        SFMLPE/Core/ResourceManager.cpp SFMLPE/Core/ResourceManager.hpp SFMLPE/Core/Scene.cpp test_example/TestSprite.cpp
        SFMLPE/Core/Scene.hpp SFMLPE/Core/Game.cpp SFMLPE/Core/Game.hpp CMGT_PrototypeGame/CMGT_PrototypeGame.cpp CMGT_PrototypeGame/CMGT_PrototypeGame.hpp SFMLPE/SFMLPE.hpp CMGT_PrototypeGame/Utility/InputHelper.cpp CMGT_PrototypeGame/Utility/InputHelper.hpp SFMLPE/Core/AnimationSprite.cpp SFMLPE/Core/AnimationSprite.hpp CMGT_PrototypeGame/AnimationTest.cpp CMGT_PrototypeGame/AnimationTest.hpp CMGT_PrototypeGame/Screens/MainMenu.cpp CMGT_PrototypeGame/Screens/MainMenu.hpp CMGT_PrototypeGame/IO/Buttons/Button.cpp CMGT_PrototypeGame/IO/Buttons/Button.hpp CMGT_PrototypeGame/IO/Buttons/StartButton.cpp CMGT_PrototypeGame/IO/Buttons/StartButton.hpp CMGT_PrototypeGame/IO/Buttons/ExitButton.cpp CMGT_PrototypeGame/IO/Buttons/ExitButton.hpp CMGT_PrototypeGame/Data/ScoreManager.cpp CMGT_PrototypeGame/Data/ScoreManager.hpp CMGT_PrototypeGame/MainMenu/ScoreViewer.cpp CMGT_PrototypeGame/MainMenu/ScoreViewer.hpp CMGT_PrototypeGame/MainMenu/ScoreCard.cpp CMGT_PrototypeGame/MainMenu/ScoreCard.hpp)

target_link_libraries(SFMLPEngine PRIVATE sfml-graphics)
target_compile_features(SFMLPEngine PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SFMLPEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SFMLPEngine> $<TARGET_FILE_DIR:SFMLPEngine> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SFMLPEngine)
