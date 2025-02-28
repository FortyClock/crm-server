cmake_minimum_required(VERSION 3.5)

project(MechWarrior LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определение переменных версии
set(PROJECT_VERSION "1.0.0")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

# Найти необходимые компоненты Qt
find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

# Настройка проекта
qt_standard_project_setup()

# Добавление исполняемого файла
qt_add_executable(MechWarrior
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mapwidget.h
    mapwidget.cpp
    mapwidget.h
)


# Связывание библиотек
target_link_libraries(MechWarrior PRIVATE Qt6::Widgets Qt6::Network)

# Установка свойств целевого исполняемого файла
set_target_properties(MechWarrior PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "MechWarrior"
)

# Установка целевого исполняемого файла
install(TARGETS MechWarrior
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
