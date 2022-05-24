cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME ModernOpenGL)


project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILE "${PROJECT_SOURCE_DIR}/source/src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILE "${PROJECT_SOURCE_DIR}/source/include/*.h")
add_executable(${PROJECT_NAME} 
	"${SRC_FILE}"
	"${INCLUDE_FILE}")
	
set_property(TARGET ${PROJECT_NAME} PROPERTY
VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

#	Add GLAD
target_include_directories(${PROJECT_NAME} PUBLIC
	"Dependencies/GLAD/include")
target_sources(${PROJECT_NAME} PUBLIC "Dependencies/GLAD/src/glad.cpp")

	
#	Add GLFW
set(GLFW3_ROOT "Dependencies/GLFW")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake")
find_package(GLFW3 REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW3_LIBRARY})


#	Add STB
target_include_directories(${PROJECT_NAME} PUBLIC 
	"Dependencies/STB")
	
# Add Maths LIbrary
set(MATHS_DIR "source/maths")
file(GLOB_RECURSE MATH_SOURCES "${MATHS_DIR}/*.cpp" "${MATHS_DIR}/*.h")
add_library(LibMaths STATIC EXCLUDE_FROM_ALL "${MATH_SOURCES}")
target_include_directories(LibMaths PRIVATE ${MATHS_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATHS_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC LibMaths)