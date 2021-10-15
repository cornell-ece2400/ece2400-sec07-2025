#=========================================================================
# CMake script for PA3
#=========================================================================
# To add new implementations or new tests, simply append your new file to
# the corresponding list.
#
# Author: Yanghui Ou, Peitian Pan
#   Date: Oct 30, 2020
#

set(SRC_FILES
  ece2400-stdlib.c
  selection-sort-int.c
)

set(TEST_ALL_FILES
  selection-sort-int-helper-test.c
  selection-sort-int-directed-test.c
)

set(EVAL_FILES
  selection-sort-int-eval.c
)

#=========================================================================
# !!!!DO NOT TOUCH THE FOLLOWING CODE!!!!
#=========================================================================

#-------------------------------------------------------------------------
# remove_extension
#-------------------------------------------------------------------------
# Removes the file extension. For example:
# remove_extension(IMPL, "pow-iter.c") stores "pow-iter" into IMPL.

function(remove_extension VARNAME FILE_NAME)
  string(REGEX REPLACE "\\.[^.]*$" "" NAME_WITHOUT_EXT ${FILE_NAME})
  set(${VARNAME} "${NAME_WITHOUT_EXT}" PARENT_SCOPE)
endfunction()

#-------------------------------------------------------------------------
# Set up environment
#-------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8...3.19)
enable_language(C)
enable_testing()
project(pa3-algo)

# Make sure we are using the correct version of gcc
set(ece2400_gcc_version "6.3.1")
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_C_COMPILER_VERSION VERSION_LESS ece2400_gcc_version)
    message(FATAL_ERROR "It seems like your CMAKE GNU C compiler has "
                        "version ${CMAKE_C_COMPILER_VERSION} but the "
                        "required version for ECE 2400 PAs is >= "
                        "${ece2400_gcc_version}. Please make sure you "
                        "are developing on ECELinux and that you have "
                        "sourced the setup script for ECE 2400. If "
                        "this error persists, please rerun the build "
                        "system after removing all files in your build "
                        "directory (rm -rf build).")
  endif()
else()
  message(FATAL_ERROR "It seems like your CMAKE C compiler is "
                      "${CMAKE_C_COMPILER_ID}. The build system of "
                      "ECE 2400 PAs requires a GNU C compiler. "
                      "Please make sure you are developing on ECELinux "
                      "and that you have sourced the setup script for "
                      "ECE 2400!")
endif()

# Set and cache the build type
set(default_build_type "debug")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "debug" "eval" )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "${default_build_type}")
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

# Flags for GCC
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wvla -Werror -Werror=vla")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g --coverage -Wno-unused-parameter")
set(CMAKE_C_FLAGS_EVAL "-DEVAL -O3 -g -Wno-unused-parameter")

# Path to this PA's source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(EVAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eval")

# Include path to this PA's header files
include_directories(${SRC_DIR})

#-------------------------------------------------------------------------
# Link source files into a library
#-------------------------------------------------------------------------

foreach(SRC_FILE ${SRC_FILES})
  set(LIB_SRCS ${LIB_SRCS} "${SRC_DIR}/${SRC_FILE}")
endforeach(SRC_FILE)

add_library(${PROJECT_NAME} ${LIB_SRCS})

#-------------------------------------------------------------------------
# Test targets
#-------------------------------------------------------------------------

add_custom_target(check COMMAND ctest "--timeout" "10" ${CTEST_OUTPUT_ON_FAILURE})

foreach(TEST_FILE ${TEST_ALL_FILES})

  remove_extension(TEST_BIN ${TEST_FILE})
  set(TEST_SRC "${TEST_DIR}/${TEST_FILE}")

  # Add test
  add_executable(${TEST_BIN} EXCLUDE_FROM_ALL ${TEST_SRC})
  target_link_libraries(${TEST_BIN} ${PROJECT_NAME} m) # link the math and src library
  add_dependencies(check ${TEST_BIN})
  add_test(${TEST_BIN} ${TEST_BIN})

endforeach(TEST_FILE)

