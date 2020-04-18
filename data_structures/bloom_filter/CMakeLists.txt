set (CMAKE_CXX_STANDARD 11)
set(SOURCES thirdparty/MurmurHash3.cpp main.cpp)
add_executable (bloom_filter ${SOURCES})
