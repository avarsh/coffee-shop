#include "audio.h"
#include "globals.h"

/**
TODO: allow for each channel to be panned using a slider and the 
Mix_SetPanning function
**/

Mix_Chunk *sounds[PLAYER_NUMBER];
double OVERALL_VOLUME = 100.0; /*Temporary; volumes will eventually be loaded from config file*/

/*Initialize the sound system*/
int init() 
{
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

int load_files()
{
    char *file_names[PLAYER_NUMBER];
    int index;

    file_names[0] = "sounds/fire.wav";
    file_names[1] = "sounds/rain.wav";
    file_names[2] = "sounds/restaurant.wav";
    file_names[3] = "sounds/thunder.wav";
    file_names[4] = "sounds/waves.wav";
    file_names[5] = "sounds/wind.wav";

    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        channel_volumes[index] = 50; /*Temporary; the volumes will eventually be loaded from config file*/
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

void play()
{
    int index; 
    double volume;
    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        Mix_PlayChannel(index, sounds[index], -1);
        volume = MIX_MAX_VOLUME  * (OVERALL_VOLUME / 100) * (channel_volumes[index] / 100);
        Mix_Volume(index, volume);
    }
}

void clean() 
{
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
