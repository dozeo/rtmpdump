cmake_minimum_required(VERSION 2.8)

project(rtmpdump)
set(version "v2.4")

option(BUILD_RTMP_EXECUTABLES "Build RTMP executables" ON)

# simplify output directories on platforms with multiple configurations
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(WIN32)
	if(NOT TARGET zlib)
		set(BUILD_ZLIB_EXAMPLE CACHE BOOL OFF)	
		set(BUILD_MINIGZIP CACHE BOOL OFF)
		add_subdirectory(vendor/zlib)
	endif()

	set(ZLIB_LIBRARIES zlib)
else()
	find_package(ZLIB REQUIRED)
endif()

add_subdirectory(librtmp)

if(BUILD_RTMP_EXECUTABLES AND NOT WIN32)
	set(definitions "RTMPDUMP_VERSION=\"${version}\"")
	if(MSVC AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/wingetopt)
		add_subdirectory(vendor/wingetopt)
		list(APPEND systemlibs wingetopt)
	endif()

	add_executable(rtmpdump rtmpdump.c)
	set_target_properties(rtmpdump PROPERTIES COMPILE_DEFINITIONS ${definitions})
	target_link_libraries(rtmpdump librtmp ${systemlibs})

	find_package(Threads REQUIRED)
	add_executable(rtmpsrv rtmpsrv.c thread.c)
	set_target_properties(rtmpsrv PROPERTIES COMPILE_DEFINITIONS ${definitions})
	target_link_libraries(rtmpsrv librtmp ${systemlibs} ${CMAKE_THREAD_LIBS_INIT})

	add_executable(rtmpsuck rtmpsuck.c thread.c)
	set_target_properties(rtmpsuck PROPERTIES COMPILE_DEFINITIONS ${definitions})
	target_link_libraries(rtmpsuck librtmp ${systemlibs} ${CMAKE_THREAD_LIBS_INIT})
endif()
