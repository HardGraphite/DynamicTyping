cmake_minimum_required(VERSION 3.18)

project(DynamicTyping)
set(TargetName hgdt)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_VISIBILITY_PRESET hidden)

include_directories(include)

aux_source_directory(src Srcs)
add_library(${TargetName} ${Srcs})
add_compile_definitions(_GHL_BUILD_DL)

aux_source_directory(test TestSrcs)
foreach(_tst_src IN LISTS TestSrcs)
    get_filename_component(_tst_target ${_tst_src} NAME_WE)
    add_executable(${_tst_target} ${_tst_src})
    target_link_libraries(${_tst_target} ${TargetName})
    add_test(NAME "test-${_tst_target}" COMMAND ${_tst_target})
endforeach()
enable_testing()
