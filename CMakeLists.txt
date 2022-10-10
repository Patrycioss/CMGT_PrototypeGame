cmake_minimum_required(VERSION 3.19)
project(SFMLPEngine)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(SFMLPEngine main.cpp)

target_link_libraries(SFMLPEngine PRIVATE sfml-graphics)
target_compile_features(SFMLPEngine PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SFMLPEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SFMLPEngine> $<TARGET_FILE_DIR:SFMLPEngine> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SFMLPEngine)
