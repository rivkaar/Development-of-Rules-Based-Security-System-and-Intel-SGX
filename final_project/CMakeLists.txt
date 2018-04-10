project(decompile CXX)
cmake_minimum_required(VERSION 3.6)

find_package(Threads)

include_directories(SYSTEM
	"C:\\retdec-pz\\retdec-cpp\\include"
)
add_executable(decompile decompile.cpp)
target_link_libraries(decompile
	"C:\\retdec-pz\\retdec-cpp\\build\\src\\retdec\\Release\\retdec.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_filesystem-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_regex-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_system-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_thread-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_chrono-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_date_time-vc140-mt-1_59.lib"
	"C:\\Boost\\lib64-msvc-14.0\\libboost_atomic-vc140-mt-1_59.lib"
	"C:\\retdec-pz\\retdec-cpp\\build\\third_party\\src\\cpp-netlib-build\\libs\\network\\src\\Release\\cppnetlib-uri.lib"
	"C:\\retdec-pz\\retdec-cpp\\build\\third_party\\src\\cpp-netlib-build\\libs\\network\\src\\Release\\cppnetlib-client-connections.lib"
	"C:\\retdec-pz\\retdec-cpp\\build\\third_party\\src\\json-cpp-build\\src\\lib_json\\Release\\jsoncpp.lib"
	"C:\\OpenSSL-Win64\\lib64\\libeay32MT.lib"
	"C:\\OpenSSL-Win64\\lib64\\ssleay32MT.lib"
	${CMAKE_THREAD_LIBS_INIT}
)
