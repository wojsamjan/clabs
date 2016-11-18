/* Jakub S³awiñski 13.12.2003 r.
 * plik nag³ówkowy dla funkcji obs³uguj±cych grafikê
 * dragraph.h
 */

#include <gtk/gtk.h>

#ifndef _JS_DRAGRAPH_H
#define _JS_DRAGRAPH_H


void load_image( GtkWidget *widget, GdkPixbuf **pixbuf, const char* filename);
void announce_result( GtkWidget *widget, int who);
gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event );
gboolean expose_event( GtkWidget *widget, GdkEventExpose *event );
void draw_square( GtkWidget *widget, gdouble x, gdouble y,int type);
void redraw_square( GtkWidget *widget, char x, char y);
gboolean button_press_event( GtkWidget *widget, GdkEventButton *event );
gboolean button_release_event( GtkWidget *widget, GdkEventButton *event );
void start (GtkWidget *widget); 
void quit (void);
void show_rules (void);
void show_about (void);
void show_config (void);
gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event );
GtkWidget* create_list();
void insert_to_list (gchar* msg, char mode);
void clear_moves_list(void);

#endif
