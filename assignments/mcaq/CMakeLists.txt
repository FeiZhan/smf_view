cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(mcaq)
add_executable(mcaq main.cpp MeshGui.h MeshGui.cpp SmfModel.h SmfModel.cpp Subdivision.h Subdivision.cpp Decimator.h Decimator.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLUI REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLUI_INCLUDE_DIRS} )
target_link_libraries(mcaq ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLUI_LIBRARY} )
