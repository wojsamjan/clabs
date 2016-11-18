#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <stdio.h>
#include "othello.h"
#include "main.h"
#include "othello_gtk.h"

static void help(void)
{
	FILE *file;
	unsigned int n;
	char *linia = NULL;
	
	/* otwarcie pliku z zasadami gry */
	file=fopen("zasady_gry.txt","r");
	/* pobranie zasad gry do string'a linia */
	getdelim(&linia, &n, EOF,  file);
	
	pop_up_window("Zasady gry", linia);
	free(linia);
	fclose(file);
}

static void New_game(void)
{
	state=NewGame();
	print_game(drawing_area);
	gameover=FALSE;
}

/******** Menu ************/

static GtkItemFactoryEntry menu_items[] = {
	{"/_Gra",		NULL,		NULL,		0, "<Branch>"},
	{"/Gra/_Nowa _gra",	"<ctrl>N",	New_game, 		0, NULL},
	{"/Gra/_Koniec",	"<CTRL>Q",	gtk_main_quit,	0, NULL},
	{"/_Pomoc",		NULL, 		NULL, 		0, "<LastBranch>"},	
	{"/Pomoc/_Zasady _gry",	NULL,		help, 		0, NULL},
};


void get_main_menu( GtkWidget  *window, GtkWidget **menubar)
{
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;
	gint nmenu_items = sizeof(menu_items) / sizeof(menu_items[0]);

	/* Make an accelerator group (shortcut keys) */
	accel_group = gtk_accel_group_new ();
	/* Make an ItemFactory (that makes a menubar) */
	item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", accel_group);
	/* This function generates the menu items. Pass the item factory,
	the number of items in the array, the array itself, and any
	callback data for the the menu items. */
	gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
	/* Attach the new accelerator group to the window. */
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
	/* Finally, return the actual menu bar created by the item factory. */
	if (menubar)	
		*menubar=gtk_item_factory_get_widget (item_factory, "<main>");
}

