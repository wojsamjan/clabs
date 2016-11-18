/*  
 *  File: main.c
 *
 *  Program graj±cy w Othello. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h> 
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "menu.h"
#include "othello_gtk.h"

GtkWidget *window=NULL;
GtkWidget *drawing_area=NULL;

GdkPixbuf *tlo=NULL;
GdkPixbuf *biale=NULL;
GdkPixbuf *czarne=NULL;

stateT state;

int main(int argc, char **argv)
{
	GtkWidget *main_vbox;
	GtkWidget *menubar;
	state=NewGame();
	
	gtk_init(&argc, &argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "Othello");
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_border_width (GTK_CONTAINER (main_vbox), 1);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);

	
	get_main_menu(window, &menubar);
	gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);

	if (tlo == NULL)
		tlo = gdk_pixbuf_new_from_file("green.bmp", NULL);
	if (biale == NULL)
		biale = gdk_pixbuf_new_from_file("white.bmp", NULL);
	if (czarne == NULL)
		czarne = gdk_pixbuf_new_from_file("black.bmp", NULL);
	
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(drawing_area), 8*ICON_WIDTH, 8*ICON_HEIGHT);
	gtk_box_pack_start (GTK_BOX (main_vbox), drawing_area, TRUE, TRUE, 0);

	
	gtk_signal_connect (GTK_OBJECT (drawing_area), "button_press_event",
	      		      (GtkSignalFunc) button_press_event, NULL);
	gtk_signal_connect (GTK_OBJECT (drawing_area),  "expose_event",
			      G_CALLBACK (expose_event), NULL);
	gtk_signal_connect (GTK_OBJECT(drawing_area),"configure_event",
	  		      G_CALLBACK (configure_event), NULL);

	gtk_widget_set_events (drawing_area, GDK_BUTTON_PRESS_MASK | GDK_EXPOSURE_MASK );
	
	
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
