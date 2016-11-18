#include <gdk/gdk.h>
#include <gdk/gdktypes.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <math.h>
#include "draw.h"
#include "mazelib.h"
#include "random.h"
#include "maze.h"

/* Pixmapa, na której wszystko rysujemy */
static GdkPixmap* MAIN_PIXMAP;

/* Obrazki z ikonkami */
static GdkPixbuf* terrain_tiles(void);
static GdkPixbuf* road_tiles(void);

/* Pozycja ¿±danych ikonek w obrazkach */
static pointT get_icon_position(int terrain_type, pointT pt, GdkPixbuf** buf);
static pointT get_icon_marked_pos(pointT pt);

/* Rysuj t³o labiryntu */
static void draw_background(GtkWidget* widget);

void update_view(GtkWidget* widget)
{
      int w, h;

      if (MAIN_PIXMAP != NULL)
            gdk_pixmap_unref(MAIN_PIXMAP);
      gtk_layout_get_size(GTK_LAYOUT(widget), &w, &h);
      MAIN_PIXMAP = gdk_pixmap_new(GTK_LAYOUT(widget)->bin_window, w, h, -1);
      gdk_draw_rectangle(MAIN_PIXMAP, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], TRUE, 0, 0, w, h);
      draw_background(widget);
      draw_pixmap(widget);
}

gint on_expose_event(GtkWidget* widget, GdkEventExpose* event)
{
      gdk_draw_drawable(GTK_LAYOUT(widget)->bin_window,
                      widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
                      MAIN_PIXMAP,
                      event->area.x, event->area.y,
                      event->area.x, event->area.y,
                      event->area.width, event->area.height);
      return FALSE;
}

static void draw_background(GtkWidget* widget)
{
      int lines = mazeLines();
      int i, j;

      for (i = 0; i < lines; ++i)
            for (j = 0; j < mazeLineLength(i); ++j)
                  draw_icon_in_pos(widget, TERRAIN_NORMAL, j, i);
}

void draw_pixmap(GtkWidget* widget)
{
      int lines = mazeLines();
      int i, j;
      pointT temp;

      for (i = 0; i < lines; ++i)
            for (j = 0; j < mazeLineLength(i); ++j) {
                  temp.y = i;
                  temp.x = j;
                  if (GetTerrain(temp) != TERRAIN_NORMAL)
                        draw_icon_in_pos(widget, GetTerrain(temp), j, i);
            }
}

void draw_icon_in_pos(GtkWidget* widget, int terrain_type, int xpos, int ypos)
{
      pointT temp, srcpt;
      GdkPixbuf* buf;

      temp.x = xpos; temp.y = ypos;
      srcpt = get_icon_position(terrain_type, temp, &buf);
      gdk_pixbuf_render_to_drawable(buf, GDK_DRAWABLE(MAIN_PIXMAP),
                                    widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
                                    srcpt.x, srcpt.y,
                                    xpos * ICON_WIDTH, ypos * ICON_HEIGHT,
                                    ICON_WIDTH, ICON_HEIGHT,
                                    GDK_RGB_DITHER_NONE, 0, 0);
}

static GdkPixbuf* terrain_tiles(void)
{
      static GdkPixbuf* tiles = NULL;
      if (tiles == NULL)
            tiles = gdk_pixbuf_new_from_file("tiles.png", NULL);
      return tiles;
}

static GdkPixbuf* road_tiles(void)
{
      static GdkPixbuf* roads = NULL;
      if (roads == NULL)
            roads = gdk_pixbuf_new_from_file("roads.png", NULL);
      return roads;
}

static pointT get_icon_position(int terrain_type, pointT pt, GdkPixbuf** buf)
{
      pointT temp = {0, 0};
      *buf = terrain_tiles();

      switch (terrain_type) {
            case TERRAIN_NORMAL:
                  temp.y = 30; //temp.x = random_integer(0, 16) * ICON_WIDTH;
                  temp.x = 30;
                  return temp;
            case TERRAIN_WALL:
                  temp.x = 0; temp.y = 300;
                  return temp;
            case TERRAIN_MARKED:
                  *buf = road_tiles();
                  return get_icon_marked_pos(pt);
            case TERRAIN_START_POS:
                  temp.x = 14 * ICON_WIDTH;
                  temp.y = 12 * ICON_HEIGHT;
                  return temp;
            default:
                  return temp;
      }
}

