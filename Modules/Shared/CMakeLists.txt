set(TARGET Shared)

add_library(${TARGET} INTERFACE)

add_subdirectory(Session)
add_subdirectory(Widgets)
