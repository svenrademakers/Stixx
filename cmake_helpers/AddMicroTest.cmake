set(CURR_DIR ${CMAKE_CURRENT_LIST_DIR})  
#include(${CURR_DIR}/GTest.cmake)

macro(AddMicroTest target)
    set (extra_macro_args ${ARGN})
	# check if sources files are passed..
	list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} EQUAL 0)
        message (FATAL_ERROR "no source files passed to AddMicroTest macro")
	endif ()
	
	add_executable(${target}_MicroTests ${CURR_DIR}/test.cpp ${extra_macro_args})
	target_include_directories(${target}_MicroTests
		PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
			
	if(WIN32)
		SET(gtest_force_shared_crt on CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.") 
	endif()
	
	target_link_libraries(${target}_MicroTests ${target} gtest gmock)
	install(TARGETS ${target}_MicroTests DESTINATION bin)	
endmacro()