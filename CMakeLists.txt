cmake_minimum_required(VERSION 3.16)

project(bfjit LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(GMAKE_EXECUTABLE NAMES gmake make REQUIRED)

find_program(LLVM_CONFIG_EXECUTABLE NAMES llvm-config-22 llvm-config REQUIRED)

function(bfjit_query_llvm_config output_variable option)
    execute_process(
        COMMAND "${LLVM_CONFIG_EXECUTABLE}" "${option}"
        OUTPUT_VARIABLE query_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE query_status
    )

    if(NOT query_status EQUAL 0)
        message(FATAL_ERROR "Failed to query LLVM using ${LLVM_CONFIG_EXECUTABLE} ${option}")
    endif()

    set(${output_variable} "${query_output}" PARENT_SCOPE)
endfunction()

bfjit_query_llvm_config(LLVM_VERSION --version)

if(NOT LLVM_VERSION MATCHES "^22\\.")
    message(FATAL_ERROR "LLVM 22 is required, but ${LLVM_VERSION} was found")
endif()

bfjit_query_llvm_config(LLVM_INCLUDE_DIR --includedir)
bfjit_query_llvm_config(LLVM_SHARED_MODE --shared-mode)
bfjit_query_llvm_config(LLVM_LIBFILES_RAW --libfiles)

if(NOT LLVM_SHARED_MODE STREQUAL "shared")
    message(FATAL_ERROR "LLVM must provide shared libraries, but llvm-config --shared-mode returned ${LLVM_SHARED_MODE}")
endif()

string(REPLACE "\n" ";" LLVM_SHARED_LIBRARIES "${LLVM_LIBFILES_RAW}")
list(FILTER LLVM_SHARED_LIBRARIES EXCLUDE REGEX "^$")

if(NOT LLVM_SHARED_LIBRARIES)
    message(FATAL_ERROR "No LLVM shared libraries were reported by llvm-config --libfiles")
endif()

add_library(llvm-shared INTERFACE)
target_include_directories(llvm-shared INTERFACE "${LLVM_INCLUDE_DIR}")
target_link_libraries(llvm-shared INTERFACE ${LLVM_SHARED_LIBRARIES})

add_library(libbfjit STATIC
	include/bfjit.h
    include/bfjit_internal.h
    include/bflexer.h
    include/bfopt.h
    include/bfparser.h
	src/bfjit.c
    src/bfjit_codegen.c
    src/bfjit_runtime.c
    src/bflexer.c
    src/bfopt.c
    src/bfparser.c
)

target_include_directories(libbfjit PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(libbfjit PUBLIC llvm-shared)
set_target_properties(libbfjit PROPERTIES OUTPUT_NAME bfjit)

add_executable(bfjit src/main.c)
target_link_libraries(bfjit PRIVATE libbfjit)

set(BFJIT_HYDROGEN_SOURCE_DIR "/tmp/Brainfuck/extras" CACHE PATH
    "Path to the Brainfuck repo extras directory containing hydrogen.c")
set(BFJIT_HYDROGEN_BINARY "${BFJIT_HYDROGEN_SOURCE_DIR}/hydrogen8")

if(NOT EXISTS "${BFJIT_HYDROGEN_SOURCE_DIR}/hydrogen.c")
    message(FATAL_ERROR
        "hydrogen.c was not found in ${BFJIT_HYDROGEN_SOURCE_DIR}. "
        "Clone https://github.com/rdebath/Brainfuck and point BFJIT_HYDROGEN_SOURCE_DIR to its extras directory.")
endif()

add_custom_command(
    OUTPUT "${BFJIT_HYDROGEN_BINARY}"
    COMMAND "${GMAKE_EXECUTABLE}" -f GNUmakefile hydrogen8
    WORKING_DIRECTORY "${BFJIT_HYDROGEN_SOURCE_DIR}"
    DEPENDS
        "${BFJIT_HYDROGEN_SOURCE_DIR}/GNUmakefile"
        "${BFJIT_HYDROGEN_SOURCE_DIR}/hydrogen.c"
        "${BFJIT_HYDROGEN_SOURCE_DIR}/ov_int.h"
    COMMENT "Building hydrogen8 benchmark interpreter"
    VERBATIM
)
add_custom_target(hydrogen_benchmark ALL DEPENDS "${BFJIT_HYDROGEN_BINARY}")

set(BFJIT_BENCHMARK_CASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/benchmark_cases")
add_custom_command(
    OUTPUT
        "${BFJIT_BENCHMARK_CASE_DIR}/mandelbrot_x2.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/hanoi_x2.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/deep_nesting_512.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/wide_sweep_24k_x128.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/arith_pipeline_4k.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/copy_restore_2k.bf"
    COMMAND
        "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/suite.py"
        generate "${BFJIT_BENCHMARK_CASE_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/suite.py"
    COMMENT "Generating benchmark cases"
    VERBATIM
)
add_custom_target(benchmark_cases ALL
    DEPENDS
        "${BFJIT_BENCHMARK_CASE_DIR}/mandelbrot_x2.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/hanoi_x2.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/deep_nesting_512.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/wide_sweep_24k_x128.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/arith_pipeline_4k.bf"
        "${BFJIT_BENCHMARK_CASE_DIR}/copy_restore_2k.bf"
)

function(bfjit_add_benchmark_case case_name source_file)
    add_test(
        NAME "benchmark_bfjit_${case_name}"
        COMMAND "$<TARGET_FILE:bfjit>" "${source_file}"
    )
    add_test(
        NAME "benchmark_hydrogen_${case_name}"
        COMMAND "${BFJIT_HYDROGEN_BINARY}" "${source_file}"
    )
    set_tests_properties(
        "benchmark_bfjit_${case_name}"
        "benchmark_hydrogen_${case_name}"
        PROPERTIES LABELS "benchmark"
    )
endfunction()

bfjit_add_benchmark_case(mandelbrot "${CMAKE_CURRENT_SOURCE_DIR}/examples/mandelbrot.b.txt")
bfjit_add_benchmark_case(hanoi "${CMAKE_CURRENT_SOURCE_DIR}/examples/hanoi.b.txt")

bfjit_add_benchmark_case(mandelbrot_x2 "${BFJIT_BENCHMARK_CASE_DIR}/mandelbrot_x2.bf")
bfjit_add_benchmark_case(hanoi_x2 "${BFJIT_BENCHMARK_CASE_DIR}/hanoi_x2.bf")
bfjit_add_benchmark_case(deep_nesting_512 "${BFJIT_BENCHMARK_CASE_DIR}/deep_nesting_512.bf")
bfjit_add_benchmark_case(wide_sweep_24k_x128 "${BFJIT_BENCHMARK_CASE_DIR}/wide_sweep_24k_x128.bf")
bfjit_add_benchmark_case(arith_pipeline_4k "${BFJIT_BENCHMARK_CASE_DIR}/arith_pipeline_4k.bf")
bfjit_add_benchmark_case(copy_restore_2k "${BFJIT_BENCHMARK_CASE_DIR}/copy_restore_2k.bf")
