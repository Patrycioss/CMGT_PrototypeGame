cmake_minimum_required(VERSION 3.19)
project(SFMLPEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(SFML)
add_executable(SFMLPEngine 
        SFMLPE/Core/Game/main.cpp SFMLPE/Core/Game/Game.cpp SFMLPE/Core/Game/Game.hpp 
        SFMLPE/Core/Game/WindowSize.hpp MyGame.cpp SFMLPE/Core/Game/MyGame.hpp 
        SFMLPE/Core/Drawing/Sprite.cpp SFMLPE/Core/Drawing/Sprite.hpp SFMLPE/Core/Vector2.hpp
        SFMLPE/Core/EventSystem/EventManager.cpp SFMLPE/Core/EventSystem/EventManager.hpp 
        SFMLPE/Core/EventSystem/EventHandler.cpp SFMLPE/Core/EventSystem/EventHandler.hpp 
        SFMLPE/Core/Rectangle.hpp SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp 
        SFMLPE/Core/Rectangle.cpp SFMLPE/Core/GameObject.cpp SFMLPE/Core/GameObject.hpp
        SFMLPE/Core/ResourceManager.cpp SFMLPE/Core/ResourceManager.hpp SFMLPE/Core/Scene.cpp SFMLPE/Core/Scene.hpp)

target_link_libraries(SFMLPEngine PRIVATE sfml-graphics)
target_compile_features(SFMLPEngine PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SFMLPEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SFMLPEngine> $<TARGET_FILE_DIR:SFMLPEngine> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SFMLPEngine)
