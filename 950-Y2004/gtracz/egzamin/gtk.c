#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include "gui.h"

int main(int argc, char *argv[]){
  gtk_init(&argc,&argv);

  window();

  gtk_main();

  return 0;
}
