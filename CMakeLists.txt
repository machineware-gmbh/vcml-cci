 ##############################################################################
 #                                                                            #
 # Copyright (C) 2024 MachineWare GmbH                                        #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

cmake_minimum_required(VERSION 3.16)
project(vcml-cci VERSION 2024.05.27 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(FindGithubRepo)
include(GenVersionInfo)
include(Sanitizer)

find_package(Git REQUIRED)
find_github_repo(mwr "machineware-gmbh/mwr")
find_github_repo(vcml "machineware-gmbh/vcml")

option(VCML_CCI_TESTS "Build unit tests" OFF)
option(VCML_CCI_COVERAGE "Generate coverage data" OFF)
set(VCML_CCI_LINTER "" CACHE STRING "Code linter to use")

if(NOT TARGET cci)
    # TODO:: it would be nice if systemc-cci would only use "export" if it is not
    # included as a subdirectory, i.e. iff CMAKE_CURRENT_SOURCE_DIR == CMAKE_SOURCE_DIR
    # Unfortunatly, cci always exports itself, even if it is just a submodule.
    # Once this has been fixed, the following export can be removed.
    export(TARGETS systemc
           NAMESPACE SystemC::
           FILE SystemCLanguageTargets.cmake)
    install (EXPORT SystemCLanguageTargets
             NAMESPACE SystemC::
             DESTINATION ${SystemCLanguage_INSTALL_CMAKEDIR}
             COMPONENT dev)
    # TODO: cci defaults to shared libraries, which causes problems when the
    # rest is built without fPIC
    option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
    add_subdirectory(cci)
endif()

set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(inc ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(gen ${CMAKE_CURRENT_BINARY_DIR}/gen)

configure_file(${src}/vcml/cci/version.h.in
               ${gen}/vcml/cci/version.h @ONLY)

add_library(vcml-cci STATIC
            ${src}/vcml/cci/broker.cpp)

target_compile_options(vcml-cci PRIVATE ${MWR_COMPILER_WARN_FLAGS})
target_compile_features(vcml-cci PRIVATE cxx_std_17)

target_include_directories(vcml-cci PUBLIC ${inc})
target_include_directories(vcml-cci PRIVATE ${src})
target_include_directories(vcml-cci PUBLIC ${gen})
target_include_directories(vcml-cci SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cci/src)

target_link_libraries(vcml-cci PUBLIC mwr)
target_link_libraries(vcml-cci PUBLIC vcml)
target_link_libraries(vcml-cci PUBLIC cci)

set_target_properties(vcml-cci PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(vcml-cci PROPERTIES CXX_CLANG_TIDY "${VCML_CCI_LINTER}")
set_target_properties(vcml-cci PROPERTIES VERSION "${VCML_CCI_VERSION}")
set_target_properties(vcml-cci PROPERTIES SOVERSION "${VCML_CCI_VERSION_MAJOR}")

if(VCML_CCI_COVERAGE)
    target_compile_options(vcml-cci PUBLIC --coverage)
    target_link_libraries(vcml-cci PUBLIC -lgcov)
endif()

if(VCML_CCI_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(TARGETS vcml-cci DESTINATION lib)
install(DIRECTORY ${inc}/ DESTINATION include)
install(DIRECTORY ${gen}/ DESTINATION include)

