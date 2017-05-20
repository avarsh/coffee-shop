#include "interface.h"
#include "audio.h"
#include <string.h>

int is_playing = 1;
GtkWidget* play_button;

/*
 * Function definitions for building UI
 * ------------------------------------
*/

/*This is executed upon window activation (i.e. when the app launches)*/
void on_activate (GtkApplication* app, gpointer user_data) 
{

    GtkWidget* window;
    GtkWidget* grid;

    /*Misc. window properties*/
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW(window), "Coffee Shop");
    gtk_window_set_default_size (GTK_WINDOW(window), 600, 300);
    gtk_widget_set_size_request(window, 600, 300);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    /*Building the layout of the interface*/
    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);

    build_grid(grid);

    gtk_widget_show_all (window);

    play();
}

void on_window_destroy (GtkWidget* widget, gpointer user_data) 
{
    g_object_unref(button_images[0]);
    g_object_unref(button_images[1]);
}

/*Function to create and add elements of the UI to the grid*/
void build_grid (GtkWidget* grid) 
{
    GtkWidget* app_volume;

    GtkWidget* player_grid;

    GtkWidget* player_boxes[PLAYER_NUMBER];
    GtkWidget* images[PLAYER_NUMBER];
    GtkWidget* player_volumes[PLAYER_NUMBER];

    char *icon_names[PLAYER_NUMBER];
    char icon_name[30];
    int index;

    icon_names[0] = "fire.svg";
    icon_names[1] = "rain.svg";
    icon_names[2] = "restaurant.svg";
    icon_names[3] = "thunder.svg";
    icon_names[4] = "waves.svg";
    icon_names[5] = "wind.svg";

    /*The play/pause button*/
    button_images[0] = gtk_image_new_from_icon_name("media-playback-start-symbolic", GTK_ICON_SIZE_DIALOG);
    button_images[1] = gtk_image_new_from_icon_name("media-playback-pause-symbolic", GTK_ICON_SIZE_DIALOG);

    g_object_ref(button_images[0]);
    g_object_ref(button_images[1]);

    play_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(play_button), button_images[1]);
    gtk_widget_set_margin_top(play_button, 12);
    gtk_widget_set_margin_bottom(play_button, 12);
    gtk_widget_set_margin_start(play_button, 12);
    gtk_widget_set_margin_end(play_button, 6);
    gtk_style_context_add_class(gtk_widget_get_style_context (play_button), "flat");

    g_signal_connect(play_button, "clicked", G_CALLBACK(on_play_button_click), NULL);

    gtk_grid_attach(GTK_GRID(grid), play_button, 0, 0, 1, 1);

    /*The overall volume slider*/
    app_volume = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk_adjustment_new(OVERALL_VOLUME, 0, 101, 1, 1, 1));
    gtk_widget_set_margin_top(app_volume, 12);
    gtk_widget_set_margin_bottom(app_volume, 12);
    gtk_widget_set_margin_start(app_volume, 6);
    gtk_widget_set_margin_end(app_volume, 12);
    gtk_widget_set_hexpand(app_volume, TRUE);

    g_signal_connect(app_volume, "value-changed", G_CALLBACK(on_app_volume_change), NULL);
    
    gtk_grid_attach(GTK_GRID(grid), app_volume, 1, 0, 1, 1);

    /*A flow box dynamically resizes and relocates children depending on window size*/
    player_grid = gtk_flow_box_new();
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(player_grid), GTK_SELECTION_NONE);
    
    for(index = 0; index < PLAYER_NUMBER; index = index + 1) 
    {
        /*Create the file name*/
        strncpy(icon_name, "images/", sizeof(icon_name));
        strcat(icon_name, icon_names[index]);

        /*Create a smaller grid to house the image and volume slider*/
        player_boxes[index] = gtk_grid_new();

        /*Icons for the sounds*/
        images[index] = gtk_image_new_from_file(icon_name);
        gtk_widget_set_hexpand(images[index], TRUE);
        gtk_grid_attach(GTK_GRID(player_boxes[index]), images[index], 0, 0, 1, 1);

        /*The individual volume sliders*/
        player_volumes[index] = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk_adjustment_new(50, 0, 101, 1, 1, 1));
        gtk_widget_set_size_request(player_volumes[index], 150, -1);

        g_signal_connect(player_volumes[index], "value-changed", G_CALLBACK(on_player_volume_change), (gpointer)index);

        gtk_grid_attach(GTK_GRID(player_boxes[index]), player_volumes[index], 0, 1, 1, 1);

        /*Add them to the flow box*/
        gtk_flow_box_insert(GTK_FLOW_BOX(player_grid), player_boxes[index], index);
    }

    gtk_grid_attach(GTK_GRID(grid), player_grid, 0, 1, 2, 2);
    
}

void on_play_button_click(GtkButton* button, gpointer user_data)
{
    /*Firstly change the image*/
    is_playing = 1 - is_playing;
    gtk_button_set_image(button, button_images[is_playing]);

    /*Pause or resume all channels*/
    if(is_playing == 0) { 
        Mix_Pause(-1); 
    } else { 
        Mix_Resume(-1); 
    }
}

void on_app_volume_change(GtkRange* range, gpointer user_data) 
{
    int index;
    double temp_volume;
    
    OVERALL_VOLUME = gtk_range_get_value(range);

    /*Set each channel's volume accordingly*/
    for(index = 0; index < PLAYER_NUMBER; index = index + 1) {
        temp_volume = MIX_MAX_VOLUME * (OVERALL_VOLUME / 100) * (channel_volumes[index] / 100);
        Mix_Volume(index, temp_volume);
    }
}

void on_player_volume_change(GtkRange* range, gpointer user_data)
{
    double volume;
    int index = (int) user_data; /*There's a warning here because of pointer to int casting*/
    channel_volumes[index] = gtk_range_get_value(range);
    volume = MIX_MAX_VOLUME * (OVERALL_VOLUME / 100) * (channel_volumes[index] / 100);
    Mix_Volume(index, volume);
}
