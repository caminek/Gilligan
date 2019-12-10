#Specify the minimum recommended version of CMake
cmake_minimum_required(VERSION 3.1)

#Specify the C++ Standard
set(CMAKE_CXX_STANDARD 11)

# Specify project title
project(Gilligan)

find_package(Qt5Core REQUIRED)
set(QT_CORE_TARGET Qt5::Core)

# To automatically run MOC when building(Meta Object Compiler)
set(CMAKE_AUTOMOC ON)

# To automatically run UIC when building(User Interface Compiler)
set(CMAKE_AUTOUIC ON)

# To automatically run RCC when building(Resource Compiler)
set(CMAKE_AUTORCC ON)

# Take care of Qt dependencies
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# add required source, header, uiand resource files
add_executable(${PROJECT_NAME} "main.cpp" "generate.cpp" "generate.hpp" "gilligan.cpp" "gilligan.hpp" "utils.cpp" "utils.hpp" "validate.cpp" "validate.hpp")

# link required libs
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

# install project
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
