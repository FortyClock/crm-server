cmake_minimum_required(VERSION 3.5)
project(utils_test CXX)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# используем FetchContent для загрузки GTest непосредственно в процессе сборки CMake.
# подгружает нужные библиотеки во время сборки проекта
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)


# Добавляет в сборку пути к заголовочным файлам из проекта (в которых находятся функции,
# которые нужно протестировать)
include_directories(
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googletest
    ../sutils
)



# Здесь прописывается название проекта с тестами,
# исходный файл с тестами,
# путь к исходным файлам с функциями проекта, которые нужно протестировать
add_executable(
    utils_test # название проекта с тестами (есть в начале этого файла)
    test_main.cc
    ../sutils/sutils.cc
)



# Привязывает необходимые библиотеки к сборке проекта с тестами
target_link_libraries(
    utils_test # название проекта с тестами (есть в начале этого файла)
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)



# Отключаем find_package(GTest REQUIRED) т.к. GTest теперь подключается через FetchContent
#find_package(GTest REQUIRED)
