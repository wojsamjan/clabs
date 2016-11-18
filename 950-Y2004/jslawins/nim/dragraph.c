/* Jakub S³awiñski 13.12.2003 r.
 * plik implementuj±cy obs³ugê grafiki w warcabach
 * dragraph.c
 */

#include <stdlib.h>
#include <gtk/gtk.h>

#include "dragraph.h"
#include "dramm.h"
#include "draughts.h"

static GdkPixbuf *images[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static GdkPixmap *pixmap = NULL;
static GtkWidget *otherwin = NULL;
static GtkWidget *label = NULL;
static GtkListStore *model = NULL;
extern GtkWidget *info;
extern GtkWidget *list;
extern chessboardT board;
static int transported;
static int inserted;

/* load_image
 * ³aduje do pamiêci obraz z pliku
 */

void
load_image( GtkWidget *widget, GdkPixbuf **pixbuf, const char* filename)
{	
	*pixbuf = gdk_pixbuf_new_from_file (filename, NULL);

	
	if (*pixbuf == NULL) {
		g_print("Can't load image: %s\n", filename);
		exit(1);
	}

	
}

/* configure_event
 * funkcja wywo³ywana przez gtk przy pierwszym pojawieniu siê drawing_area
 */

gboolean 
configure_event( GtkWidget *widget, GdkEventConfigure *event )
{
	int i;
	load_image(widget, &images[0], "images/chessboard.xpm");
	load_image(widget, &images[2], "images/white_checker.xpm");
	load_image(widget, &images[1], "images/red_checker.xpm");
	load_image(widget, &images[4], "images/white_queen.xpm");
	load_image(widget, &images[3], "images/red_queen.xpm");
	load_image(widget, &images[6], "images/red_win.xpm");
	load_image(widget, &images[5], "images/white_win.xpm");
	
  if (pixmap)
    g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
			   widget->allocation.width,
			   widget->allocation.height,
			   -1);

	gdk_pixbuf_render_to_drawable (images[0], GDK_DRAWABLE (pixmap),
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			0, 0, 0, 0, widget->allocation.width, widget->allocation.height,
			GDK_RGB_DITHER_NONE, 0, 0);

  for (i = 0; i < 24; ++i) {
	  draw_square (widget, board.checkers[i].pos.x, board.checkers[i].pos.y, (i/12)+1);
  }

  return TRUE;
}

/* expose_event
 * funkcja wywo³ywana przez gtk przy zmianie zawarto¶ci ekranu
 */

gboolean
expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  gdk_draw_drawable (widget->window,
		     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		     pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);

  return FALSE;
}

/* announce_result
 * funkcja wy¶wietla na ekranie, kto wygra³
 */

void
announce_result( GtkWidget *widget, int type)
{
  gdk_pixbuf_render_to_drawable (images[type], GDK_DRAWABLE (pixmap),
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			0, 0, 100, 100, 200, 200, GDK_RGB_DITHER_NONE, 0, 0);
	
  gtk_widget_queue_draw_area (widget, 
		      100, 100, 200, 200);
}

/* redraw_square
 * funkcja przerysowuje dany fragment szachownicy
 */

void
redraw_square(GtkWidget* widget, char x, char y)
{
	pointT pos;
	pos.x = x;
	pos.y = y;
	draw_square(widget, pos.x * 50 + 25, pos.y * 50 + 25, board.board[(int) x][(int) y]);
}

/* draw_square
 * funkcja kolejkuje do rysowania dany fragment ekranu
 */

