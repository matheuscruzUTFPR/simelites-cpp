cmake_minimum_required(VERSION 3.1.0)
project(ElitesCpp VERSION 1.0.0)

add_executable(ElitesCpp ./src/main.cpp)

# Require MPI for this project:
find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(MPI_INCLUDE_PATH)
target_link_libraries(ElitesCpp ${MPI_LIBRARIES})

#Teste de execução:
enable_testing()
add_test(SimpleTest ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${CMAKE_CURRENT_BINARY_DIR}/ElitesCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED mpi system log)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(ElitesCpp ${Boost_LIBRARIES})


#find_package(PostgreSQL REQUIRED)
#include_directories(${PostgreSQL_INCLUDE_DIRS})
#target_link_libraries(ElitesCpp ${PostgreSQL_LIBRARIES})
#target_link_libraries(ElitesCpp PRIVATE PostgreSQL::PostgreSQL)



include(CTest)


enable_testing()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
