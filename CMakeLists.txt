cmake_minimum_required(VERSION 3.24)
project(graphe2023)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/edonadibra/Qt/6.5.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(graphe2023 main.cpp Point.h Sommet.h Sommet.cpp Arc.cpp Arc.h Graphe.cpp Graphe.h Algorithme.cpp Algorithme.h Point.cpp )

target_link_libraries(graphe2023 Qt6::Widgets)
