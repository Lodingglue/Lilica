cmake_minimum_required(VERSION 3.20)
project(lilica)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(PROJECT_SOURCES
        src/main.cpp
        src/lua_helper.cpp
        src/imgui_binding.cpp
        src/gui_manager.cpp
)

add_executable(lilica ${PROJECT_SOURCES} ${IMGUI_SOURCES})

target_include_directories(lilica PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_PREFIX_PATH "D:/vcpkg/installed/x64-windows") # ye, fucked lol :sob:
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(lilica PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(lilica PRIVATE OpenGL::GL)

find_package(Lua REQUIRED)
target_include_directories(lilica PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(lilica PRIVATE ${LUA_LIBRARIES})

if(WIN32)
    target_link_libraries(lilica PRIVATE gdi32 opengl32)
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(lilica PRIVATE GL X11)
endif()

configure_file(${CMAKE_SOURCE_DIR}/script.lua ${CMAKE_BINARY_DIR}/script.lua COPYONLY)