#-------------------------------------------------------------------------
# Milestone test targets
#-------------------------------------------------------------------------

add_custom_target(check-milestone COMMAND ctest "-L" "milestone" "--timeout" "10")

foreach(TEST_FILE ${TEST_MILESTONE_FILES})

  remove_extension(TEST_BIN ${TEST_FILE})
  add_dependencies(check-milestone ${TEST_BIN})
  set_tests_properties(${TEST_BIN} PROPERTIES LABELS "milestone")

endforeach(TEST_FILE)

#-------------------------------------------------------------------------
# Evaluation targets
#-------------------------------------------------------------------------

add_custom_target(eval)

foreach(EVAL_FILE ${EVAL_FILES})

  remove_extension(EVAL_BIN ${EVAL_FILE})
  set(EVAL_SRC "${EVAL_DIR}/${EVAL_FILE}")

  # Add eval
  add_executable(${EVAL_BIN} EXCLUDE_FROM_ALL ${EVAL_SRC})
  target_link_libraries(${EVAL_BIN} ${PROJECT_NAME} m) # link the math and src library
  add_dependencies(eval ${EVAL_BIN})

endforeach(EVAL_FILE)

#-------------------------------------------------------------------------
# Code coverage target
#-------------------------------------------------------------------------

add_custom_target(coverage
  COMMAND lcov --capture --directory . --output-file coverage.info
  COMMAND genhtml coverage.info --output-directory coverage-html
)

#-------------------------------------------------------------------------
# Mem check target
#-------------------------------------------------------------------------

add_custom_target(memcheck
  COMMAND echo ""
  COMMAND echo "========================================================="
  COMMAND echo " memcheck passed!"
  COMMAND echo "========================================================="
  COMMAND echo ""
)

foreach(TEST_FILE ${TEST_ALL_FILES})

  remove_extension(TEST_BIN ${TEST_FILE})
  add_custom_target(memcheck-${TEST_BIN}
    COMMAND mkdir -p "memcheck-log"
    COMMAND valgrind "--trace-children=yes"
                     "--leak-check=full"
                     "--error-exitcode=1"
                     "--undef-value-errors=no"
                     "--log-file=memcheck-log/${TEST_BIN}.log"
                     "${CMAKE_CURRENT_BINARY_DIR}/${TEST_BIN}"
                     ">" "memcheck-log/${test_bin}.stdout"
    COMMAND sed "-r" "\"s/\\x1B\\[([0-9]{1,2}(;[0-9]{1,2})?)?[mGK]//g\""
                "memcheck-log/${test_bin}.stdout"
                ">" "memcheck-log/${test_bin}.stdout"
    DEPENDS ${TEST_BIN}
  )
  add_dependencies(memcheck memcheck-${TEST_BIN})

endforeach(TEST_FILE)

#-------------------------------------------------------------------------
# Clang format target
#-------------------------------------------------------------------------

add_custom_target(clang-format
  COMMAND echo ""
  COMMAND echo "========================================================="
  COMMAND echo " clang-format has finished! Please check your code or do "
  COMMAND echo " ``git diff'' to inspect the changes.                    "
  COMMAND echo "========================================================="
  COMMAND echo ""
)

add_custom_target(clang-format-check-git-clean
  COMMAND git diff --exit-code > /dev/null || {
              echo &&
              echo ========================================================= &&
              echo  \ Your git repo has unstaged changes. Please commit all  &&
              echo  \ your changes before running clang-format!              &&
              echo ========================================================= &&
              echo &&
              exit 1\;
          }
)

add_custom_target(clang-format-run
  COMMAND mkdir -p "clang-format-log"
  COMMAND clang-format "-i"
                       "-style=file"
                       "${SRC_DIR}/*.c"
                       "${SRC_DIR}/*.h"
                       "${TEST_DIR}/*.c"
                       "2>&1" "clang-format-log/c_files.stdout" || exit 0
)

add_dependencies(clang-format-run clang-format-check-git-clean)
add_dependencies(clang-format clang-format-run)
