set(TARGET View)

set(SOURCE_FILES
    MainWindow.cpp    
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_link_libraries(${TARGET}
    PUBLIC 
        Qt6::Widgets
        Modules
        CustomWidgets
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR})
