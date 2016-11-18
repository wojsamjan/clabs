#include <stdlib.h>
#include <gtk/gtk.h>
#include "main.h"
#include "minimax.h"

GtkWidget *drawing_area;
GtkWidget *talk;
GString *string;
static GtkAdjustment *adj, *adj1, *adj2;
int stos[3 + 1];
int max = 3;
int rek_depth;
int dane[] = { 3, 4, 5, 9, 0 };

extern gboolean configure_event(GtkWidget * widget, GdkEventConfigure * event);

void AnnounceResults(GtkWidget * widget);

void show_help(void);

void show_opc(void);

void DisplayGame(GtkWidget * widget);

extern gboolean expose_event(GtkWidget * widget, GdkEventExpose * event);

void change_max(void);

static void make_move(GtkWidget * widget);


void start(void)
{
    int i;

    for (i = 0; i < 3; i++)
	stos[i + 1] = dane[i];
    rek_depth = dane[3];
    change_max();
    DisplayGame(drawing_area);
    if (dane[4]) {

	string = g_string_new("");

	move = ChooseComputerMove();
	g_string_printf(string, "Komputer bierze %d kule z %d stosu.",
			move.liczba, move.nr_stosu);
	gtk_label_set_text(GTK_LABEL(talk), g_string_free(string, FALSE));

	MakeMove(move);

	if (GameIsOver()) {
	    gtk_label_set_text(GTK_LABEL(talk), "Przegrałeś");
	    dane[4] = 0;
	    AnnounceResults(drawing_area);
	    return;
	}
    } else
	gtk_label_set_text(GTK_LABEL(talk),
			   "Zaczyna Człowiek:\nWprowadź dane w pola poniżej i naciśnij ok.");

    DisplayGame(drawing_area);


}


void quit(void)
{
    exit(0);
}





int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *box2;
    GtkWidget *menu;
    GtkWidget *main_menu;
    GtkWidget *menu_bar;
    GtkWidget *menu_items;
    GtkWidget *label;
    GtkWidget *button;

    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),
			 "NIM - wersja z trzema stosami");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    /* drawing area */
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(drawing_area), 400, 300);
    gtk_widget_show(drawing_area);

    /* main menu */
    menu = gtk_menu_new();
    menu_items = gtk_menu_item_new_with_label("Nowa gra");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);



    g_signal_connect_swapped(G_OBJECT(menu_items), "activate",
			     G_CALLBACK(start), G_OBJECT(drawing_area));
    gtk_widget_show(menu_items);

    menu_items = gtk_menu_item_new_with_label("Opcje");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
    g_signal_connect_swapped(G_OBJECT(menu_items), "activate",
			     G_CALLBACK(show_opc), G_OBJECT(drawing_area));
    gtk_widget_show(menu_items);

    menu_items = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
    gtk_widget_show(menu_items);

    gtk_widget_show(menu_items);
    menu_items = gtk_menu_item_new_with_label("Wyjdź");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
    g_signal_connect_swapped(G_OBJECT(menu_items), "activate",
			     G_CALLBACK(quit), G_OBJECT(drawing_area));
    gtk_widget_show(menu_items);


    main_menu = gtk_menu_item_new_with_label("Main");
    gtk_widget_show(main_menu);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(main_menu), menu);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);

    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show(menu_bar);

    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, FALSE, FALSE, 2);
    
    label = gtk_hseparator_new();
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);


    talk =
	gtk_label_new
	("Zaczyna Człowiek:\nWprowadź dane w pola poniżej i naciśnij ok.");
    gtk_widget_show(talk);
    gtk_box_pack_start(GTK_BOX(vbox), talk, FALSE, FALSE, 2);


    label = gtk_hseparator_new();
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);


    box2 = gtk_hbox_new(FALSE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Z którego stosu chcesz zabrać kule?");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(vbox), box2, FALSE, FALSE, 2);

    adj1 = (GtkAdjustment *) gtk_adjustment_new(1, 1, 3, 1, 10, 0);
    spinner5 = gtk_spin_button_new(adj1, 1.0, 2);
    gtk_widget_show(spinner5);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner5), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner5), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner5), FALSE);
    gtk_widget_set_size_request(spinner5, 100, -1);

    gtk_box_pack_start(GTK_BOX(box2), spinner5, TRUE, FALSE, 0);

    box2 = gtk_hbox_new(FALSE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Ile kul chcesz zabrać ze stosu?");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(vbox), box2, FALSE, FALSE, 2);

    adj2 = (GtkAdjustment *) gtk_adjustment_new(1, 1, max, 1, 10, 0);
    spinner6 = gtk_spin_button_new(adj2, 1.0, 2);
    gtk_widget_show(spinner6);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner6), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner6), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner6), FALSE);
    gtk_widget_set_size_request(spinner6, 100, -1);

    g_signal_connect(adj1, "value_changed",
		     G_CALLBACK(change_max), (gpointer) spinner5);

    gtk_box_pack_start(GTK_BOX(box2), spinner6, TRUE, FALSE, 0);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(make_move), G_OBJECT(window));
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, FALSE, 0);
    gtk_widget_show(button);




    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), main_menu);

    /*Help */
    menu_items = gtk_menu_item_new_with_label("Help");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_items);
    g_signal_connect_swapped(G_OBJECT(menu_items), "activate",
			     G_CALLBACK(show_help),
			     G_OBJECT(drawing_area));
    gtk_widget_show(menu_items);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(quit), NULL);

    g_signal_connect(G_OBJECT(drawing_area), "configure_event",
		     G_CALLBACK(configure_event), NULL);

    g_signal_connect(G_OBJECT(drawing_area), "expose_event",
		     G_CALLBACK(expose_event), NULL);




    gtk_widget_show(window);

    gtk_main();

    return 0;
}




static void make_move(GtkWidget * widget)
{

    move.nr_stosu =
	gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner5));
    move.liczba =
	gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner6));

    if (MoveIsLegal(move) && !GameIsOver())
	MakeMove(move);
    else
	return;

    if (GameIsOver()) {
	gtk_label_set_text(GTK_LABEL(talk), "Wygrałeś!");
	dane[4] = 1;
	AnnounceResults(drawing_area);
	return;
    }

    DisplayGame(drawing_area);

    string = g_string_new("");

    move = ChooseComputerMove();
    g_string_printf(string, "Komputer bierze %d kule z %d stosu.",
		    move.liczba, move.nr_stosu);
    gtk_label_set_text(GTK_LABEL(talk), g_string_free(string, FALSE));

    MakeMove(move);

    if (GameIsOver()) {
	gtk_label_set_text(GTK_LABEL(talk), "Przegrałeś");
	dane[4] = 0;
	AnnounceResults(drawing_area);
	return;
    }


    DisplayGame(drawing_area);

}


void change_max(void)
{
    max = stos[gtk_spin_button_get_value_as_int(spinner5)];

    gtk_spin_button_set_range(spinner6, 1, max);

}
