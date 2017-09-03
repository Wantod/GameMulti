cmake_minimum_required(VERSION 2.8)
project(noname)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
else()
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -std=c++1y")
	set(GLAD_LIBRARIES dl)
endif()

file (
	GLOB_RECURSE
	source_files_client
	src/client/*
)

file (
	GLOB_RECURSE
	source_files_ini
	src/ini/*
)

file (
	GLOB_RECURSE
	source_files_server
	src/server/*
)


add_executable(
	client
	${source_files_ini}
	${source_files_client}
)

add_executable(
	server
	${source_files_ini}
	${source_files_server}
)
