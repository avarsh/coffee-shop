#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "globals.h"

GtkWidget* button_images[2];

/*
 * Function declarations for building UI
 * -------------------------------------
*/

void on_activate (GtkApplication* app, gpointer user_data);
void on_window_destroy (GtkWidget* widget, gpointer user_data);
void build_grid (GtkWidget* grid);

void on_play_button_click(GtkButton* button, gpointer user_data);
void on_app_volume_change(GtkRange* range, gpointer user_data);
void on_player_volume_change(GtkRange* range, gpointer user_data);

#endif