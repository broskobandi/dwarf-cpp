set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.30)

if(CMAKE_CXX_COMPILER STREQUAL "x86_64-w64-mingw32-g++")
	include(FetchContent)
	FetchContent_Declare(
		SDL2
		URL https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-mingw.zip
	)
	FetchContent_MakeAvailable(SDL2)
	set(WIN 1)
	set(SDL_DIR _deps/sdl2-src/x86_64-w64-mingw32)
endif()

project(dwarf)

file(GLOB SRC src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

if (WIN)
	target_include_directories(${PROJECT_NAME} PRIVATE build/${SDL_DIR}/include)
	target_link_directories(${PROJECT_NAME} PRIVATE build/${SDL_DIR}/lib)
	target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunused-result -Wconversion)

if (WIN)
	FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/win)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_BINARY_DIR}/${SDL_DIR}/bin/SDL2.dll
		${CMAKE_CURRENT_BINARY_DIR}/win/SDL2.dll
	)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe
		${CMAKE_CURRENT_BINARY_DIR}/win/${PROJECT_NAME}.exe
	)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		/usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll
		${CMAKE_CURRENT_BINARY_DIR}/win/libwinpthread-1.dll
	)
endif()
