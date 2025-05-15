set(TARGET CustomWidgets)

set(SOURCE_FILES
    TitleBar.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
       
target_link_libraries(${TARGET}
    PUBLIC Qt6::Widgets)
