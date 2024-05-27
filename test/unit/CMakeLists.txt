 ##############################################################################
 #                                                                            #
 # Copyright (C) 2024 MachineWare GmbH                                        #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

macro(unit_test test)
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} testing)
    target_compile_options(${test} PRIVATE ${MWR_COMPILER_WARN_FLAGS})
    target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    set_target_properties(${test} PROPERTIES CXX_CLANG_TIDY "${VCML_CCI_LINTER}")
    add_test(NAME unit/${test} COMMAND ${test} ${VCML_TEST_RESOURCES})
    set_tests_properties(unit/${test} PROPERTIES ENVIRONMENT "${VCML_CCI_ENV}")
    set_tests_properties(unit/${test} PROPERTIES TIMEOUT 4)
endmacro()

unit_test(broker)
