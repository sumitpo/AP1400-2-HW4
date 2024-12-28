find ./include -name "*.h" -exec clang-format -i {} \;
find ./src -name "*.cpp" -exec clang-format -i {} \;
mkdir build
(cd build; cmake ..; make)
