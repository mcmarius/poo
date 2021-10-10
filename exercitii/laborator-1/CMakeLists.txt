project(exercitii)
cmake_minimum_required(VERSION 3.8)

# https://stackoverflow.com/questions/45955272/modern-way-to-set-compiler-flags-in-cross-platform-cmake-project
if(MSVC)
    add_compile_options("/W4")
else()
    add_compile_options("-Wall" "-Wextra" "-pedantic" "-g")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    endif()
endif()
set(SOURCE_FILES 1_liste_simplu_inlantuite.cpp)
set(TEST_FILES test_liste_simplu_inlantuite.cpp)

add_executable(liste_simplu_inlantuite ${SOURCE_FILES})

add_executable(test_liste_simplu_inlantuite ${TEST_FILES})

target_include_directories(test_liste_simplu_inlantuite PUBLIC include)
target_compile_features(test_liste_simplu_inlantuite PUBLIC cxx_std_20)
