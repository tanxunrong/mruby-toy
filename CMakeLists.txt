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
target_include_directories(skynet PUBLIC /usr/include/lua5.2 ${PROJECT_SOURCE_DIR}/skynet-src )

##target_compile_options(${PROJECT_NAME})
function(skynetso name)
    add_library(${name} SHARED service-src/service_${name}.c)
    target_include_directories(${name} PUBLIC ${PROJECT_SOURCE_DIR}/skynet-src /usr/include/lua5.2)
#    install(TARGETS ${name} LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib)
endfunction(skynetso)

skynetso(gate)
skynetso(harbor)
skynetso(logger)
skynetso(snlua)

target_link_libraries(skynet lua5.2 pthread m dl gate harbor logger snlua)
