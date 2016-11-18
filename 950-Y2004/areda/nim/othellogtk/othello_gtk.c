#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <stdio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "othello.h"
#include "othello_gtk.h"
#include "minimax.h"
#include "main.h"

static GdkPixmap *pixmap=NULL;
gint gameover;

void pop_up_window(gchar *title, gchar *text)
{
	GtkWidget *dialog, *label;
	/* tu powstaje wyskakuj±ce okienko */
	dialog = gtk_dialog_new_with_buttons (title, GTK_WINDOW(window), 
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_CLOSE, GTK_RESPONSE_NONE, NULL);
	/* po naci¶niêciu przycisku zamyka siê */
	g_signal_connect_swapped (GTK_OBJECT (dialog), "response",  
			G_CALLBACK (gtk_widget_destroy), GTK_OBJECT (dialog));
	label = gtk_label_new (text);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show_all (dialog);
}

/********* obsluga zdarzeñ na drawing_area ****************/

/* Create a new backing pixmap of the appropriate size */
gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event )
{
  if (pixmap)
    g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window, 8*ICON_WIDTH, 8*ICON_HEIGHT, -1);
  print_game(widget);
  return TRUE;
}


/* Redraw the screen from the backing pixmap */
gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  gdk_draw_drawable (widget->window,
                     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                     pixmap,
                     event->area.x, event->area.y,
                     event->area.x, event->area.y,
                     event->area.width, event->area.height);
  return FALSE;
}


void invalidate_all(GtkWidget* widget)
{     
	GdkRectangle r = { 0, 0, 0, 0 };
	gdk_drawable_get_size(GDK_DRAWABLE(widget->window), &r.width, &r.height);
	gdk_window_invalidate_rect(GDK_WINDOW(widget->window), &r, FALSE);
}    

void invalidate_in_pos(GtkWidget* widget, moveT pt)
{     
	GdkRectangle r;
	gint w,h;
	gdk_drawable_get_size(GDK_DRAWABLE(widget->window), &w, &h);
	r.x=(pt.x-1) * ICON_WIDTH;
	r.y=(pt.y-1) * ICON_HEIGHT;
	r.width = ICON_WIDTH;
	r.height = ICON_HEIGHT;
	gdk_window_invalidate_rect(GDK_WINDOW(widget->window), &r, FALSE);
}     

void print_icon_in_pos(GtkWidget *widget, GdkPixbuf *pixbuf, int posx,int posy)
{	
	gdk_pixbuf_render_to_drawable(pixbuf, GDK_DRAWABLE(pixmap),
		  widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
		  0,0,
		  (posx-1)*ICON_WIDTH, (posy-1)*ICON_HEIGHT,
		  ICON_WIDTH, ICON_HEIGHT,
		  GDK_RGB_DITHER_NONE, 0, 0);
}

void ComputerMove(GtkWidget *widget, stateT state)
{
	moveT move;
	char changes[8];

	move=ChooseComputerMove(state);
	if (move.x == -1)
		pop_up_window("UWAGA!", "\nNie moge wykonac ruchu.\n");

	MakeMove(state, move, changes);
	print_part_of_game(widget, move, changes);
}

void AnnounceResults(stateT state)
{
  gameover = TRUE;
  if (CheckForWin(state,Human)) {
    pop_up_window("Koniec Gry","\n  Wygrales mistrzu!  \n");
  } else if (CheckForWin(state,Computer)) {
    pop_up_window("Koniec Gry", "\n  Juhuuuu... Wygralem :)  \n");
  } else {
    pop_up_window("Koniec Gry", "\n  Remis  \n");
  }
}

gint button_press_event (GtkWidget *widget, GdkEventButton *event)
{
	moveT move;
	char changes[8];

	if (event->button == 1 && pixmap != NULL && gameover == FALSE)
	{		  
		move.x =(event->x / ICON_WIDTH) +1;
      		move.y =(event->y / ICON_HEIGHT) +1;		
			
		if(NoLegalMoves(state))
		{
			pop_up_window("UWAGA!","\nPrzykro mi ale nie mozesz wykonac zadnego ruchu\n");
			move.x=-1;
		}
		else if (!MoveIsLegal(move, state))
		{
			return TRUE;
		}
		MakeMove(state, move, changes);
//		print_game(widget);
		print_part_of_game(widget, move, changes);

		while (gtk_events_pending ())
	        	gtk_main_iteration ();
		if(GameIsOver(state)) 
		{
			AnnounceResults(state);
			return TRUE;	
		}

		ComputerMove(widget, state);

		if(GameIsOver(state)) 
		{
			AnnounceResults(state);
			return TRUE;	
		}
		
	}
	  
	return TRUE;
}

GdkPixbuf *choose_bg(char znak)
{
	switch (znak){
		case ' ': return tlo;
			  break;
		case 'o': return biale;
			  break;
		case 'x': return czarne;
			  break;
	}	
	return tlo;
}

void print_game(GtkWidget *widget)
{
	int x,y;
	for(y=1; y<=8; y++)
		for(x=1; x<=8; x++)
		print_icon_in_pos(widget, choose_bg(state->board[y][x]), x, y);
	invalidate_all(widget);
}			 

void print_part_of_game(GtkWidget *widget, moveT move, char *changes)
{
	int dir, i, y,x;
	moveT adjMove;

	for(y=1; y<=8; y++)
		for(x=1; x<=8; x++)
		print_icon_in_pos(widget, choose_bg(state->board[y][x]), x, y);
	
	invalidate_in_pos(widget, move);
	for(dir=0; dir<8; dir++)
	{
		adjMove=AdjacentPoint(move, dir);
		for(i=0; i<changes[dir]; i++)
		{
			invalidate_in_pos(widget, adjMove);
			adjMove=AdjacentPoint(adjMove, dir);
		}
	}      
	
}
