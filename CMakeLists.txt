cmake_minimum_required(VERSION 2.8)

project(rtmpdump)

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

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/zlib)
	set(BUILD_ZLIB_EXAMPLE CACHE BOOL OFF)
	set(BUILD_MINIGZIP CACHE BOOL OFF)
	add_subdirectory(vendor/zlib)
endif()

add_subdirectory(librtmp)

if(BUILD_RTMP_EXECUTABLES AND NOT WIN32)
	if(MSVC AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/wingetopt)
		add_subdirectory(vendor/wingetopt)
		list(APPEND systemlibs wingetopt)
	endif()

	add_executable(rtmpdump rtmpdump.c)
	target_link_libraries(rtmpdump librtmp ${systemlibs})

	#add_executable(rtmpsrv rtmpsrv.c)
	#target_link_libraries(rtmpsrv librtmp ${systemlibs})

	add_executable(rtmpsuck rtmpsuck.c)
	target_link_libraries(rtmpsuck librtmp ${systemlibs})
endif()