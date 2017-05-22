#!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o ./bin/coffee-shop -lSDL_mixer -lSDL `pkg-config --libs gtk+-3.0` ./src/main.c ./src/interface.c ./src/audio.c ./src/file.c
