file(GLOB_RECURSE tests *.cpp *.hpp mocks/*)
add_executable(StixxMicroTests ${tests})

target_include_directories(StixxMicroTests
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
		
if(WIN32)
	SET(gtest_force_shared_crt on CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.") 
endif()
add_subdirectory(googletest)

target_link_libraries(StixxMicroTests Stixx gtest gmock)
install(TARGETS StixxMicroTests DESTINATION bin)

