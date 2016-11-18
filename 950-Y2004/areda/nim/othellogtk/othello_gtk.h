#ifndef INCLUDED__OTHELLO_GTK_H
#define INCLUDED__OTHELLO_GTK_H
#include "othello.h"

#define ICON_WIDTH 58
#define ICON_HEIGHT 58


extern gint gameover;
void pop_up_window(gchar *title, gchar *text);

gboolean configure_event( GtkWidget         *widget,
                                 GdkEventConfigure *event );

gboolean expose_event( GtkWidget      *widget,
                              GdkEventExpose *event );

void invalidate_all(GtkWidget* widget);
void invalidate_in_pos(GtkWidget* widget, moveT pt);

void print_icon_in_pos(GtkWidget *widget, GdkPixbuf *pixbuf, int posx,int posy);

GdkPixbuf *choose_bg(char znak);

gint button_press_event (GtkWidget *widget, GdkEventButton *event);

void print_game(GtkWidget *widget);

void print_part_of_game(GtkWidget *widget, moveT move, char *changes);

#endif
