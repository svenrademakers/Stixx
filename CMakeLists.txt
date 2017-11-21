cmake_minimum_required(VERSION 3.8.2)

set(STIXX_MAJOR_VERSION 0)
set(STIXX_MINOR_VERSION 1)
set(STIXX_PATCH_VERSION 0)
set(STIXX_VERSION ${STIXX_MAJOR_VERSION}.${STIXX_MINOR_VERSION}.${STIXX_PATCH_VERSION})
message(STATUS "Stixx version: ${STIXX_VERSION}")

option(STIXX_GLFW "Build glfw implementation for window interfaces" OFF)
option(STIXX_ASSIMP "Build Assimp implementation for AssetLoader interfaces" OFF)
option(STIXX_MICROTESTS "Build micro tests" ON)

file(GLOB_RECURSE utils_sources utils/*.cpp utils/*.hpp)
file(GLOB_RECURSE infra_sources infra/*.cpp infra/*.hpp)
file(GLOB_RECURSE platform_sources platform/*.cpp platform/*.hpp)
file(GLOB_RECURSE interfaces_sources interfaces/*.cpp interfaces/*.hpp)
file(GLOB_RECURSE interactors_sources interactors/*.cpp interactors/*.hpp)
source_group("utils" FILES ${utils_sources})
source_group("infra" FILES ${infra_sources})
source_group("platform" FILES ${platform_sources})
source_group("interfaces" FILES ${interfaces_sources})
source_group("interactors" FILES ${interactors_sources})
set(sources ${utils_sources} ${infra_sources} ${platform_sources} ${interfaces_sources} ${interactors_sources})

if(STIXX_ASSIMP)
	set(assimp_sources ${CMAKE_CURRENT_SOURCE_DIR}/assimp/src/AssetImporterAssimp.cpp)
	set(assimp_headers ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include/AssetImporterAssimp.hpp)
	source_group("assimp" FILES ${assimp_headers} ${assimp_sources})
	list(APPEND sources ${assimp_headers} ${assimp_sources})
endif()

if(STIXX_GLFW)
	add_subdirectory(glfw/glfw)
	set(glfw_headers ${CMAKE_CURRENT_SOURCE_DIR}/glfw/InputGlfw.hpp ${CMAKE_CURRENT_SOURCE_DIR}/glfw/WindowGlfw.hpp)
	set(glfw_sources ${CMAKE_CURRENT_SOURCE_DIR}/glfw/InputGlfw.cpp ${CMAKE_CURRENT_SOURCE_DIR}/glfw/WindowGlfw.cpp)
	source_group("assimp" FILES ${glfw_headers} ${glfw_sources})
	list(APPEND sources ${glfw_headers} ${glfw_sources})
endif()
	
add_subdirectory(glm)

add_library(Stixx ${sources})

set_target_properties(Stixx PROPERTIES
	OUTPUT_NAME Stixx
	DEBUG_POSTFIX -d
	VERSION ${STIXX_VERSION}
	SOVERSION ${STIXX_MAJOR_VERSION}
	FOLDER stixx
)

set_property(TARGET Stixx PROPERTY CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

target_include_directories(Stixx
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 		$<INSTALL_INTERFACE:stixx>)
			
target_link_libraries(Stixx glm)

if (STIXX_GLFW)
	target_include_directories(Stixx PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glfw>)
	target_link_libraries(Stixx glfw)
endif()

install(DIRECTORY include interfaces DESTINATION include)

install(TARGETS Stixx
		EXPORT 	Stixx-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT Stixx-targets FILE Stixx-config.cmake DESTINATION lib/cmake/Stixx)

if(STIXX_ASSIMP)
	include(assimp/assimp.cmake)
endif()

if(STIXX_MICROTESTS)
	add_subdirectory(test)
endif()
