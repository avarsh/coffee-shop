#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int load_config() 
{
    char* home_directory;
    char* config_dir = "/.config/";
    char* file_name = "coffee-shop.conf";
    char* config_path; 

    char current_volume[100];

    struct stat st;

    char file_char;
    char* end;
    FILE* config_file;

    int dir_res = 0;
    int array_index;

    for(array_index = 0; array_index < (sizeof(volumes) / sizeof(int)); array_index++)
    {
        volumes[array_index] = 50;
    }

    // First check if the config directory exists
    home_directory = getenv("HOME");

    config_path = (char*)calloc(strlen(home_directory) + strlen(config_dir) + strlen(file_name) + 1, sizeof(char));

    strcat(config_path, home_directory); // TODO: use strcat_s
    strcat(config_path, config_dir);

    // Make it if it doesn't exist 
    if(stat(config_path, &st) == -1)
    {
        printf("Dir not found!\n");
        dir_res = mkdir(config_path, 0700);
        if(dir_res == -1)
        {
            // TODO: We need to get the exact error as well...
            printf("Error occured when making configuration directory!\n");
            return 1;
        }
    }

    strcat(config_path, file_name); 
    config_file = fopen(config_path, "ab+");
    array_index = 0;
    if(config_file)
    {
        while((file_char = getc(config_file)) != EOF) 
        {
            // TODO: This is dodgy
            if(file_char == '\n')
            {
                volumes[array_index] = strtol(current_volume, &end, 10);
                memset(current_volume, 0, sizeof(current_volume));
                array_index++;
            } else {
                strncat(current_volume, &file_char, 1); 
            }
        }

        fclose(config_file);
    }

    free(config_path);

    return 0;
}
