cmake_minimum_required(VERSION 3.29.0)

project(NEW_UI_FOR_MESSENGER)

# Global settings. Should probably be moved to a separate file later.
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS off)

# For those VSCode users
set(EXPORT_COMPILE_COMMANDS TRUE)

# Set warnings level higher and force treating them as errors.
# GCC TBD
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(TARGET new_ui_for_messenger)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
        main.cpp)

if (WIN32)
    list(APPEND EXTRA_LIBS ws2_32 wsock32 winmm dwmapi)
elseif (UNIX AND NOT APPLE)
    list(APPEND EXTRA_LIBS xcb)
endif ()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_add_resources(RESOURCE_FILES Assets/resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RESOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
        View
        Modules
        ${EXTRA_LIBS}
)

target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

add_subdirectory(Modules)
add_subdirectory(View)
