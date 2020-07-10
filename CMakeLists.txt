cmake_minimum_required(VERSION 3.0.0)
project(CGPA)

set(CMAKE_CXX_STANDARD 11)

set(wxWidgets_ROOT_DIR </usr/include/wx-3.0)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES src/Main.cpp src/Frame.cpp src/Calc.cpp)
add_executable(cgpaCalc ${SOURCE_FILES})

target_link_libraries(cgpaCalc ${wxWidgets_LIBRARIES})