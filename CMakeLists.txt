cmake_minimum_required(VERSION 3.10)
project(mp3-player VERSION 1.0.0 LANGUAGES CXX)

# set(PATCH_VERSION 0 CACHE STRING "Package patch version")
# set(SFML_BUILD_WINDOW OFF CACHE BOOL "Build SFML window module" FORCE)
# set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "Build SFML graphics module" FORCE)
# set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build SFML network module" FORCE)
# set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build SFML examples" FORCE)
# set(SFML_BUILD_DOC OFF CACHE BOOL "Build SFML documentation" FORCE)

# Опции (опционально)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(mp3-player
    src/main/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/icon.ico
)

qt_add_qml_module(mp3-player
    URI mp3player
    VERSION 1.0
    QML_FILES
        qml/Main.qml
    RESOURCES
        assets/cover-placeholder.jpeg
    SOURCES
        include/presentation/Client.hpp
        src/lib/Client.cpp
    
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Директории с заголовками
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Список исходников библиотеки
file(GLOB LIB_SOURCES "src/lib/*.cpp")

# add_executable(mp3-player "src/main/main.cpp")

# Для приложения тоже нужны публичные заголовки библиотеки
target_include_directories(mp3-player PRIVATE ${INCLUDE_DIR})
# target_link_libraries(mp3-player PRIVATE SFML::Audio)
target_sources(mp3-player PRIVATE ${LIB_SOURCES})

target_link_libraries(mp3-player
    PRIVATE Qt6::Quick Qt6::Core Qt6::Multimedia SFML::Audio
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mp3-player)

install(TARGETS mp3-player
    RUNTIME DESTINATION bin
)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION .)

set_target_properties(mp3-player PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appappseabattle
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mp3-player
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
