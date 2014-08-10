project(mruby-toy)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_definitions( -Wall -g )

add_library(mruby STATIC IMPORTED)
set_target_properties(mruby PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/mruby/build/host/lib/libmruby.a )
include_directories( ${PROJECT_SOURCE_DIR}/mruby/include )
target_link_libraries(${PROJECT_NAME} mruby m )
target_compile_options(${PROJECT_NAME} PUBLIC -std=c99)

aux_source_directory(./skynet-src SKYNET_SRC_LIST)
add_executable(skynet ${SKYNET_SRC_LIST})

#if(APPLE)
#    message(STATUS "Apple OS")
#    set(LUA_INCLUDE_DIR /usr/local/Cellar/lua52/5.2.3/include)
#    set(LUA_LIB lua)
#    #link_directories(/usr/local/Cellar/lua52/5.2.3/lib)
#endif(APPLE)

#if(LINUX)
    message(STATUS "Linux OS")
    set(LUA_INCLUDE_DIR /usr/include/lua5.2)
    set(LUA_LIB lua5.2)
#endif(LINUX)

target_include_directories(skynet PUBLIC ${LUA_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/skynet-src )

function(skynetso name)
    add_library(${name} SHARED ${PROJECT_SOURCE_DIR}/service-src/service_${name}.c)
    target_include_directories(${name} PUBLIC ${PROJECT_SOURCE_DIR}/skynet-src ${LUA_INCLUDE_DIR})
endfunction(skynetso)

skynetso(gate)
skynetso(harbor)
skynetso(logger)
skynetso(snlua)
#skynetso(toy)

target_link_libraries(skynet ${LUA_LIB} pthread m dl gate harbor logger snlua)
