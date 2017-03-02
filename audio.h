#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>  
#include <SDL2/SDL_mixer.h>  
#include "globals.h"

/*
 * Function declarations for audio mixing
 * --------------------------------------
*/

int init();
int load_files();
void play();
void clean();

#endif