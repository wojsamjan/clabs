#include <stdlib.h>
#include <gtk/gtk.h>
#include "main.h"

static GtkWidget *otherwin;
static GtkWidget *label;
static GtkWidget *button;
static GtkWidget *buttonH;
static GtkWidget *box1;
static GtkWidget *box2;
static GtkWidget *spinner1, *spinner2, *spinner3, *spinner4;
static GtkAdjustment *adj;
static GdkPixbuf *images[] = { NULL, NULL, NULL, NULL };
static GdkPixmap *pixmap = NULL;


static void
load_image(GtkWidget * widget, GdkPixbuf ** pixbuf, const char *filename);

void show_warning(void);

static GSList *group;

void win_close(void);

static void change_options(GtkWidget * widget);


void show_help()
{
    if (otherwin)
	return;
    otherwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(otherwin), "Zasady gry");
    gtk_window_set_resizable(GTK_WINDOW(otherwin), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(otherwin), 10);
    label = gtk_label_new("Zasady gry w NIM:\n\n"
			  "1. Ruchy wykonywane są na przemian.\n"
			  "2. W każdym ruchu można zabrać dowolną ilość kul,\n"
			  "ale tylko z jednego stosu na raz.\n"
			  "3. Gracz, który zabierze ostatnią kulę - przegrywa.\n");
    box1 = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(box1);
    gtk_container_add(GTK_CONTAINER(otherwin), box1);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);
    button = gtk_button_new_with_label("Zamknij");
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(gtk_widget_destroy),
			     G_OBJECT(otherwin));

    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    gtk_widget_show(otherwin);
    g_signal_connect(G_OBJECT(otherwin), "destroy",
		     G_CALLBACK(win_close), NULL);
}

void win_close(void)
{
    otherwin = NULL;
}

void show_opc(void)
{
    if (otherwin)
	return;
    otherwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(otherwin), "Opcje");
    gtk_window_set_resizable(GTK_WINDOW(otherwin), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(otherwin), 10);
    label = gtk_label_new("Liczba kul na stosie:");
    box1 = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(box1);
    gtk_container_add(GTK_CONTAINER(otherwin), box1);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);

/*Pudełko pierwsze z tekstem do wprowadzenia*/
    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Stos 1");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    adj = (GtkAdjustment *) gtk_adjustment_new(dane[0], 1, 20, 1, 10, 0);
    spinner1 = gtk_spin_button_new(adj, 1.0, 2);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner1), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner1), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner1), FALSE);
    gtk_widget_set_size_request(spinner1, 100, -1);

    gtk_box_pack_start(GTK_BOX(box2), spinner1, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_widget_show(spinner1);

/*Podobnie pudełko drugie*/

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Stos 2");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    adj = (GtkAdjustment *) gtk_adjustment_new(dane[1], 1, 20, 1, 10, 0);
    spinner2 = gtk_spin_button_new(adj, 1.0, 2);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner2), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner2), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner2), FALSE);
    gtk_widget_set_size_request(spinner2, 100, -1);


    gtk_box_pack_start(GTK_BOX(box2), spinner2, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_widget_show(spinner2);

/*I pudełko trzecie*/

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Stos 3");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    adj = (GtkAdjustment *) gtk_adjustment_new(dane[2], 1, 20, 1, 10, 0);
    spinner3 = gtk_spin_button_new(adj, 1.0, 2);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner3), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner3), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner3), FALSE);
    gtk_widget_set_size_request(spinner3, 100, -1);


    gtk_box_pack_start(GTK_BOX(box2), spinner3, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_widget_show(spinner3);
/* Odstęp pomiędzy ...*/

    label = gtk_hseparator_new();
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);
/*Pudełko czwarte z danymi o rekursji*/

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Maksymalna głębokość rekursji:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    adj = (GtkAdjustment *) gtk_adjustment_new(dane[3], 1, 30, 1, 10, 0);
    spinner4 = gtk_spin_button_new(adj, 1.0, 2);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner4), TRUE);
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinner4), 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner4), FALSE);
    gtk_widget_set_size_request(spinner4, 100, -1);

    gtk_box_pack_start(GTK_BOX(box2), spinner4, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_widget_show(spinner4);
/* I znów odstęp pomiędzy ...*/

    label = gtk_hseparator_new();
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);
//Przyciski radio, kto zaczyna*/

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    label = gtk_label_new("Kto zaczyna:");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    buttonH = gtk_radio_button_new_with_label(NULL, "Człowiek");
    gtk_box_pack_start(GTK_BOX(box2), buttonH, TRUE, TRUE, 0);
    gtk_widget_show(buttonH);

    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(buttonH));

    button = gtk_radio_button_new_with_label(group, "Komputer");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), dane[4]);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
/* I znów odstęp pomiędzy ...*/

    label = gtk_hseparator_new();
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);

/*Przyciski ok. i Zamknij*/

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_widget_show(box2);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(change_options),
			     G_OBJECT(otherwin));
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(show_warning), G_OBJECT(otherwin));
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(gtk_widget_destroy),
			     G_OBJECT(otherwin));


    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Zamknij");
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(gtk_widget_destroy),
			     G_OBJECT(otherwin));

    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
///////////////////////////////////////



    gtk_widget_show(otherwin);
    g_signal_connect(G_OBJECT(otherwin), "destroy",
		     G_CALLBACK(win_close), NULL);

}

static void change_options(GtkWidget * widget)
{
    dane[0] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner1));
    dane[1] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner2));
    dane[2] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner3));
    dane[3] = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner4));
    dane[4] = !gtk_toggle_button_get_active(buttonH);
    otherwin = NULL;

}

