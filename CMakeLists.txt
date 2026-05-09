cmake_minimum_required(VERSION 3.16)

project(Lab5_KG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable( Lab5_KG 
                core/main.cpp
                core/CScene/CScene.cpp
                core/CCanvas/CCanvas.cpp
                core/CMainWindow/CMainWindow.cpp
                core/CMainWindow/CMainWindow.ui
                core/Figures/CFigure/CFigure.cpp
                core/Figures/CTriangle/CTriangle.cpp
                core/CMotion/CMotion.cpp
)

target_include_directories(Lab5_KG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)

set_source_files_properties(core/CProperties/CProperties.cpp PROPERTIES SKIP_AUTOUIC ON)

target_link_libraries(Lab5_KG PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)