void
draw_square( GtkWidget *widget, gdouble x, gdouble y, int type)
{
  GdkRectangle update_rect;
  pointT offset;

  if (is_outside((int) x, (int) y))
	  return;

  update_rect.x = x - 25;
  update_rect.y = y - 25;
  update_rect.width = offset.x = 50;
  update_rect.height = offset.y = 50;

  if (update_rect.x < 0) {
	  update_rect.width += update_rect.x;
	  offset.x += update_rect.x;
	  update_rect.x = 0;
  }
  if (update_rect.y < 0) {
	  update_rect.height += update_rect.y;
	  offset.y += update_rect.y;
	  update_rect.y = 0;
  }
  if (update_rect.x + update_rect.width >= 400) {
	  update_rect.width = 400 - update_rect.x - 1;
	  offset.x = 50;
  }
  if (update_rect.y + update_rect.height >= 400) {
	  update_rect.height = 400 - update_rect.y - 1;
	  offset.y = 50;
  }
	gdk_pixbuf_render_to_drawable (images[type], GDK_DRAWABLE (pixmap),
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			(!type)?update_rect.x:50-offset.x,
			(!type)?update_rect.y:50-offset.y,
			update_rect.x, update_rect.y,
			update_rect.width, update_rect.height,
			GDK_RGB_DITHER_NONE, 0, 0);
	
  gtk_widget_queue_draw_area (widget, 
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
}

/* button_press_event
 * funkcja wywo³ywana przy naci¶niêciu klawisza myszy
 */

gboolean
button_press_event( GtkWidget *widget, GdkEventButton *event )
{
  if (event->button == 1 && pixmap != NULL) {
	  if ((transported = is_checker( (int) event->x, (int) event->y, board.player)) != 24) {
		  if (board.checkers[transported].legal == 0) {
			  return TRUE;
		  }
			  board.checkers[transported].state = 1;
  board.board[board_square(board.checkers[transported].back.x, board.checkers[transported].back.y).x]
	     [board_square(board.checkers[transported].back.x, board.checkers[transported].back.y).y] = 0;
	  }
  }
  
  return TRUE;
}

/* button_release_event
 * funkcja wywo³ywana przy puszczeniu klawisza myszy
 */

gboolean
button_release_event( GtkWidget *widget, GdkEventButton *event )
{
	int result, xdel, ydel;
	gchar* msg;
	pointT newxy, oldxy, resxy;
  if (event->button == 1 && pixmap != NULL)
	  if ((transported != 24) && (board.checkers[transported].state != 0)) {
		  newxy = board.checkers[transported].pos;
		  oldxy = board.checkers[transported].back;
		draw_square (widget, newxy.x, newxy.y, 0);
		
	if (!is_outside(newxy.x-25, newxy.y-25))
	draw_square (widget,square_centre(newxy.x-25, newxy.y-25).x,square_centre(newxy.x-25, newxy.y-25).y,
		board.board[board_square(newxy.x-25, newxy.y-25).x][board_square(newxy.x-25, newxy.y-25).y]);
	if (!is_outside(newxy.x+25, newxy.y-25))
	draw_square (widget,square_centre(newxy.x+25, newxy.y-25).x,square_centre(newxy.x+25, newxy.y-25).y,
		board.board[board_square(newxy.x+25, newxy.y-25).x][board_square(newxy.x+25, newxy.y-25).y]);
	if (!is_outside(newxy.x-25, newxy.y+25))
	draw_square (widget,square_centre(newxy.x-25, newxy.y+25).x,square_centre(newxy.x-25, newxy.y+25).y,
		board.board[board_square(newxy.x-25, newxy.y+25).x][board_square(newxy.x-25, newxy.y+25).y]);
	if (!is_outside(newxy.x+25, newxy.y+25))
	draw_square (widget,square_centre(newxy.x+25, newxy.y+25).x,square_centre(newxy.x+25, newxy.y+25).y,
		board.board[board_square(newxy.x+25, newxy.y+25).x][board_square(newxy.x+25, newxy.y+25).y]);
	

		newxy.x = board.checkers[transported].pos.x = event->x;
		newxy.y = board.checkers[transported].pos.y = event->y;
		if ((result = is_allowed_move( newxy.x, newxy.y, oldxy.x, oldxy.y,
						board.checkers[transported].type))) {
			board.newgamepending = 0;
			/* human move */
			if (result == 2) {
				msg = g_strdup_printf("%c%c : %c%c", board_square(oldxy.x,oldxy.y).x + 'A',
					'8' - board_square(oldxy.x, oldxy.y).y,
						board_square(newxy.x,newxy.y).x + 'A',
					'8' - board_square(newxy.x, newxy.y).y);
				if (board.state) {
					insert_to_list(msg, 0);
				}
				else {
					insert_to_list(msg, 1);
				}
				g_free(msg);

				resxy.x = (board_square(newxy.x,newxy.y).x+board_square(oldxy.x,oldxy.y).x)/2;
				resxy.y = (board_square(newxy.x,newxy.y).y+board_square(oldxy.x,oldxy.y).y)/2;
				board.board[resxy.x][resxy.y] = 0;
				resxy.x = resxy.x * 50 + 25;
				resxy.y = resxy.y * 50 + 25;
				draw_square (widget, resxy.x, resxy.y, 0);
				board.checkers[is_checker(resxy.x, resxy.y, 0)].type = 0;
			}
			else if (result == 4) {
				msg = g_strdup_printf("%c%c : %c%c", board_square(oldxy.x,oldxy.y).x + 'A',
					'8' - board_square(oldxy.x, oldxy.y).y,
						board_square(newxy.x,newxy.y).x + 'A',
					'8' - board_square(newxy.x, newxy.y).y);
				if (board.state) {
					insert_to_list(msg, 0);
				}
				else {
					insert_to_list(msg, 1);
				}
				g_free(msg);

				if (newxy.x > oldxy.x) {
					xdel = 1;
				}
				else {
					xdel = -1;
				}
				if (newxy.y > oldxy.y) {
					ydel = 1;
				}
				else {
					ydel = -1;
				}
				resxy = board_square(oldxy.x, oldxy.y);
				newxy = board_square(newxy.x, newxy.y);
				resxy.x = resxy.x + xdel;
				resxy.y = resxy.y + ydel;
				while ((resxy.x != newxy.x) || (resxy.y != newxy.y)) {
					if (board.board[resxy.x][resxy.y] != 0) {
						board.board[resxy.x][resxy.y] = 0;
						redraw_square (widget, resxy.x, resxy.y);
				board.checkers[is_checker(resxy.x * 50 + 25, resxy.y * 50 + 25, 0)].type = 0;
					}
					resxy.x += xdel;
					resxy.y += ydel;
				}
			}
			else {
			msg = g_strdup_printf("%c%c - %c%c", board_square(oldxy.x,oldxy.y).x + 'A',
					'8' - board_square(oldxy.x, oldxy.y).y,
						board_square(newxy.x,newxy.y).x + 'A',
					'8' - board_square(newxy.x, newxy.y).y);
			insert_to_list(msg, 1);
			g_free(msg);
			}
			board.checkers[transported].pos  = 
				board.checkers[transported].back = 
			square_centre(board.checkers[transported].pos.x, board.checkers[transported].pos.y);
			board.data = board_square(board.checkers[transported].pos.x,
						  board.checkers[transported].pos.y);
	board.board[board_square(board.checkers[transported].pos.x, board.checkers[transported].pos.y).x]
	     [board_square(board.checkers[transported].pos.x, board.checkers[transported].pos.y).y] = 
	               board.checkers[transported].type;
			if (((result == 2) || (result == 4)) &&
		(is_next_break(board.checkers[transported].type))) {
				board.state = 1;
				unlegalize_moves();
				legalize_move(board.data.x, board.data.y);
			}
			else {
				board.state = 0;
					gtk_label_set_text (GTK_LABEL (info), "turn: RED");
					if (board_square(board.checkers[transported].pos.x,
								board.checkers[transported].pos.y).y == 0) {
						if (board.checkers[transported].type < 3) {
			msg = g_strdup_printf("--> Queen");
			insert_to_list(msg, 0);
			g_free(msg);
							board.checkers[transported].type += 2;
	board.board[board_square(board.checkers[transported].pos.x, board.checkers[transported].pos.y).x]
	     [board_square(board.checkers[transported].pos.x, board.checkers[transported].pos.y).y] = 
	               board.checkers[transported].type;
						}
					}
		draw_square (widget, board.checkers[transported].pos.x, board.checkers[transported].pos.y,
			board.checkers[transported].type);
		board.checkers[transported].state = 0;
			while (gtk_events_pending ())
				  gtk_main_iteration ();
				/* computer move */
				if (OpponentMove(widget))
					return TRUE;
				/* end of computer move */
					gtk_label_set_text (GTK_LABEL (info), "turn: WHITE");
			}
		}
		else {
			board.checkers[transported].pos = board.checkers[transported].back;
  board.board[board_square(board.checkers[transported].back.x, board.checkers[transported].back.y).x]
	     [board_square(board.checkers[transported].back.x, board.checkers[transported].back.y).y] =
	     board.checkers[transported].type;
			
		}
		draw_square (widget, board.checkers[transported].pos.x, board.checkers[transported].pos.y,
			board.checkers[transported].type);
		board.checkers[transported].state = 0;
	  }

  return TRUE;
}

/* motion_notify_event
 * funkcja wywo³ywana przy poruszeniu mysz±
 */

gboolean
motion_notify_event( GtkWidget *widget, GdkEventMotion *event )
{
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      state = event->state;
    }
    
  if (state & GDK_BUTTON1_MASK && pixmap != NULL) {
	  if ((transported != 24) && (board.checkers[transported].state == 1)) {
		draw_square (widget, board.checkers[transported].pos.x, board.checkers[transported].pos.y, 0);
	
	if (!is_outside(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y-25)) {
		draw_square (widget,
		square_centre(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y-25).x,
		square_centre(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y-25).y,
board.board[board_square(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y-25).x]
  	   [board_square(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y-25).y]);
	}
	
	if (!is_outside(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y-25)) {
		draw_square (widget,
		square_centre(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y-25).x,
		square_centre(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y-25).y,
board.board[board_square(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y-25).x]
  	   [board_square(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y-25).y]);
	}
	
	if (!is_outside(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y+25)) {
		draw_square (widget,
		square_centre(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y+25).x,
		square_centre(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y+25).y,
board.board[board_square(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y+25).x]
  	   [board_square(board.checkers[transported].pos.x-25, board.checkers[transported].pos.y+25).y]);
	}
	
	if (!is_outside(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y+25)) {
		draw_square (widget,
		square_centre(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y+25).x,
		square_centre(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y+25).y,
board.board[board_square(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y+25).x]
  	   [board_square(board.checkers[transported].pos.x+25, board.checkers[transported].pos.y+25).y]);
	}
		
		board.checkers[transported].pos.x = event->x;
		board.checkers[transported].pos.y = event->y;
		draw_square (widget, x, y, board.checkers[transported].type);
	  }
  }
  
  return TRUE;
}

