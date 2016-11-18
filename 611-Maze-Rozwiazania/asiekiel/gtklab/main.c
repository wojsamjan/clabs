#include <gtk/gtk.h>
#include <unistd.h>
#include "draw.h"
#include "random.h"
#include "mazelib.h"
#include "maze.h"
#include "menu.h"

GtkWidget* layout;
GtkWidget* main_window;

int main(int argc, char** argv)
{
      GtkWidget* main_window;
      GtkWidget* scroller;
      GtkWidget* menubar;
      GtkWidget* main_vbox;

      /* Na pocz±tek wczytujemy plik z labiryntem, je¿eli taki jest */
      if (access("labirynt.txt", R_OK) == 0)
            ReadMazeMap("labirynt.txt");
      /* Inicjalizacja generatora liczb losowych */
      init_random_gen();

      /* Inicjalizacja gtk i g³ównego okna */
      gtk_init(&argc, &argv);
      main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_default_size(GTK_WINDOW(main_window), 600, 400);

      /* vbox */
      main_vbox = gtk_vbox_new(FALSE, 1);
      gtk_container_add(GTK_CONTAINER(main_window), main_vbox);

      /* Wygeneruj menu */
      generate_menu(main_window, &menubar);
      gtk_box_pack_start(GTK_BOX(main_vbox), menubar, FALSE, TRUE, 0);

      /* layout i scrolle */
      layout = gtk_layout_new(NULL, NULL);
      scroller = gtk_scrolled_window_new(NULL, NULL);
      gtk_container_add(GTK_CONTAINER(scroller), layout);
      gtk_box_pack_start(GTK_BOX(main_vbox), scroller, TRUE, TRUE, 0);

      g_signal_connect(G_OBJECT(main_window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), "WM destroy");
      g_signal_connect(G_OBJECT(layout), "expose_event",
                         G_CALLBACK(on_expose_event), NULL);
      gtk_layout_set_size(GTK_LAYOUT(layout), maxMazeWidth() * ICON_WIDTH, mazeLines() * ICON_HEIGHT);

      gtk_widget_show_all(main_window);
      update_view(layout);
      gtk_main();
      return 0;
}
