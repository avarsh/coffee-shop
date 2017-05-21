#include <gtk/gtk.h>
#include "interface.h"
#include "audio.h"
#include "file.h"

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;
    int index;
    double volumes[PLAYER_NUMBER + 1];

    init_audio();
    load_config(volumes, PLAYER_NUMBER + 1);

    OVERALL_VOLUME = volumes[0];
    for(index = 1; index <= PLAYER_NUMBER; index++)
    {
        channel_volumes[index] = volumes[index];
    }

    load_sounds(&volumes[1]);

    app = gtk_application_new("com.github.avarsh.coffee-shop", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), volumes);

    status = g_application_run (G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    volumes[0] = OVERALL_VOLUME;
    for(index = 1; index <= PLAYER_NUMBER; index++)
    {
        volumes[index] = channel_volumes[index - 1];
    }

    write_config(volumes, PLAYER_NUMBER + 1);

    clean();

    return status;
}
