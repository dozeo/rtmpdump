find_package(OpenSSL REQUIRED)

option(BUILD_LIBRTMP_SHARED "Build librtmp as shared library" ON)

list(APPEND srcs
	"amf.c"
	"hashswf.c"
#	"librtmp.3"
#	"librtmp.pc.in"
	"log.c"
	"parseurl.c"
	"rtmp.c"
)

list(APPEND public_hdrs
	"amf.h"
	"rtmp.h")

list(APPEND hdrs
	"bytes.h"
	"dh.h"
	"dhgroups.h"
	"handshake.h"
	"http.h"
	"log.h"
	"rtmp_sys.h")

if(BUILD_LIBRTMP_SHARED)
	set(LIBTYPE SHARED)
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

set_target_properties(librtmp PROPERTIES
	PUBLIC_HEADERS "${public_hdrs}"
	INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR};${OPENSSL_INCLUDE_DIR};${ZLIB_INCLUDE_DIR}"
	COMPILE_DEFINITIONS "${definitions}"
#	INTERFACE_COMPILE_DEFINITIONS "${interface_definitions}"
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/.."
	)
