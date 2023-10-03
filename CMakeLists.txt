cmake_minimum_required(VERSION 3.18)

project(c-audio C)

add_executable(${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/writeWav.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/generateSine.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/writeCSV.c
)
