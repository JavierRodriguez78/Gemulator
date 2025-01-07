cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Gemunin)

# Establecer la versión de C++ a utilizar
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Buscar la librería SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Ruta a los archivos de ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/editor/libs/imgui)
set(IMGUI_FILES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Ruta a los archivos de gl3w
set(GL3W_DIR ${CMAKE_SOURCE_DIR}/core/libs/gl3w)
set(GL3W_FILES
    ${GL3W_DIR}/gl3w.c)

#Ruta a los archivos del editor
set(EDITOR_DIR ${CMAKE_SOURCE_DIR}/editor/src)
set(EDITOR_FILES
    ${EDITOR_DIR}/gui/mainWindow.cpp
    ${EDITOR_DIR}/gui/dialogLog.cpp
    ${EDITOR_DIR}/core/window.cpp)

#Ruta a los archivos del core
set(CORE_DIR ${CMAKE_SOURCE_DIR}/core/src)
set(CORE_FILES 
    ${CORE_DIR}/events/eventManager.cpp
    ${CORE_DIR}/logs/logEvent.cpp
    ${CORE_DIR}/logs/logger.cpp
    ${CORE_DIR}/graphics/graphic.cpp)

#Ruta a los archivos del emulador nes
set(NES_DIR ${CMAKE_SOURCE_DIR}/nintendo/nes/src)
set(NES_FILES
    ${NES_DIR}/core/nes.cpp
    ${NES_DIR}/bus/bus.cpp
    ${NES_DIR}/bus/pBus.cpp
    ${NES_DIR}/cpu/cpu.cpp
    ${NES_DIR}/mappers/mapper.cpp
    ${NES_DIR}/mappers/mapperNROM.cpp
    ${NES_DIR}/cartridge/cartridge.cpp)

# Incluir los directorios de cabeceras de ImGui y gl3w
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ${GL3W_DIR} ${EDITOR_DIR} ${CORE_DIR} ${NES_DIR})

# Añadir los archivos fuente de tu proyecto
add_executable(Gemunin main.cpp ${IMGUI_FILES} ${GL3W_FILES} ${EDITOR_FILES} ${CORE_FILES} ${NES_FILES})

# Enlazar SDL2 y OpenGL a tu proyecto
target_link_libraries(Gemunin ${SDL2_LIBRARIES} -lGL)