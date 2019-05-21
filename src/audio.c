#include "audio.h"
#include "globals.h"

/**
TODO: allow for each channel to be panned using a slider and the
Mix_SetPanning function
**/

Mix_Chunk *sounds[PLAYER_NUMBER];

/*Initialize the sound system*/
int init_audio() {
    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error occured: %s\n", SDL_GetError());
        return 1;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error occured: %s\n", Mix_GetError());
        return 1;
    }

    return 0;
}

int load_sounds(double* volume_array) {
    char *file_names[PLAYER_NUMBER];
    int index;

    file_names[0] = "/usr/share/coffee-shop/sounds/fire.wav";
    file_names[1] = "/usr/share/coffee-shop/sounds/rain.wav";
    file_names[2] = "/usr/share/coffee-shop/sounds/restaurant.wav";
    file_names[3] = "/usr/share/coffee-shop/sounds/thunder.wav";
    file_names[4] = "/usr/share/coffee-shop/sounds/waves.wav";
    file_names[5] = "/usr/share/coffee-shop/sounds/wind.wav";

    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        channel_volumes[index] = *volume_array;
        volume_array++;
    }

    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        sounds[index] = NULL;
        sounds[index] = Mix_LoadWAV(file_names[index]);
        if(sounds[index] == NULL) {
            printf("Error occured when loading sounds: %s\n", Mix_GetError());
            return 1;
        }
    }

    return 0;
}

void play(double overall_volume) {
    int index;
    double volume;
    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        Mix_PlayChannel(index, sounds[index], -1);
        volume = MIX_MAX_VOLUME * (overall_volume / 100) * (channel_volumes[index] / 100);
        Mix_Volume(index, volume);
    }
}

void clean() {
    int index;
    Mix_HaltChannel(-1); /*Stop chunks from being played while being freed*/
    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        Mix_FreeChunk(sounds[index]);
        sounds[index] = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}
