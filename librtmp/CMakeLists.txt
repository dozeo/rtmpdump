
option(BUILD_WITH_OPENSSL "Build librtmp with openssl" ON)

if(BUILD_WITH_OPENSSL)
	find_package(OpenSSL REQUIRED)
else()
	list(APPEND definitions "NO_CRYPTO")
endif()

option(BUILD_LIBRTMP_SHARED "Build librtmp as shared library" ON)

list(APPEND srcs
	"amf.c"
	"hashswf.c"
	"log.c"
	"parseurl.c"
	"rtmp.c")

list(APPEND public_hdrs
	"amf.h"
	"rtmp.h"
	"rtmp_shared.h"
	"log.h")

list(APPEND hdrs
	"bytes.h"
	"dh.h"
	"dhgroups.h"
	"handshake.h"
	"http.h"
	"rtmp_sys.h")

if(BUILD_LIBRTMP_SHARED)
	set(LIBTYPE SHARED)
	list(APPEND definitions "RTMP_EXPORT_DLL")
	list(APPEND public_definitions RTMP_IMPORT_DLL)
else()
	set(LIBTYPE STATIC)
endif()

if(WIN32)
	list(APPEND systemlibs
		"wsock32"
		"ws2_32"
		"winmm"
		)
endif()

add_library(librtmp ${LIBTYPE} ${srcs} ${public_hdrs} ${hdrs})
target_link_libraries(librtmp ${OPENSSL_LIBRARIES} ${systemlibs} ${ZLIB_LIBRARIES})

if(MSVC)
	list(APPEND definitions _CRT_SECURE_NO_WARNINGS)
endif()

list(APPEND include_dirs
	"${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND include_dirs
	"${OPENSSL_INCLUDE_DIR}")

if(ZLIB_FOUND)
	list(APPEND include_dirs
		"${ZLIB_INCLUDE_DIR}")
endif()

set_target_properties(librtmp PROPERTIES
	PUBLIC_HEADER "${public_hdrs}"
	INCLUDE_DIRECTORIES "${include_dirs}"
	COMPILE_DEFINITIONS "${definitions}"
	INTERFACE_COMPILE_DEFINITIONS "${public_definitions}"
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/.."
	PREFIX ""
	IMPORT_PREFIX ""
	)

install(TARGETS librtmp
	LIBRARY DESTINATION lib COMPONENT lib
	ARCHIVE DESTINATION lib COMPONENT lib
	RUNTIME DESTINATION bin COMPONENT bin
	PUBLIC_HEADER DESTINATION include/librtmp COMPONENT dev)
