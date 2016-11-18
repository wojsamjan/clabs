#include <gtk/gtk.h>
#include "main.h"
#include "gui.h"

void quick_message(const gchar* message)
{
       GtkWidget *dialog, *label;
       dialog = gtk_dialog_new_with_buttons ("Informacja",
                                             GTK_WINDOW(main_window),
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_STOCK_OK,
                                             GTK_RESPONSE_NONE,
                                             NULL);
       label = gtk_label_new (message);
       g_signal_connect_swapped (GTK_OBJECT (dialog), 
                                 "response", 
                                 G_CALLBACK (gtk_widget_destroy),
                                 GTK_OBJECT (dialog));
       gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                          label);
       gtk_widget_show_all (dialog);
}

