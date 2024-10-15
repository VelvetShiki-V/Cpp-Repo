# 编译链接源文件形成可执行程序名
add_executable(oj_server oj_server.cc)

# 包含服务器进程本地头文件
include_directories(oj_server ${CMAKE_SOURCE_DIR}/oj_server/include)

# 引入外部pthread库(ctemplate需要使用到)
find_package(Threads REQUIRED)
set(PTHREAD_INCLUDE_DIRS /usr/include)
set(PTHREAD_LIBRARIES /usr/lib64/libpthread.so)
if(Threads_FOUND)
    message("pthread found")
    target_include_directories(oj_server PUBLIC ${PTHREAD_INCLUDE_DIRS})
    target_link_libraries(oj_server ${PTHREAD_LIBRARIES})
else()
    message("pthread not found")
endif(Threads_FOUND)

# 引入boost库
find_package(Boost REQUIRED)
set(BOOST_INCLUDE_DIRS /usr/include)
set(BOOST_LIBRARIES /usr/lib64/libboost_system.so)
if(Boost_FOUND)
    message ("Boost found")
    target_include_directories(oj_server PUBLIC ${BOOST_INCLUDE_DIRS})
    target_link_libraries(oj_server ${BOOST_LIBRARIES})
else()
    message (FATAL_ERROR "Cannot find pthread")
endif(Boost_FOUND)

# 引入ctemplate库
find_package(ctemplate REQUIRED)
set(CTEMPLATE_INCLUDE_DIRS /usr/include)
set(CTEMPLATE_LIBRARIES /usr/local/lib/libctemplate.a)
if(ctemplate_FOUND)
    message("ctemplate found")
    target_include_directories(oj_server PUBLIC ${CTEMPLATE_INCLUDE_DIRS})
    target_link_libraries(oj_server ${CTEMPLATE_LIBRARIES})
else()
    message("ctempalte not found")
endif(ctemplate_FOUND)


# 设置exe输出路径
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)