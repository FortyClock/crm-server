cmake_minimum_required(VERSION 3.5)
project(server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# -fsanitize=address Это флаг компилятора, который включает AddressSanitizer.
# AddressSanitizer — это инструмент для обнаружения ошибок памяти, таких как
# переполнение буфера, использование после освобождения и т. д.

#-fsanitize=undefined Это флаг компилятора, который включает UndefinedBehaviorSanitizer.
# UndefinedBehaviorSanitizer — это инструмент для обнаружения неопределенного поведения в
# программе, такого как деление на ноль, переполнение знаковых целых чисел и т. д.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")

# Точно указывает компилятору на исходные файлы
set(SRC_FILES
    main.cc
    sutils/actionSutils.cc
    sutils/sutils.cc
    sutils/movementSutils.cc
    controllers/StateController.cc
    controllers/MapController.cc
    controllers/MovementController.cc
    controllers/ActionController.cc
)


# aux_source_directory - собирает список всех исходных файлов
# в указанной директории и сохраняет в переменной
# (сейчас - переменная CTL_SRC_DIR)
aux_source_directory(controllers CTL_SRC_DIR)






# указывает компилятору, где искать заголовочные файлы
# (в каких директориях)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/sutils
    
)



# создаёт исполняемый файл, используя все перечисленные файлы в переменных
# если оставить add_executable(${PROJECT_NAME} main.cc)
# то будет использован только main.cc
add_executable(${PROJECT_NAME} ${SRC_FILES} ${CTL_SRC_DIR})

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)


add_subdirectory(test)


set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER DM)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_HOMEPAGE_URL https://github.com/FortyClock/crm-server.git)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.27), gcc, g++, cmake, libjsoncpp-dev, uuid-dev, zlib1g-dev, openssl, libssl-dev, libyaml-cpp-dev, libpq-dev, libmariadb-dev")
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)

include(CPack)