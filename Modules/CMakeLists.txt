set(TARGET Modules)

set(SOURCE_FILES
    Auth/Core/LoginPasswordAuth.cpp
    Auth/Core/PhoneNumberAuth.cpp
    Auth/Core/QRCodeAuth.cpp

    Auth/Ui/LoginPasswordUI.cpp
    Auth/Ui/PhoneNumberUI.cpp
    Auth/Ui/QRCodeUI.cpp
)
    
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Auth)
       
target_link_libraries(${TARGET}
    PUBLIC Qt6::Widgets)

add_subdirectory(Shared)
