# CMake generated Testfile for 
# Source directory: /home/matheus/Workspace/ElitesCppGithub/simelites-cpp
# Build directory: /home/matheus/Workspace/ElitesCppGithub/simelites-cpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SimpleTest "/usr/bin/mpiexec" "-n" "4" "/home/matheus/Workspace/ElitesCppGithub/simelites-cpp/build/ElitesCpp")
set_tests_properties(SimpleTest PROPERTIES  _BACKTRACE_TRIPLES "/home/matheus/Workspace/ElitesCppGithub/simelites-cpp/CMakeLists.txt;16;add_test;/home/matheus/Workspace/ElitesCppGithub/simelites-cpp/CMakeLists.txt;0;")
