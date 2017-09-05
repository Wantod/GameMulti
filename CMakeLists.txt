cmake_minimum_required(VERSION 2.8)
project(noname)

# DEFINE NAME
set(CLIENT_NAME client)
set(SERVER_NAME server)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
else()
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -std=c++1y")
	set(GLAD_LIBRARIES dl)
endif()

# librairie
add_subdirectory(external/glew)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/Simple-OpenGL-Image-Library)
add_subdirectory(external/freetype-2.6)
add_subdirectory(external/openal-soft)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

include_directories(
	external/glfw/include/
	external/glfw/include/GLFW/
	external/glm/
	external/glew/include/
	external/freetype-2.6/include/
	external/Simple-OpenGL-Image-Library/src/
	external/openal-soft/OpenAL32/Include/
)

# Trouver les fichier
file (
	GLOB_RECURSE
	source_files_ini
	src/ini/*
)

file (
	GLOB_RECURSE
	source_files_client
	src/client/*
)


file (
	GLOB_RECURSE
	source_files_server
	src/server/*
)

#
add_executable(
	${CLIENT_NAME}
	${source_files_ini}
	${source_files_client}
)

set(LIBS libglew_static glfw ${GLFW_LIBRARIES} SOIL freetype)
target_link_libraries(${CLIENT_NAME} ${LIBS})


add_executable(
	${SERVER_NAME}
	${source_files_ini}
	${source_files_server}
)
