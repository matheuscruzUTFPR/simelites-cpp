# CMake generated Testfile for 
# Source directory: /home/matheus/Workspace/ElitesCpp
# Build directory: /home/matheus/Workspace/ElitesCpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SimpleTest "/usr/bin/mpiexec" "-n" "4" "/home/matheus/Workspace/ElitesCpp/build/ElitesCpp")
set_tests_properties(SimpleTest PROPERTIES  _BACKTRACE_TRIPLES "/home/matheus/Workspace/ElitesCpp/CMakeLists.txt;15;add_test;/home/matheus/Workspace/ElitesCpp/CMakeLists.txt;0;")
