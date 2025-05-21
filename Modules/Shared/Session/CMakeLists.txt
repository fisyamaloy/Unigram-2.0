set(TARGET Session)

set(SOURCE_FILES
    InMemoryTokenStorage.cpp
    DefaultSessionClock.cpp
    UserSession.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
       
target_link_libraries(${TARGET}
    PUBLIC Qt6::Core)
