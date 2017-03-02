#include <gtk/gtk.h>
#include "interface.h"
#include "audio.h"

int main (int argc, char **argv) 
{
    GtkApplication *app;
    int status;

    init();
    load_files();

    app = gtk_application_new("com.github.avarsh.coffee-shop", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run (G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    clean();
    
    return status;
}