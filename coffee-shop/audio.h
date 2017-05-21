#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "globals.h"

/*
 * Function declarations for audio mixing
 * --------------------------------------
*/

int init_audio();
int load_sounds(double* volume_array);
void play(double overall_volume);
void clean();

#endif
