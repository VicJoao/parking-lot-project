cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c
        terminal.c
        terminal.h
        estacionamento.c
        estacionamento.h
        dataHora.c
        dataHora.h
        )