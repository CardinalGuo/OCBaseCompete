# Install script for directory: /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/lib/libcommon.so.1.0.0"
    "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/lib/libcommon.so.1"
    "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/lib/libcommon.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcommon.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/lib/libcommon.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/conf" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/conf/ini.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/defs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/io" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/io/io.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/io" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/io/roll_select_dir.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/io" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/io/select_dir.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lang" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/lang/bitmap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lang" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/lang/mutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lang" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/lang/serializable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lang" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/lang/string.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/log" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/log/log.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/math" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/math/md5.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/math" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/math/random_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/math" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/math/regex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/console_reporter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/histogram_snapshot.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/log_reporter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/metric.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/metrics.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/metrics_registry.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/reporter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/reservoir.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/sampler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/snapshot.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/timer_snapshot.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/metrics" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/metrics/uniform_reservoir.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mm" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/mm/debug_new.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mm" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/mm/mem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mm" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/mm/mpool.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/os.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/path.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/pidfile.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/process.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/process_param.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/os" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/os/signal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/callback.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/class_factory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/event_dispatcher.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/example_stage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/init.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/kill_thread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/metrics_report_event.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/metrics_stage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/seda_config.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/seda_defs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/stage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/stage_event.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/stage_factory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/thread_pool.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/seda" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/seda/timer_stage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/time" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/time/datetime.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/time" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/time/timeout_info.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/deps/common/version.h")
endif()

