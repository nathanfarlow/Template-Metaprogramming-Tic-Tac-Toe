add_executable(tictactoe-tests)

# The .cpp files for this executable, here:
target_sources(tictactoe-tests PRIVATE
        main.cpp
        tictactoe.cpp)

# The directories containing .h files for this executable, here:
target_include_directories(tictactoe-tests PRIVATE
        .)

set_target_properties(tictactoe-tests PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(tictactoe-tests PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(tictactoe-tests PRIVATE
            /W3)
endif ()