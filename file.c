#include "file.h"
#include "globals.h"
#include <stdlib.h>
#include <string.h>

#define CS_FALSE 0
#define CS_TRUE 1

double OVERALL_VOLUME = 100.0;

int open_file(FILE** config_file, int write_mode)
{
    char* home_directory;
    char* config_dir = "/.config/";
    char* file_name = "coffee-shop.conf";
    char* config_path;

    char open_mode[4];

    struct stat st;

    int dir_create_result = 0;

    // First check if the config directory exists
    home_directory = getenv("HOME");

    config_path = (char*)calloc(strlen(home_directory) + strlen(config_dir) + strlen(file_name) + 1, sizeof(char));

    strcat(config_path, home_directory); // TODO: use strcat_s
    strcat(config_path, config_dir);

    // Make it if it doesn't exist
    if(stat(config_path, &st) == -1)
    {
        printf("Directory not found!\n");
        dir_create_result = mkdir(config_path, 0700);
        if(dir_create_result == -1)
        {
            // TODO: We need to get the exact error as well...
            printf("Error occured when making configuration directory!\n");
            return 1;
        }
    }

    strcat(config_path, file_name);

    // False is 0
    if(write_mode == CS_FALSE) {
        strncpy(open_mode, "ab+", 4);
    } else {
        strncpy(open_mode, "wb+", 4);
    }

    *config_file = fopen(config_path, open_mode);

    free(config_path);

    return 0;
}

int load_config(double* volume_array, int array_size)
{
    char current_volume[100];

    struct stat st;

    char file_char;
    char* end;
    FILE* config_file;

    int dir_res = 0;
    int array_index;

    int count = 0;

    for(array_index = 0; array_index < array_size; array_index++)
    {
        *volume_array = 50;
        volume_array++;
    }

    // Reset the pointer to the start of the array
    volume_array = volume_array - array_size;

    array_index = 0;
    memset(current_volume, 0, sizeof(current_volume));

    open_file(&config_file, CS_FALSE);

    if(config_file)
    {
        while((file_char = getc(config_file)) != EOF)
        {
            // TODO: This is dodgy
            if(file_char == '\n')
            {
                if(count < PLAYER_NUMBER + 1) {
                  *volume_array = strtod(current_volume, &end);

                  memset(current_volume, 0, sizeof(current_volume));
                  volume_array++;

                  count++;
                }
            } else {
                strncat(current_volume, &file_char, 1);
            }
        }

        fclose(config_file);
    } else {
        return 1;
    }

    volume_array = volume_array - array_size;

    return 0;
}

int write_config(double* volume_array, int array_size)
{
    FILE* config_file;
    int count = 0;

    open_file(&config_file, CS_TRUE);
    for(count = 0; count < array_size; count++) {
        fprintf(config_file, "%lf\n", *volume_array);
        volume_array++;
    }

    return 0;
}
