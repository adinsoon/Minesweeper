cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra)


if (UNIX)
    set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
endif(UNIX)
if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "C:/SFML-2.5/SFML-2.5.1/lib/cmake/SFML/")
endif(WIN32)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(Minesweeper main.cpp Board.cpp Board.h ConsoleView.cpp ConsoleView.h ConsoleController.cpp ConsoleController.h SFMLView.cpp SFMLView.h SFMLController.cpp SFMLController.h MsgBox.cpp MsgBox.h SFMLMenu.cpp SFMLMenu.h)


target_link_libraries(Minesweeper sfml-graphics sfml-audio)