/* start
 * funkcja wywo³ywana przy naci¶nieciu opcji 'New Game'
 */

void
start (GtkWidget *widget)
{
	int i;
  NewGame(); 
	gtk_label_set_text (GTK_LABEL (info), "turn: WHITE");
	gdk_pixbuf_render_to_drawable (images[0], GDK_DRAWABLE (pixmap),
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			0, 0, 0, 0, widget->allocation.width, widget->allocation.height,
			GDK_RGB_DITHER_NONE, 0, 0);

  gtk_widget_queue_draw_area (widget, 
		      0, 0, 400, 400);
  for (i = 0; i < 24; ++i) {
	  draw_square (widget, board.checkers[i].pos.x, board.checkers[i].pos.y, (i/12)+1);
  }

}

/* quit
 * funkcja wywo³ywana przy naci¶nieciu opcji 'Exit'
 */

void
quit ()
{
  exit (0);
}

/* win_quit
 * funkcja wywo³ywana przy zamkniêciu okna z zasadami b±dz about
 */

void
win_quit()
{
	otherwin = NULL;
}

/* show_rules
 * funkcja wy¶wietlaj±ca na ekranie okno z zasadami
 */

void
show_rules()
{
	if (otherwin)
		return;
  otherwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (otherwin), "Rules");
  gtk_window_set_resizable (GTK_WINDOW (otherwin), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (otherwin), 5);
  label = gtk_label_new ("Zasady gry w Simple draughts:\n\n" \
		  	 "1. GrÄ™ rozpoczyna czÅ‚owiek (biaÅ‚e piony)\n" \
			 "2. Nie moÅ¼na zrezygnowaÄ‡ z ruchu\n" \
			 "3. Trzeba zawsze biÄ‡ najwiÄ™kszÄ… moÅ¼liwÄ… iloÅ›Ä‡ pionÃ³w przeciwnika\n" \
			 "4. Gra koÅ„czy siÄ™, gdy ktÃ³ryÅ› z graczy nie ma moÅ¼liwoÅ›ci ruchu\n");
  gtk_container_add (GTK_CONTAINER (otherwin), label);
  gtk_widget_show (label);
  gtk_widget_show (otherwin);
  g_signal_connect (G_OBJECT (otherwin), "destroy",
                    G_CALLBACK (win_quit), NULL);
}

