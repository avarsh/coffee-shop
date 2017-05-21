#!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o Coffee-Shop -lSDL_mixer -lSDL `pkg-config --libs gtk+-3.0` ./coffee-shop/main.c ./coffee-shop/interface.c ./coffee-shop/audio.c ./coffee-shop/file.c
