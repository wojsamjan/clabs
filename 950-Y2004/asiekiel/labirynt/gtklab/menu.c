#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mazelib.h"
#include "maze_traced.h"
#include "maze.h"
#include "gui.h"
#include "draw.h"
#include "main.h"

/* Wszystkie funkcje, ktÛrych nazwy zaczynaj± siÍ od 'cb' s± callbackami
 * wywo≥ywanymi w momencie wybrania odpowiedniej opcji w menu */

/* Czy ci±gle ∂ledzimy drogÍ? */
static bool traced_running = FALSE;

/* OpÛºnienie w milisekukach */
static unsigned int tracing_interval = 200;

static void cb_exit(void)
{
      gtk_main_quit();
}

/* SprÛbuj wczytaÊ labirynt z pliku, ktÛrego nazwÍ poda≥ uøytkownik */
static void try_reading_mazemap(GtkWidget* widget, gpointer user_data)
{
      GtkWidget* file_selector = (GtkWidget *)user_data;
      const gchar* selected_filename;
      static char buf[1024];

      selected_filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));
      if (access(selected_filename, R_OK) != 0) {
            snprintf(buf, 1024, "\nNie mo≈ºna by≈Ço odczytaƒá pliku %s!\n", selected_filename);
            quick_message(buf);
      }
      else {
            ReadMazeMap(selected_filename);
            gtk_layout_set_size(GTK_LAYOUT(layout), maxMazeWidth() * ICON_WIDTH, mazeLines() * ICON_HEIGHT);
            update_view(layout);
      }
}

static void cb_read_maze(void)
{
      GtkWidget *file_selector;
      file_selector = gtk_file_selection_new ("Wybierz plik z labiryntem");
      g_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->ok_button),
                        "clicked",
                        G_CALLBACK (try_reading_mazemap),
                        (gpointer) file_selector);
      g_signal_connect_swapped (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->ok_button),
                                "clicked",
                                G_CALLBACK (gtk_widget_destroy), 
                                (gpointer) file_selector); 
      g_signal_connect_swapped (GTK_OBJECT (GTK_FILE_SELECTION (file_selector)->cancel_button),
                                "clicked",
                                G_CALLBACK (gtk_widget_destroy),
                                (gpointer) file_selector); 
      gtk_widget_show (file_selector);
}


static void cb_find_exit(void)
{
      SolveMaze(GetStartPosition());
      update_view(layout);
      invalidate_all(layout);
}

static gboolean do_tracing(gpointer data)
{
      if (!traced_running)
            return FALSE;
      if (solve_maze_step())
            return FALSE;
      update_view(layout);
      invalidate_near(layout, current_point_traced());
      return TRUE;
}

static void cb_find_traced(void)
{
      traced_running = true;
      solve_maze_by_step_init();
      gtk_timeout_add(tracing_interval, do_tracing, NULL);
}

static void cb_traced_end(void)
{
      traced_running = false;
      solve_maze_by_step_cleanup();
}

static void cb_shortest_path_length(void)
{
      static char buf[1024];
      int len = ShortestPathLength(GetStartPosition());
      if (len == NoSolution)
            strcpy(buf, "\nNie ma wyj≈õcia z labiryntu!\n");
      else
            snprintf(buf, 1024, "\nNajkr√≥tsza ≈õcie≈ºka ma d≈Çugo≈õƒá %d\n", len);
      quick_message(buf);
}

static void cb_clear_maze(void)
{
      mazeOriginal();
      update_view(layout);
      invalidate_all(layout);
}

/* Korzystamy z pythonowego generatora labiryntÛw */
static void cb_generate(void)
{
      system("./mazegen.py > genlab.txt");
      ReadMazeMap("genlab.txt");
      unlink("genlab.txt");
      gtk_layout_set_size(GTK_LAYOUT(layout), maxMazeWidth() * ICON_WIDTH, mazeLines() * ICON_HEIGHT);
      update_view(layout);
      invalidate_all(layout);
}

/* Ustaw now± warto∂Ê opÛºnienia
 * TrochÍ zabawy z dobraniem siÍ do spinnera... */
static void cb_do_set_traced_interval(GtkButton* button, gpointer window)
{
      GtkWidget* hbox;
      GtkWidget* spinner;
      GList* child_list;

      hbox = gtk_bin_get_child(GTK_BIN(window));
      child_list = gtk_container_get_children(GTK_CONTAINER(hbox));
      spinner = g_list_nth_data(child_list, 1);
      tracing_interval = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner));
      gtk_widget_destroy(GTK_WIDGET(window));
}

static void cb_set_traced_interval(void)
{
      GtkWidget* label;
      GtkWidget* spinner;
      GtkWidget* button;
      GtkWidget* vbox;
      GtkWidget* window;
      GtkAdjustment* adj;

      adj = (GtkAdjustment*)gtk_adjustment_new(200.0, 50.0, 10000.0, 50.0, 100.0, 100.0);
      vbox = gtk_vbox_new(FALSE, 2);
      gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
      label = gtk_label_new("\nOp√≥≈∫nienie w milisekundach:\n");
      spinner = gtk_spin_button_new(adj, 1.0, 0);
      button = gtk_button_new_with_label("OK");
      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

      g_signal_connect(G_OBJECT(button), "clicked",
                       G_CALLBACK(cb_do_set_traced_interval), (gpointer)window);

      gtk_container_add(GTK_CONTAINER(vbox), label);
      gtk_container_add(GTK_CONTAINER(vbox), spinner);
      gtk_container_add(GTK_CONTAINER(vbox), button);

      gtk_container_add(GTK_CONTAINER(window), vbox);

      gtk_widget_show_all(window);
}

static GtkItemFactoryEntry elementy_menu[] = {
        { "/_Plik", NULL, NULL, 0, "<Branch>" },
        { "/Plik/_Wczytaj labirynt", "<control>N", cb_read_maze, 0, NULL },
        { "/Plik/_Wyj≈õcie", "<control>Q", cb_exit, 0, NULL },
        { "/_Akcje", NULL, NULL, 0, "<Branch>" },
        { "/Akcje/_Znajd≈∫ wyj≈õcie", "<control>U", cb_find_exit, 0, NULL },
        { "/Akcje/_Dlugo≈õƒá najkr√≥tszej ≈õcie≈ºki", "", cb_shortest_path_length, 0, NULL },
        { "/Akcje/_Wyczy≈õƒá labirynt", NULL, cb_clear_maze, 0, NULL },
        { "/Akcje/_Wygeneruj labirynt", NULL, cb_generate, 0, NULL },
        { "/_Krokowe wyszukiwanie drogi", NULL, NULL, 0, "<Branch>" },
        { "/_Krokowe wyszukiwanie drogi/_Ustaw op√≥≈∫nienie", NULL, cb_set_traced_interval, 0, NULL },
        { "/_Krokowe wyszukiwanie drogi/_Rozpocznij", NULL, cb_find_traced, 0, NULL },
        { "/_Krokowe wyszukiwanie drogi/_Zako≈Ñcz", NULL, cb_traced_end, 0, NULL }
};

void generate_menu(GtkWidget* okno, GtkWidget** menubar)
{
        GtkItemFactory* factory;
        GtkAccelGroup* accel_group;
        int ile = sizeof(elementy_menu) / sizeof(elementy_menu[0]);

        accel_group = gtk_accel_group_new();
        factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel_group);
        gtk_item_factory_create_items(factory, ile, elementy_menu, NULL);
        gtk_window_add_accel_group(GTK_WINDOW(okno), accel_group);
        if (menubar)
                *menubar = gtk_item_factory_get_widget(factory, "<main>");
}

