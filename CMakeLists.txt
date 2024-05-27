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

cmake_minimum_required(VERSION 3.11)
project(template-model VERSION 2022.02.22 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(FindGithubRepo)
include(GenVersionInfo)
include(Sanitizer)

find_package(Git REQUIRED)
find_github_repo(mwr "machineware-gmbh/mwr")
find_github_repo(vcml "machineware-gmbh/vcml")

option(TEMPLATE_MODEL_TESTS "Build unit tests" OFF)
option(TEMPLATE_MODEL_COVERAGE "Generate coverage data" OFF)
set(TEMPLATE_MODEL_LINTER "" CACHE STRING "Code linter to use")

set(src ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(inc ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(gen ${CMAKE_CURRENT_BINARY_DIR}/gen)

configure_file(${src}/vcml/models/generic/model_version.h.in
               ${gen}/vcml/models/generic/model_version.h @ONLY)

add_library(template-model STATIC
            ${src}/vcml/models/generic/model.cpp)

target_compile_options(template-model PRIVATE ${MWR_COMPILER_WARN_FLAGS})
target_compile_features(template-model PRIVATE cxx_std_17)

target_include_directories(template-model PUBLIC ${inc})
target_include_directories(template-model PRIVATE ${src})
target_include_directories(template-model PUBLIC ${gen})

target_link_libraries(template-model PUBLIC mwr)
target_link_libraries(template-model PUBLIC vcml)

set_target_properties(template-model PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(template-model PROPERTIES CXX_CLANG_TIDY "${TEMPLATE_MODEL_LINTER}")
set_target_properties(template-model PROPERTIES VERSION "${TEMPLATE_MODEL_VERSION}")
set_target_properties(template-model PROPERTIES SOVERSION "${TEMPLATE_MODEL_VERSION_MAJOR}")

if(TEMPLATE_MODEL_COVERAGE)
    target_compile_options(template-model PUBLIC --coverage)
    target_link_libraries(template-model PUBLIC -lgcov)
endif()

if(TEMPLATE_MODEL_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(TARGETS template-model DESTINATION lib)
install(DIRECTORY ${inc}/ DESTINATION include)
install(DIRECTORY ${gen}/ DESTINATION include)

