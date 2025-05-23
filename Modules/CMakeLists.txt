set(TARGET Modules)

set(SOURCE_FILES
    Auth/Core/LoginPasswordAuth.cpp
    Auth/Core/PhoneNumberAuth.cpp
    Auth/Core/QRCodeAuth.cpp

    Auth/Ui/LoginPasswordPage.cpp
    Auth/Ui/PhoneNumberPage.cpp
    Auth/Ui/QRCodePage.cpp

    Registration/Ui/RegistrationPage.cpp
    
    Chat/Include/Chat/ChatPage.h
    Chat/ChatPage.cpp

    Chat/List/Core/Models/ChatListItem.h
    Chat/List/Core/Models/ChatListModel.h
    Chat/List/Core/Models/ChatListModel.cpp
    
    Chat/List/Ui/ChatListWidget.h
    Chat/List/Ui/ChatItemDelegate.h
    Chat/List/Ui/ChatItemDelegate.cpp
    Chat/List/Ui/ChatListWidget.cpp
)
    
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Auth ${CMAKE_CURRENT_SOURCE_DIR}/Chat/Include ${CMAKE_CURRENT_SOURCE_DIR}/Registration)
       
target_link_libraries(${TARGET}
    PUBLIC Qt6::Widgets)

add_subdirectory(Shared)
