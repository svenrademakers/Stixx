cmake_minimum_required(VERSION 3.10.0)
project(stixx)

set(STIXX_MAJOR_VERSION 0)
set(STIXX_MINOR_VERSION 2)
set(STIXX_PATCH_VERSION 0)
set(STIXX_VERSION ${STIXX_MAJOR_VERSION}.${STIXX_MINOR_VERSION}.${STIXX_PATCH_VERSION})
message(STATUS "Stixx version: ${STIXX_VERSION}")

option(STIXX_TESTS "Build micro and benchmark tests" ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file(GLOB_RECURSE sources sources/*.cpp sources/*.hpp sources/*.h)

add_library(Stixx ${sources})
set_target_properties(Stixx PROPERTIES
	OUTPUT_NAME Stixx
	DEBUG_POSTFIX -d
	VERSION ${STIXX_VERSION}
	SOVERSION ${STIXX_MAJOR_VERSION}
	FOLDER Stixx
)

target_include_directories(Stixx
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>
 		$<INSTALL_INTERFACE:stixx>)

install(DIRECTORY include interfaces DESTINATION include)
install(TARGETS Stixx
		EXPORT 	Stixx-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)
install(EXPORT Stixx-targets FILE Stixx-config.cmake DESTINATION lib/cmake/Stixx)

if(STIXX_TESTS)
	add_subdirectory(test)
endif()
