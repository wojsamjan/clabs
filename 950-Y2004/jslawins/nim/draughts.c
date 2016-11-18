/* Jakub S³awiñski 13.12.2003 r.
 * plik g³ówny programu graj±cego w warcaby z u¿yciem strategii minimax
 * i z interfejsem w gtk
 * draughts.c
 */

#include <stdlib.h>
#include <gtk/gtk.h>

#include "draughts.h"
#include "dragraph.h"

GtkWidget *info = NULL;
GtkWidget *list = NULL;
chessboardT board;

int main( int   argc, 
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *menu;
  GtkWidget *main_menu;
  GtkWidget *menu_bar;
  GtkWidget *menu_items;
  GtkWidget *fixed;
  GtkWidget *frame;

  gtk_init (&argc, &argv);

  NewGame();
  board.reclevel = 6;

  /* window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Simple draughts");
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);

  /* drawing area */
  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 400, 400);

  /* main menu */
  menu = gtk_menu_new();
  menu_items = gtk_menu_item_new_with_label("New Game");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  g_signal_connect_swapped (G_OBJECT (menu_items), "activate", G_CALLBACK (start), G_OBJECT (drawing_area));
  gtk_widget_show (menu_items);
  
  menu_items = gtk_menu_item_new_with_label("Configure");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  g_signal_connect_swapped (G_OBJECT (menu_items), "activate", G_CALLBACK (show_config), NULL);
  gtk_widget_show (menu_items);
  
  menu_items = gtk_separator_menu_item_new();
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  gtk_widget_show (menu_items);
  
  menu_items = gtk_menu_item_new_with_label("Quit");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
			  	G_CALLBACK (gtk_widget_destroy),
				G_OBJECT (window));
  gtk_widget_show (menu_items);

  main_menu = gtk_menu_item_new_with_label ("Main");
  gtk_widget_show (main_menu);

  gtk_menu_item_set_submenu( GTK_MENU_ITEM (main_menu), menu);
  
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  menu_bar = gtk_menu_bar_new();
  gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
  gtk_widget_show (menu_bar);

  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), main_menu);
  
 /* help menu */
  menu = gtk_menu_new();
  menu_items = gtk_menu_item_new_with_label("Rules");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  g_signal_connect_swapped (G_OBJECT (menu_items), "activate", G_CALLBACK (show_rules), NULL);
  gtk_widget_show (menu_items);
  
  menu_items = gtk_separator_menu_item_new();
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  gtk_widget_show (menu_items);
  
  menu_items = gtk_menu_item_new_with_label("About");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);
  g_signal_connect_swapped (G_OBJECT (menu_items), "activate", G_CALLBACK (show_about), NULL);
  gtk_widget_show (menu_items);

  main_menu = gtk_menu_item_new_with_label ("Help");
  gtk_widget_show (main_menu);

  gtk_menu_item_set_submenu( GTK_MENU_ITEM (main_menu), menu);

  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), main_menu);

  /* rest */ 
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (quit), NULL);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
  gtk_widget_show (hbox);
  
  gtk_box_pack_start (GTK_BOX (hbox), drawing_area, TRUE, TRUE, 0);
  gtk_widget_show (drawing_area);

  frame = gtk_frame_new ("game status");
  gtk_widget_set_size_request (GTK_WIDGET (frame), 100, 50);
  fixed = gtk_fixed_new();
  info = gtk_label_new ("turn: WHITE");
  list = create_list();
  gtk_fixed_put ( GTK_FIXED (fixed), info, 0, 10);
  gtk_container_add (GTK_CONTAINER (frame), fixed);
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), list, TRUE, TRUE, 0);
  gtk_widget_show (vbox);
  gtk_widget_show (info);
  gtk_widget_show (list);
  gtk_widget_show (fixed);
  gtk_widget_show (frame);


  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
		    G_CALLBACK (expose_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area),"configure_event",
		    G_CALLBACK (configure_event), NULL);


  g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
		    G_CALLBACK (button_press_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_release_event",
		    G_CALLBACK (button_release_event), NULL);

  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_BUTTON_RELEASE_MASK
			 | GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}

