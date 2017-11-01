cmake_minimum_required(VERSION 3.8)
project(SymulatorFizyki)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Kolizja.cpp
        Kolizja.h
        Kolo.cpp
        Kolo.h
        Ksztalt.cpp
        Ksztalt.h
        Macierz22.cpp
        Macierz22.h
        main.cpp
        Obiekt.cpp
        Obiekt.h
        Scena.cpp
        Scena.h
        Stale.h
        Wektor.cpp
        Wektor.h
        Wielokat.cpp
        Wielokat.h)

add_executable(SymulatorFizyki ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(SymulatorFizyki allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)