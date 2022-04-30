cmake_minimum_required(VERSION 3.16)
project(Prog__Syst�me_et_R�seau C)
project(solver LANGUAGES CXX)
#important

set(CMAKE_C_STANDARD 11)



add_executable(test src/ex1.c)

add_executable(donutspin cool/donut.c)
add_executable(testPIc src/test-pi.c)
add_executable(testPI2 src/test-pi2.c)
add_executable(testPI3 src/test-pi3.c)
add_executable(testFibo1 src/test-fibo.c)
add_executable(testFibo3 src/test-fibo3.c)
add_executable(testFibo2 src/testFibo2.c)
add_executable(lab9 src/lab9.c)
add_executable(assignment02 src/assignment02/assignment2.c)
add_executable(assig-v2 src/assignment02/asig-v2.c)



find_package(OpenMP)
find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(testPIc PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testPI2 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testPI3 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo1 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo2 PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(testFibo3 PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(testPIc PROPERTIES VERSION 1.0)
set_target_properties(testPI2 PROPERTIES VERSION 1.0)
target_link_libraries(lab9 PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(lab9 PROPERTIES VERSION 1.0)
target_link_libraries(assignment02 PRIVATE OpenMP::OpenMP_CXX)
#target_link_libraries(assignment02 PRIVATE MPI_C)
set_target_properties(assignment02 PROPERTIES VERSION 1.0)
set_target_properties(assig-v2 PROPERTIES VERSION 1.0)
include(GNUInstallDirs)


set(CMAKE_BUILD_TYPE Release)