void
load_image(GtkWidget * widget, GdkPixbuf ** pixbuf, const char *filename)
{
    *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);


    if (*pixbuf == NULL) {
	g_print("Can't load image: %s\n", filename);
	exit(1);
    }


}

gboolean configure_event(GtkWidget * widget, GdkEventConfigure * event)
{
    int i, j;
    load_image(widget, &images[0], "images/puppet.jpg");
    load_image(widget, &images[1], "images/Kolka.xpm");
    load_image(widget, &images[2], "images/wygr.tif");
    load_image(widget, &images[3], "images/przeg.tif");

    if (pixmap)
	g_object_unref(pixmap);

    pixmap = gdk_pixmap_new(widget->window,
			    widget->allocation.width,
			    widget->allocation.height, -1);

    gdk_pixbuf_render_to_drawable(images[0], GDK_DRAWABLE(pixmap),
				  widget->style->
				  fg_gc[GTK_WIDGET_STATE(widget)], 0, 0, 0,
				  0, widget->allocation.width,
				  widget->allocation.height,
				  GDK_RGB_DITHER_NONE, 0, 0);

    for (i = 0; i <= 2; i++) {
	for (j = dane[i]; j > 0; j--) {
	    gdk_pixbuf_render_to_drawable(images[1], GDK_DRAWABLE(pixmap),
					  widget->style->
					  fg_gc[GTK_WIDGET_STATE(widget)],
					  0, 0, (110 + 80 * i),
					  (270 - 13 * j), 30, 30,
					  GDK_RGB_DITHER_NONE, 0, 0);
	}
    }
    for (i = 0; i < 3; i++)
	stos[i + 1] = dane[i];

    return TRUE;
}

void DisplayGame(GtkWidget * widget)
{
    int i, j;

    gdk_pixbuf_render_to_drawable(images[0], GDK_DRAWABLE(pixmap),
				  widget->style->
				  fg_gc[GTK_WIDGET_STATE(widget)], 0, 0, 0,
				  0, widget->allocation.width,
				  widget->allocation.height,
				  GDK_RGB_DITHER_NONE, 0, 0);

    for (i = 1; i <= 3; i++) {
	for (j = stos[i]; j > 0; j--) {
	    gdk_pixbuf_render_to_drawable(images[1], GDK_DRAWABLE(pixmap),
					  widget->style->
					  fg_gc[GTK_WIDGET_STATE(widget)],
					  0, 0, (30 + 80 * i),
					  (270 - 13 * j), 30, 30,
					  GDK_RGB_DITHER_NONE, 0, 0);

	}
    }
    gtk_widget_queue_draw_area(widget, 0, 0, 400, 300);
}


gboolean expose_event(GtkWidget * widget, GdkEventExpose * event)
{
    gdk_draw_drawable(widget->window,
		      widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
		      pixmap,
		      event->area.x, event->area.y,
		      event->area.x, event->area.y,
		      event->area.width, event->area.height);

    return FALSE;
}

void AnnounceResults(GtkWidget * widget)
{

    int i, j;

    gdk_pixbuf_render_to_drawable(images[0], GDK_DRAWABLE(pixmap),
				  widget->style->
				  fg_gc[GTK_WIDGET_STATE(widget)], 0, 0, 0,
				  0, widget->allocation.width,
				  widget->allocation.height,
				  GDK_RGB_DITHER_NONE, 0, 0);
    for (i = 1; i <= 3; i++) {
	for (j = stos[i]; j > 0; j--) {
	    gdk_pixbuf_render_to_drawable(images[1], GDK_DRAWABLE(pixmap),
					  widget->style->
					  fg_gc[GTK_WIDGET_STATE(widget)],
					  0, 0, (30 + 80 * i),
					  (270 - 13 * j), 30, 30,
					  GDK_RGB_DITHER_NONE, 0, 0);

	}
    }
    if (dane[4]) {
	i = 2;

	gdk_pixbuf_render_to_drawable(images[i], GDK_DRAWABLE(pixmap),
				      widget->style->
				      fg_gc[GTK_WIDGET_STATE(widget)],
				      0, 0, 50,
				      10, 250, 250,
				      GDK_RGB_DITHER_NONE, 0, 0);
    } else {
	i = 3;
	gdk_pixbuf_render_to_drawable(images[i], GDK_DRAWABLE(pixmap),
				      widget->style->
				      fg_gc[GTK_WIDGET_STATE(widget)],
				      0, 0, 50,
				      10, 250, 250,
				      GDK_RGB_DITHER_NONE, 0, 0);
    }

    gtk_widget_queue_draw_area(widget, 0, 0, 400, 300);
}

void show_warning(void)
{
    if (otherwin)
	return;
    otherwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(otherwin), "Uwaga!");
    gtk_window_set_resizable(GTK_WINDOW(otherwin), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(otherwin), 10);
    label =
	gtk_label_new
	("Zmiany zostaną zaakceptowane dopiero po wybraniu opcji \"Nowa gra\".");
    box1 = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(box1);
    gtk_container_add(GTK_CONTAINER(otherwin), box1);
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box1), label, TRUE, TRUE, 0);
    button = gtk_button_new_with_label("Zamknij");
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
			     G_CALLBACK(gtk_widget_destroy),
			     G_OBJECT(otherwin));

    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    gtk_widget_show(otherwin);
    g_signal_connect(G_OBJECT(otherwin), "destroy",
		     G_CALLBACK(win_close), NULL);
}
