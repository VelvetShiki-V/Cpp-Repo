# 编译链接源文件形成可执行程序名
add_executable(compile_run_svr compile_run.cc)

# 包含服务器进程本地头文件
include_directories(${CMAKE_SOURCE_DIR}/compile_server/include)

# 引入外部json库
find_package(jsoncpp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
set(JSONCPP_INCLUDE_DIRS /usr/include)
set(JSONCPP_LIBRARIES /usr/lib64/libjsoncpp.so)
if(jsoncpp_FOUND)
    message("jsoncpp include dir path -> ${JSONCPP_INCLUDE_DIRS}")
    message("jsoncpp library dir path -> ${JSONCPP_LIBRARIES}")
    target_include_directories(compile_run_svr PUBLIC ${JSONCPP_INCLUDE_DIRS})
    target_link_libraries(compile_run_svr ${JSONCPP_LIBRARIES})
else()
    message("Jsoncpp package not found")
endif(jsoncpp_FOUND)

include_directories(${JSONCPP_INCLUDE_DIRS})

# 引入外部pthread库(httplib需要使用到)
find_package(Threads REQUIRED)
set(PTHREAD_INCLUDE_DIRS /usr/include)
set(PTHREAD_LIBRARIES /usr/lib64/libpthread.so)
if(Threads_FOUND)
    message("pthread found")
    target_include_directories(compile_run_svr PUBLIC ${PTHREAD_INCLUDE_DIRS})
    target_link_libraries(compile_run_svr ${PTHREAD_LIBRARIES})
else()
    message("pthread not found")
endif(Threads_FOUND)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)