CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(antisocial)
SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "1")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

file(GLOB SOURCES src/*.cpp src/*.c src/.cc src/*.h src/*.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_definitions(-DANTISOCIAL_EXPORT -DGLEW_STATIC -DGLEW_NO_GLU)
include_directories(${PROJECT_SOURCE_DIR}/external)
link_directories(${PROJECT_SOURCE_DIR}/lib)

if (UNIX)
target_link_libraries(${PROJECT_NAME} GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt pthread dl)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} glew32 glfw3 opengl32 user32 kernel32 glew32.dll)
endif (WIN32)
