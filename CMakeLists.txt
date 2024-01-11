cmake_minimum_required(VERSION 3.22)
project(uni_bd2_backend)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

include(CPM.cmake)

############ CPM ############

CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 10.1.1
)

CPMAddPackage(
        NAME gsl
        GITHUB_REPOSITORY microsoft/GSL
        GIT_TAG v4.0.0
)

CPMAddPackage(
        NAME oatpp
        GITHUB_REPOSITORY oatpp/oatpp
        GIT_TAG 1.3.0
)

find_package(fmt REQUIRED)
find_package(gsl REQUIRED)

link_libraries(fmt::fmt)
include_directories(${fmt_INCLUDE_DIRS})
include_directories(${gsl_SOURCE_DIR}/include)

############# OATPP ###############

add_library(uni_bd2_backend-lib
        src/AppComponent.hpp
        src/controller/BDController.cpp
        src/controller/BDController.hpp
        src/dto/DtoSearchResultsRegions.hpp
        src/dto/DtoSearchResultsDistricts.hpp
        src/dto/DtoSearchResultsMunicipalities.hpp
        src/dto/DtoStatsResultsRegions.hpp
        src/dto/DtoStatsInfoRegion.hpp
        src/dto/DtoStatsInfoDistrict.hpp
        src/dto/DtoStatsInfoMunicipality.hpp
        src/dto/DtoStatsResultsDistricts.hpp
        src/dto/DtoStatsResultsMunicipalities.hpp
)

find_package(oatpp 1.3.0 REQUIRED)

target_link_libraries(uni_bd2_backend-lib
        PUBLIC oatpp
        PUBLIC oatpp-test
)

target_include_directories(uni_bd2_backend-lib PUBLIC src)

## add executables

add_executable(uni_bd2_backend-exe
        src/App.cpp
        test/app/BDTest.hpp)
target_link_libraries(uni_bd2_backend-exe uni_bd2_backend-lib)
add_dependencies(uni_bd2_backend-exe uni_bd2_backend-lib)

add_executable(uni_bd2_backend-test
        test/tests.cpp
        test/app/BDTestComponent.hpp
        test/app/BDTest.hpp
        test/BDTestSearch.cpp
        test/BDTestSearch.hpp
        test/BDTestStats.cpp
        test/BDTestStats.hpp
)

target_link_libraries(uni_bd2_backend-test uni_bd2_backend-lib)
add_dependencies(uni_bd2_backend-test uni_bd2_backend-lib)

set_target_properties(uni_bd2_backend-lib uni_bd2_backend-exe uni_bd2_backend-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

################ TESTS #################

enable_testing()
add_test(project-tests uni_bd2_backend-test)

################ WARNINGS ###############

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(uni_bd2_backend-exe INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    target_compile_options(uni_bd2_backend-lib INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    target_compile_options(uni_bd2_backend-test INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
        target_compile_options(uni_bd2_backend-exe INTERFACE -g -O0)
        target_compile_options(uni_bd2_backend-lib INTERFACE -g -O0)
        target_compile_options(uni_bd2_backend-test INTERFACE -g -O0)
    elseif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(uni_bd2_backend-exe INTERFACE -O3)
        target_compile_options(uni_bd2_backend-lib INTERFACE -O3)
        target_compile_options(uni_bd2_backend-test INTERFACE -O3)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(uni_bd2_backend-exe INTERFACE /W4 /w14640 /permissive-)
    target_compile_options(uni_bd2_backend-lib INTERFACE /W4 /w14640 /permissive-)
    target_compile_options(uni_bd2_backend-test INTERFACE /W4 /w14640 /permissive-)
    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
        target_compile_options(uni_bd2_backend-exe INTERFACE /Zi)
        target_compile_options(uni_bd2_backend-lib INTERFACE /Zi)
        target_compile_options(uni_bd2_backend-test INTERFACE /Zi)
    elseif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(uni_bd2_backend-exe INTERFACE /O2)
        target_compile_options(uni_bd2_backend-lib INTERFACE /O2)
        target_compile_options(uni_bd2_backend-test INTERFACE /O2)
    endif ()
endif()
