cmake_minimum_required(VERSION 3.16)
project(Prog__Syst�me_et_R�seau C)
project(solver LANGUAGES CXX)
#important

set(CMAKE_C_STANDARD 11)



add_executable(test CM1/ex1.c)

add_executable(donutspin cool/donut.c)
add_executable(testPIc CM1/test-pi.c)
add_executable(testPI2 CM1/test-pi2.c)
add_executable(testPI3 CM1/test-pi3.c)
add_executable(testFibo1 CM1/test-fibo.c)
add_executable(testFibo3 CM1/test-fibo3.c)
add_executable(testFibo2 CM1/testFibo2.c)



find_package(OpenMP)
target_link_libraries(testPIc PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testPI2 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testPI3 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo1 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo2 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo3 PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(testPIc PROPERTIES VERSION 1.0)
set_target_properties(testPI2 PROPERTIES VERSION 1.0)
include(GNUInstallDirs)


set(CMAKE_BUILD_TYPE Release)
