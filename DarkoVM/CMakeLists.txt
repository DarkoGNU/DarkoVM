# CMakeList.txt : CMake project for DarkoVM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DarkoVM "DarkoVM.cpp"  "Parser.cpp" "Parser.h" "Code.cpp" "Code.h" "AssemblyMap.cpp" "AssemblyMap.h")

# TODO: Add tests and install targets if needed.
set_target_properties(
    DarkoVM PROPERTIES
    CXX_STANDARD 20)