/* Zwróæ warto¶æ informacj± o tym, które z s±siednich pól s± zaznaczone --
 * potrzebne do narysowania odpowiedniej drogi.
 * Ustawiamy 4 m³odsze bity bajtu, je¿eli który¶ z nich jest ustawiony, to
 * znaczy, ¿e pole s±siaduj±ce (w odpowiednim kierunku -- patrz funkcja
 * bit_shift) jest zaznaczone */
static char surrounding_marked(pointT pt)
{
      int bit_shift(directionT dir)
      {
            switch (dir) {
                  case North: return 3;
                  case East: return 2;
                  case South: return 1;
                  case West: return 0;
            }
            puts("nic");
            return 1;
      }

      int i;
      pointT temp;
      char b;

      b = 0;
      for (i = 0; i < 4; ++i) {
            temp = AdjacentPoint(pt, all_directions[i]);
            if (!OutsideMaze(temp) && IsMarked(temp))
                        b |= (1 << bit_shift(all_directions[i]));
      }
      return b;
}

pointT get_icon_marked_pos(pointT pt)
{
      pointT temp = {0, 0};
      char b = surrounding_marked(pt);

      temp.y = 2 * ICON_HEIGHT;
      switch (b) {
            case 0x1: case 0x5: case 0x4:
                  temp.x = 10 * ICON_WIDTH;
                  break;
            case 0xA: case 0x8: case 0x2:
                  temp.x = 5 * ICON_WIDTH;
                  break;
            case 0xF:
                  temp.x = 15 * ICON_WIDTH;
                  break;
            case 0xC:
                  temp.x = 3 * ICON_WIDTH;
                  break;
            case 0x6:
                  temp.x = 6 * ICON_WIDTH;
                  break;
            case 0x3:
                  temp.x = 12 * ICON_WIDTH;
                  break;
            case 0x9:
                  temp.x = 9 * ICON_WIDTH;
                  break;
            case 0x7:
                  temp.x = 14 * ICON_WIDTH;
                  break;
            case 0xB:
                  temp.x = 13 * ICON_WIDTH;
                  break;
            case 0xD:
                  temp.x = 11 * ICON_WIDTH;
                  break;
            case 0xE:
                  temp.x = 7 * ICON_WIDTH;
                  break;
      }
      return temp;
}

void invalidate_all(GtkWidget* widget)
{
      GdkRectangle r = { 0, 0, 0, 0 };

      gdk_drawable_get_size(GDK_DRAWABLE(GTK_LAYOUT(widget)->bin_window), &r.width, &r.height);
      gdk_window_invalidate_rect(GDK_WINDOW(GTK_LAYOUT(widget)->bin_window), &r, FALSE);
}


void invalidate_point(GtkWidget* widget, pointT pt)
{
      gint w, h;
      GdkRectangle r;

      gdk_drawable_get_size(GDK_DRAWABLE(GTK_LAYOUT(widget)->bin_window), &w, &h);
      r.x = pt.x * ICON_WIDTH;
      r.y = pt.y * ICON_HEIGHT;
      r.width = ICON_WIDTH;
      r.height = ICON_HEIGHT;
      gdk_window_invalidate_rect(GDK_WINDOW(GTK_LAYOUT(widget)->bin_window), &r, FALSE);
}

/* Ud¶wie¿ teren nie bêd±cy ¶cian± w odleg³o¶ci mniejszej
 * lub równej dwa od punktu 'pt' */
void invalidate_near(GtkWidget* widget, pointT pt)
{
      pointT temp;
      int i, j;
      int maxy = MIN(mazeLines(), pt.y + 3);
      int miny = MAX(0, pt.y - 2);
      int maxx;
      int minx = MAX(0, pt.x - 2);

      for (i = miny; i < maxy; ++i) {
            maxx = MIN(mazeLineLength(i), pt.x + 3);
            for (j = minx; j < maxx; ++j) {
                  temp.x = j; temp.y = i;
                  if (GetTerrain(temp) != TERRAIN_WALL)
                        invalidate_point(widget, temp);
            }
      }
}