/* show_about
 * funkcja wy¶wietlaj±ca okno about
 */

void
show_about()
{
	if (otherwin)
		return;
  otherwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (otherwin), "About");
  gtk_window_set_resizable (GTK_WINDOW (otherwin), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (otherwin), 5);
  label = gtk_label_new ("Slaughter House Entertainment Group\n\npresents\n\nSimple draughts v0.1");
  gtk_label_set_justify ( GTK_LABEL (label), GTK_JUSTIFY_CENTER );
  gtk_container_add (GTK_CONTAINER (otherwin), label);
  gtk_widget_show (label);
  gtk_widget_show (otherwin);
  g_signal_connect (G_OBJECT (otherwin), "destroy",
                    G_CALLBACK (win_quit), NULL);

}

/* change_reclevel
 * funkcja zmienia maksymalny poziom rekursji
 */

static void
change_reclevel( GtkWidget *widget, GtkSpinButton *spin )
{ 
	  board.reclevel = gtk_spin_button_get_value_as_int (spin);
} 


/* show_config
 * funkcja wy¶wietlaj±ca okno konfiguracji warcabów
 */

void
show_config()
{
	GtkWidget* vbox;
	GtkWidget* hbox;
	GtkWidget* spinner;
  	GtkAdjustment *adj;
	GtkWidget* button;
  
	
	if (otherwin)
		return;
  otherwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (otherwin), "Configuration");
  gtk_window_set_resizable (GTK_WINDOW (otherwin), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (otherwin), 5);
  /* vbox */
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (otherwin), vbox);
  /* label */
  label = gtk_label_new ("Maksymalny poziom rekursji:");
  gtk_label_set_justify ( GTK_LABEL (label), GTK_JUSTIFY_CENTER );
  gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 5);
  /* spinner */
  adj = (GtkAdjustment *) gtk_adjustment_new (board.reclevel, 1, 1000, 1, 10, 0);
  spinner = gtk_spin_button_new (adj, 1.0, 2);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinner), TRUE);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (spinner), 0);
  gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), FALSE);
  gtk_widget_set_size_request (spinner, 100, -1);
  gtk_box_pack_start (GTK_BOX (vbox), spinner, FALSE, TRUE, 0);
  /* hbox */
  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);
  /* button ok */
  button = gtk_button_new_with_label ("Ok");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 5);
  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (change_reclevel), (gpointer) spinner);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",
                    G_CALLBACK (gtk_widget_destroy), G_OBJECT (otherwin));
  gtk_widget_show (button);
  /* button anuluj */
  button = gtk_button_new_with_label ("Anuluj");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 5);
  gtk_widget_show (hbox);
  gtk_widget_show (button);
  gtk_widget_show (spinner);
  gtk_widget_show (vbox);
  gtk_widget_show (label);
  gtk_widget_show (otherwin);
  
  g_signal_connect (G_OBJECT (otherwin), "destroy",
                    G_CALLBACK (win_quit), NULL);
  g_signal_connect_swapped (G_OBJECT (button), "clicked",
                    G_CALLBACK (gtk_widget_destroy), G_OBJECT (otherwin));
      
}


