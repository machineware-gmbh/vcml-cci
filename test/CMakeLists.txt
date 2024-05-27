 ##############################################################################
 #                                                                            #
 # Copyright 2022 MachineWare GmbH                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is unpublished proprietary work and may not be used or disclosed to   #
 # third parties, copied or duplicated in any form, in whole or in part,      #
 # without prior written permission of the authors.                           #
 #                                                                            #
 ##############################################################################

if(NOT TARGET gtest OR NOT TARGET gmock)
    option(INSTALL_GTEST OFF)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
endif()

if(CMAKE_BUILD_TYPE MATCHES "ASAN")
    string(APPEND ENVVARS "ASAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/sanitizer/asan.suppress:detect_leaks=1:fast_unwind_on_malloc=0;")
    string(APPEND ENVVARS "LSAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/sanitizer/lsan.suppress;")
elseif(CMAKE_BUILD_TYPE MATCHES "TSAN")
    string(APPEND ENVVARS "TSAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/sanitizer/tsan.suppress;")
elseif(CMAKE_BUILD_TYPE MATCHES "UBSAN")
    string(APPEND ENVVARS "UBSAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/sanitizer/ubsan.suppress:print_stacktrace=1;")
endif()

add_executable(model-test model.cpp testing.cpp)
target_link_libraries(model-test template-model gtest gmock)
add_test(NAME test-model COMMAND model-test)
set_tests_properties(test-model PROPERTIES TIMEOUT 4)
set_tests_properties(test-model PROPERTIES ENVIRONMENT "${ENVVARS}")
