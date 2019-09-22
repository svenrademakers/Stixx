include(../cmake_helpers/AddMicroTest.cmake)
file(GLOB_RECURSE tests *.cpp *.hpp mocks/*)
AddMicroTest(Stixx ${tests})