/* create_list
 * funkcja tworz±ca listê potrzebn± do wy¶wietlania wykonanych ruchów
 */

GtkWidget*
create_list( void )
{

    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    
    model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window),
                                           tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);
 
    cell = gtk_cell_renderer_text_new ();
   
    column = gtk_tree_view_column_new_with_attributes ("Moves",
                                                       cell,
                                                       "text", 0,
                                                       NULL);
   
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
                                 GTK_TREE_VIEW_COLUMN (column));
    return scrolled_window;
}

/* insert_to_list
 * funkcja wk³adaj±ca do listy podany napis
 */

void
insert_to_list(gchar* msg, char mode)
{
	GString* string;
	GtkTreeIter iter;
	string = g_string_new("");
	if (mode) {
		inserted++;
		g_string_printf(string, "%d. ", inserted);
	}
	else {
		g_string_printf(string, "    ");
	}
	g_string_append(string, msg);
        gtk_list_store_append (GTK_LIST_STORE (model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (model),
                            &iter,
                            0, g_string_free(string, FALSE),
                            -1);
}

/* clear_moves_list
 * funkcja kasuj±ca zawarto¶æ listy z wykonanymi ruchami
 */

void
clear_moves_list()
{
	inserted = 0;
	if (list)
		gtk_list_store_clear( GTK_LIST_STORE (model) );
}
