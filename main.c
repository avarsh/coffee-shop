#include <gtk/gtk.h>
#include "interface.h"
#include "audio.h"
#include "file.h"

int main (int argc, char **argv) 
{
    GtkApplication *app;
    int status;
    int index;

    init();
    load_files();
    load_config();

    for(index = 0; index < (sizeof(volumes) / sizeof(int)); index++)
    {
        printf("%d ", volumes[index]);
    }
    

    app = gtk_application_new("com.github.avarsh.coffee-shop", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run (G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    clean();
    
    return status;
}
