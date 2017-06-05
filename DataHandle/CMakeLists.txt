include(cotire)

cmake_minimum_required(VERSION 2.8) 

project(DataHandle, CXX)

IF (NOT WIN32)
	add_compile_options(-std=c++11 -stdlib=libc++)
ENDIF()

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.8")

AUX_SOURCE_DIRECTORY(src LIB_SOURCES)
set(LIB_INCLUDES "include" "include/DataHandle" "include/DataHandle/internal")

include_directories(${LIB_INCLUDES})
add_library(DataHandle STATIC ${LIB_SOURCES})

set_target_properties(DataHandle PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "include/DataHandle/internal/PrefixHeader.pch")
cotire(DataHandle)

add_custom_command(TARGET DataHandle POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    	${CMAKE_CURRENT_SOURCE_DIR}/include 
						${CMAKE_CURRENT_BINARY_DIR}/include)
