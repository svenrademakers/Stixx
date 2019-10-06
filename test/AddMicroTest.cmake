macro(AddMicroTest target)
    set (extra_macro_args ${ARGN})
	# check if sources files are passed..
	list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} EQUAL 0)
        message (FATAL_ERROR "no source files passed to AddMicroTest macro")
	endif ()

	add_executable(${target}_MicroTests ${CURR_DIR}/test.cpp ${extra_macro_args})
	set_target_properties(${target}_MicroTests PROPERTIES CXX_STANDARD 17 FOLDER ${target})
	
	target_include_directories(${target}_MicroTests
		PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
	
	target_link_libraries(${target}_MicroTests ${target} gtest gmock)
	install(TARGETS ${target}_MicroTests DESTINATION bin)	
endmacro()

macro(AddBenchmark target)
    set (extra_macro_args ${ARGN})
	# check if sources files are passed..
	list(LENGTH extra_macro_args num_extra_args)
    if (${num_extra_args} EQUAL 0)
        message (FATAL_ERROR "no source files passed to AddMicroTest macro")
	endif ()

	add_executable(${target}_Benchmark ${extra_macro_args})
	set_target_properties(${target}_Benchmark PROPERTIES CXX_STANDARD 17 FOLDER ${target})

	target_include_directories(${target}_Benchmark
		PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
	
	target_link_libraries(${target}_Benchmark ${target} benchmark_main )
	if(WIN32)
			target_link_libraries(${target}_Benchmark Shlwapi )
	endif()

	install(TARGETS ${target}_Benchmark DESTINATION bin)	
endmacro()