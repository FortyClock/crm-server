cmake_minimum_required(VERSION 3.5)
project(utils_test CXX)


find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавляет в сборку пути к заголовочным файлам из проекта (в которых находятся функции,
# которые нужно протестировать)
include_directories(
    ${GTEST_INCLUDE_DIRS}
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
