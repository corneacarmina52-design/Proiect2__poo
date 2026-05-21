cmake_minimum_required(VERSION 3.15)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Setăm numele proiectului exact cum se numește folderul și executabilul tău
project(POO VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DESCARCARE AUTOMATA SFML 3 ---
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)

# Dezactivăm componentele inutile ca să nu se compileze exemplele lor defecte
set(SFML_BUILD_TOOLS FALSE CACHE INTERNAL "")
set(SFML_BUILD_AUDIO FALSE CACHE INTERNAL "")
set(SFML_BUILD_NETWORK FALSE CACHE INTERNAL "")
set(SFML_BUILD_DOC FALSE CACHE INTERNAL "")
set(SFML_BUILD_EXAMPLES FALSE CACHE INTERNAL "")

FetchContent_MakeAvailable(SFML)

set(SOURCES
    "src/main.cpp"
    "src/Game.cpp"
    "src/Entity.cpp"
    "src/Enemy.cpp"
    "src/WeaponStrategy.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/hpp")

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
endif()