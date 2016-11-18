#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include "gui.h"
#include "pixmaps/wall.h"
#include "pixmaps/grass.h"
#include "pixmaps/step.h"
#include "pixmaps/exit.h"
#include "pixmaps/start.h"



typedef struct {
  void (*funkcja)();
  GtkWidget *plik;
} typDanePliku;

/* wielkosc ikonek */
gint SIZE=16;
char *NazwaPliku = "labirynt.txt";
GtkWidget *glowne_okno;
GtkWidget *toolbar;
GtkWidget *ypole;
gint maze;
GtkWidget *mazepole;
/*piksmapa na ktorej rysujemy obraz w tle*/
GdkPixmap *piksmapa = NULL;
GtkWidget *obszar_rys;
/*wartosc opoznienia*/
gint timeout=150;
pointT pt;
pointT newpt;
/*tablica krokow*/
pointT last[MAXLAB];
/*liczba krokow w labiryncie*/
int lcount=-1;
/*czy znalazl pole na ktore mozna wejsc
 * 1-znalazl
 *2-wyjscie
 */
int in=0;
/*parametr ktory okresla czy nalezy tylko wyswietlic 
 *labirynt opcja=0, lub rozwiazac go opcja=1
 */
int opcja=0;
/*najmniejsza liczba krokow*/
int kroki=0;

GdkBitmap *mwall16;
GdkBitmap *mgrass16;
GdkBitmap *mstep16;
GdkBitmap *mstart16;
GdkBitmap *mexit16;
GdkPixmap *wall16;
GdkPixmap *grass16;
GdkPixmap *step16;
GdkPixmap *start16;
GdkPixmap *exit16;

/* Prototypy funkcji */

/*wyjscie z programu*/
//gint koniec (gpointer dane, guint sygnal, GtkWidget *kontrolka);
gint ZamknijOkno(GtkWidget *kontrolka,gpointer dane);

/*wywolywany po kliknieciu Plik/Otworz*/
void menu_Otworz (GtkWidget *kontrolka, gpointer dane);

/*wyjscie z programu*/
void menu_Koniec (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Labirynt/Rozwiaz*/
void menu_Rozwiaz (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Labirynt/Najkrotsza...*/
void menu_Shortest (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Labirynt/Najkrotsza...*/
void menu_Clear (GtkWidget *kontrolka, gpointer dane);

/*generuje nowy labirynt*/
void menu_Generate (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Ustawienia/Opoznienie*/
void menu_Opoznienie (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Ustawienia/Powiekszenie*/
void menu_Powiekszenie (GtkWidget *kontrolka, gpointer dane);

/*wywolywany po kliknieciu Ustawienia/Pomniejszenie*/
void menu_Pomniejszenie (GtkWidget *kontrolka, gpointer dane);

/*wyswietla okienko z pomoca*/
void menu_Help(GtkWidget *kontrolka, gpointer dane);

/*wyswietla okienko z pomoca*/
void menu_Autor(GtkWidget *kontrolka, gpointer dane);

/*ustawia opznienie wybrane z listy*/
void UstawOpoznienie(void);

/*powieksza dany labirynt*/
void UstawPowiekszenie(void);

/*pomniejsza dany labirynt*/
void UstawPomniejszenie(void);

/*wywolywany po zamknieciu okna wyboru plikow
 *przez nacisniecie X a nie przez 'Anuluj'*/
void usun(GtkWidget *kontrolka, gpointer dane);

/*funkcja wyswietla okno wyboru plikow i pobiera nazwe
 *zaznaczonego pliku*/
void PobierzNazwePliku(char *Tytul, void (*fzwrotna)(char *));

/*jesli dany plik istnieje i da sie go otworzyc 
 *to ta funkcja wywoluje funkcje wyswietlajaca 
 *zawartosc pliku*/
void PlikOk(GtkWidget *kontrolka, gpointer dane);

/*funkcja wyswietla zawatrosc pliku*/
void OtworzPlik(char *NazwaPliku);

/*tworzy pasek menu na podstawie fabryki menu*/
void CreateMenu(void);

/* Wy¶wietla komunikat w oknie dialogowym
 */
void PokazKomunikat (char *szTytul, char *szKomunikat);

/* Zwalnia blokadê okna
 */
void UsunOknoKomunikatu (GtkWidget *kontrolka, gpointer dane);

/* Procedura zamykaj±ca okno dialogowe z komunikatem.
 */
void ZamknijOknoKomunikatu (GtkWidget *kontrolka, gpointer dane);

/* Funkcja ta wywolywana jest po odslonieciu okna albo po wywolaniu
 * funkcji gdk_widget_draw. Kopiuje drugoplanowa piksmape do okna.
 */
gint expose_event (GtkWidget *kontrolka, GdkEventExpose *zdarzenie);

/*Funkcja ta jest wywolywana po zmianie rozmiaru okna*/
static gint configure_event (GtkWidget *kontrolka, 
                             GdkEventConfigure *zdarzenie);




static GtkItemFactoryEntry menu[] =
{
  { "/_Plik",                           NULL,       0,                 0, "<Branch>" },
  //  { "/Plik/_Nowy",                      NULL,       koniec,            0, "<StockItem>", GTK_STOCK_NEW },
  { "/Plik/_Otworz",                    NULL,       menu_Otworz,       0, "<StockItem>", GTK_STOCK_OPEN },
  //  { "/Plik/_Zapisz",                    NULL,       koniec,            0, "<StockItem>", GTK_STOCK_SAVE },
  //  { "/Plik/Zapsz_Jako...",              NULL,       koniec,            0, "<StockItem>", GTK_STOCK_SAVE },
  { "/Plik/sep1",                       NULL,       0,                 0, "<Separator>" },
  { "/Plik/Za_koncz",                   NULL,       menu_Koniec,       0, "<StockItem>", GTK_STOCK_QUIT },

  { "/_Labirynt",                       NULL,       0,                 0, "<Branch>" },
  { "/_Labirynt/_Rozwiaz",              NULL,       menu_Rozwiaz,      0, "<StockItem>", GTK_STOCK_QUIT },
  { "/_Labirynt/_Najkrotsza droga",     NULL,       menu_Shortest,     0, "<StockItem>", GTK_STOCK_JUMP_TO },
  { "/_Labirynt/_Wyczysc",              NULL,       menu_Clear,        0, "<StockItem>", GTK_STOCK_CLEAR },
  { "/_Labirynt/_Generuj",              NULL,       menu_Generate,     0, "<StockItem>", GTK_STOCK_EXECUTE },

  { "/_Ustawienia",                     NULL,       0,                 0, "<Branch>" },
  { "/_Ustawienia/_Opoznienie",         NULL,       menu_Opoznienie,   0, "<StockItem>", GTK_STOCK_PREFERENCES },
  { "/_Ustawienia/_Powiekszenie",       NULL,       menu_Powiekszenie, 0, "<StockItem>", GTK_STOCK_ZOOM_IN },
  { "/_Ustawienia/_Pomniejszenie",      NULL,       menu_Pomniejszenie,0, "<StockItem>", GTK_STOCK_ZOOM_OUT },

  { "/_Pomoc",                          NULL,       0,                 0, "<LastBranch>" },
  { "/_Pomoc/_O programie",             NULL,       menu_Help,         0, "<StockItem>", GTK_STOCK_HELP },
  { "/_Pomoc/_Autor",                   NULL,       menu_Autor,        0 },
};

/*funkcje wywolywane z menu*/

void menu_Otworz (GtkWidget *kontrolka, gpointer dane){
  PobierzNazwePliku("Otworz",OtworzPlik);
}

void menu_Koniec (GtkWidget *kontrolka, gpointer dane){
  gtk_main_quit();
}

void menu_Rozwiaz (GtkWidget *kontrolka, gpointer dane){
  DrawMove(1);
}

void menu_Shortest (GtkWidget *kontrolka, gpointer dane){
  char lkrokow[256];
  kroki=ShortestPath(GetStartPosition());
  sprintf(lkrokow,"%d",kroki);
  //lkrokow="29";
  if (kroki==0)
    PokazKomunikat("Niestety","Niestety z tego labiryntu\nnie ma wyjscia");
  else{
    DrawMove(0);
    PokazKomunikat("Jest wyjscie!",lkrokow);
  }
  kroki=0;
}

void menu_Clear (GtkWidget *kontrolka, gpointer dane){
  OtworzPlik(NazwaPliku);
}

void menu_Generate (GtkWidget *kontrolka, gpointer dane){
  generate("temp.txt");
  NazwaPliku="temp.txt";
  OtworzPlik(NazwaPliku);
}

void menu_Opoznienie (GtkWidget *kontrolka, gpointer dane){
  UstawOpoznienie();
}

void menu_Powiekszenie (GtkWidget *kontrolka, gpointer dane){
  UstawPowiekszenie();
}

void menu_Pomniejszenie (GtkWidget *kontrolka, gpointer dane){
  UstawPomniejszenie();
}

void menu_Help(GtkWidget *kontrolka, gpointer dane){
  FILE *file;
  unsigned int n;
  char *linia = NULL;
  
  /* otwarcie pliku z zasadami gry */
  file=fopen("pixmaps/help.txt","r");
  
  getdelim(&linia, &n, EOF,  file);
  
  PokazKomunikat("Pomoc do programu", linia);
  free(linia);
  fclose(file);
}

void menu_Autor(GtkWidget *kontrolka, gpointer dane){
  PokazKomunikat("O Autorze","LABIRYNT v 2.0\n\nUniwersytet Gdanski\n\nGrzegorz Tracz \n");
}


/*funkcje zwrotne wywolywane przez rozne widgety*/

static gint configure_event (GtkWidget *kontrolka, 
                             GdkEventConfigure *zdarzenie)
{
    /* --- zwalniamy bufor, jezli go utworzylismy --- */
    if (piksmapa) {
        gdk_pixmap_unref (piksmapa);
    }

    /* --- tworzymy piksmape o nowych rozmiarach --- */
    piksmapa = gdk_pixmap_new (kontrolka->window,
                  kontrolka->allocation.width,
                  kontrolka->allocation.height,
                  -1);

    return TRUE;
}


gint expose_event (GtkWidget *kontrolka, GdkEventExpose *zdarzenie)
{

    /* --- Kopiujemy piksmape do okna --- */
    gdk_draw_pixmap (kontrolka->window,
         kontrolka->style->fg_gc[GTK_WIDGET_STATE (kontrolka)],
         piksmapa,
         zdarzenie->area.x, zdarzenie->area.y,
         zdarzenie->area.x, zdarzenie->area.y,
         zdarzenie->area.width, zdarzenie->area.height);

    return FALSE;
}

gint ZamknijOkno(GtkWidget *kontrolka,gpointer dane){
  gtk_main_quit();
  return (FALSE);
}

/*tworzenie menu*/

void CreateMenu(void){
  GtkItemFactory *fabryka;
  int l_elem=sizeof(menu)/sizeof(menu[0]);

  ypole = gtk_vbox_new (FALSE, 0);
  
  /* --- umieszczamy pole w oknie --- */
  gtk_container_add (GTK_CONTAINER (glowne_okno), ypole);


  fabryka=gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<bla>",NULL);

  gtk_item_factory_create_items(fabryka,l_elem,menu,NULL);

  gtk_box_pack_start (GTK_BOX (ypole), 
		      gtk_item_factory_get_widget(fabryka,"<bla>"),
		      FALSE, TRUE, 0);
  gtk_widget_show_all(glowne_okno);
}

/*tworzenie glownego okna*/

void window(void){
 
  glowne_okno = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title(GTK_WINDOW(glowne_okno),"LABIRYNT");
  
  CreateMenu();
  
  gtk_signal_connect (GTK_OBJECT (glowne_okno), "destroy",
		      GTK_SIGNAL_FUNC (ZamknijOkno), NULL);
  
  obszar_rys = gtk_drawing_area_new ();
   
  gtk_drawing_area_size (GTK_DRAWING_AREA (obszar_rys), 300, 500);

  gtk_box_pack_start (GTK_BOX (ypole), obszar_rys, TRUE, TRUE, 0);
  
  gtk_widget_show (obszar_rys);
 
  gtk_signal_connect(GTK_OBJECT(obszar_rys),"expose_event",
		     (GtkSignalFunc)expose_event,NULL);
  gtk_signal_connect(GTK_OBJECT(obszar_rys),"configure_event",
		     (GtkSignalFunc)configure_event,NULL);
  
  gtk_widget_show (glowne_okno);
  
  OtworzPlik(NazwaPliku);
  
}

/*obsluga otwierania plikow*/

void OtworzPlik(char *NazwaPliku){
  int z,l,maxx,maxy;

  ReadMazeMap(NazwaPliku);
  z=0;
  maxx=0;
  maxy=0;
  l=0;
  while (lab[z].stan!='\0'){
    if (lab[z].stan!='e')
      l++;
    else{
      if (maxx<=l)
	maxx=l;
      l=0;
      maxy++;
    }
    z++;
  }
  maxx=maxx*SIZE;
  maxy=maxy*SIZE;
  if (maxx>760 || maxy>580)
    PokazKomunikat("Uwaga !","Ten labirynt jest z duzy i moze nie zmiescic sie na ekranie.\n\nNalezy albo skorzystac z opcji 'Pomniejszenie' w menu 'Ustawienia'\n lub zaladowac mniejszy labirynt\n");
  gtk_drawing_area_size (GTK_DRAWING_AREA (obszar_rys),maxx, maxy);
  DrawMove(0);
}


void PlikOk(GtkWidget *kontrolka, gpointer dane){
  char *TempNazwa;
  typDanePliku *danelokalne;
  GtkWidget *kplik;
  danelokalne=(typDanePliku *)dane;
  kplik=danelokalne->plik;
  TempNazwa=gtk_file_selection_get_filename(GTK_FILE_SELECTION(kplik));

  NazwaPliku=g_strdup(TempNazwa);

  (*(danelokalne->funkcja))(NazwaPliku);

  gtk_widget_destroy(kplik);
}


void usun(GtkWidget *kontrolka, gpointer dane){
  gtk_grab_remove(kontrolka);
  g_free(dane);
}

void PobierzNazwePliku(char *Tytul, void (*fzwrotna)(char *)){
  GtkWidget *kplik=NULL;
  typDanePliku *dane;
  /* - tworzymy kontrolke wyboru pliku - */
  kplik=gtk_file_selection_new(Tytul);
  dane=g_malloc(sizeof(typDanePliku));
  dane->funkcja=fzwrotna;
  dane->plik=kplik;
  /* - zamkniecie okienka - */
  gtk_signal_connect(GTK_OBJECT(kplik),"destroy",
		     (GtkSignalFunc)usun,dane);
  /* - sygnal do klawisza 'anuluj' - */
  gtk_signal_connect_object(GTK_OBJECT(GTK_FILE_SELECTION
				(kplik)->cancel_button),
		     "clicked",(GtkSignalFunc)gtk_widget_destroy,
		     (gpointer)kplik);
  /* - sygnal do kalwisza 'ok' - */
  gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION
				(kplik)->ok_button),
		     "clicked",(GtkSignalFunc)PlikOk,dane);
  if (NazwaPliku)
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(kplik),
				    NazwaPliku);
  gtk_widget_show(kplik);
  gtk_grab_add(kplik);
}

/*rysowanie i rozwiazywanie labiryntu*/

gboolean DrawMaze(gpointer dane){
  GtkWidget *obszar = (GtkWidget *) dane;
  GdkRectangle uakt_prostokat;
  pointT finish;
  int z,x,y,g,dir,j;

 
  /* --- Czyscimy piksmape (rysujac drugoplanowy) --- */
  gdk_draw_rectangle (piksmapa,
		      obszar->style->white_gc,
		      TRUE,
		      0, 0,
		      obszar->allocation.width,
		      obszar->allocation.height);

  dir=Random(0,3);
  j=0;
  if (opcja==1){
    g=0;
    while (fin[g].x!=-1){
      finish.x=fin[g].x;
      finish.y=fin[g].y;
      lab[FindPoint(finish)].stan='W';
      g++;
    }
    in=0;
    while(j<4){
      dir=dir%4;
      j++;
      newpt=NPoint(pt,dir);
      if (lab[FindPoint(newpt)].stan=='w' || 
	  lab[FindPoint(newpt)].stan=='W'){
	lab[FindPoint(newpt)].stan='X';
	in=2;
	break;
      }
      if (lab[FindPoint(newpt)].odw==' '){
	in=1;
	MarkSquare(newpt);
      }
      if (in==1){
	lcount++;
	last[lcount].x=pt.x;
	last[lcount].y=pt.y;
	pt.x=newpt.x;
	pt.y=newpt.y;
	break;
      }
      dir++;
    }
    if (in==0){
      if (lcount!=-1){
	UnmarkSquare(pt);
	pt.x=last[lcount].x;
	pt.y=last[lcount].y;
	last[lcount].x='\0';
	last[lcount].y='\0';   
	lcount--;
	in=1;
      }else
	in=3;
    }
  }
  else
    in=2;
  z=0;
  x=0;
  y=0;
  g=0;
  if (in==3)
    PokazKomunikat("Niestety","Niestety z tego labiryntu\nnie ma wyjscia");
  while (lab[z].stan!='\0'){
    if (lab[z].stan=='e'){
      y=y+SIZE;
      x=0;
    }else{
      g=0;
      if (lab[z].stan=='#')
	gdk_draw_pixmap(piksmapa,obszar->style->black_gc,
			wall16,0,0,x,y,SIZE,SIZE);
      if (lab[z].stan=='X' || lab[z].stan=='.')
	gdk_draw_pixmap(piksmapa,obszar->style->black_gc,
			step16,0,0,x,y,SIZE,SIZE);
      if (lab[z].stan==' ')
	gdk_draw_pixmap(piksmapa,obszar->style->black_gc,
			grass16,0,0,x,y,SIZE,SIZE);
      if (lab[z].stan=='W' || lab[z].stan=='w')
	gdk_draw_pixmap(piksmapa,obszar->style->black_gc,
			exit16,0,0,x,y,SIZE,SIZE);
      if (lab[z].x==start.x && lab[z].y==start.y)
	gdk_draw_pixmap(piksmapa,obszar->style->black_gc,
			start16,0,0,x,y,SIZE,SIZE);
      x=x+SIZE;
    }
    z++;
  }
  
  /* --- Ustawiamy prostokat
   * --- Do okna bedzie kopiowana cala piksmapa, wiec
   * --- prostokat ma rozmiary rowne obszarowi okna
   */
  uakt_prostokat.x = 0;
  uakt_prostokat.y = 0;
  uakt_prostokat.width = obszar->allocation.width;
  uakt_prostokat.height = obszar->allocation.height;

  gtk_widget_draw (obszar, &uakt_prostokat);
  if (in!=1){
    gtk_timeout_remove(maze);
    return FALSE;
  }
  else
    return TRUE;
}

void DrawMove(int y){
  opcja=y;
  if (y==1){
    pt.x=start.x;
    pt.y=start.y;
  }
  if (SIZE==16){
    wall16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
				      &mwall16,NULL,(gchar **)wall16_xpm);
    grass16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mgrass16,NULL,(gchar **)grass16_xpm);
    step16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mstep16,NULL,(gchar **)step16_xpm);
    start16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mstart16,NULL,(gchar **)start16_xpm);
    exit16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mexit16,NULL,(gchar **)exit16_xpm);
  }
  if(SIZE==24){
    wall16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mwall16,NULL,(gchar **)wall24_xpm);
    grass16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mgrass16,NULL,(gchar **)grass24_xpm);
    step16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mstep16,NULL,(gchar **)step24_xpm);
    start16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mstart16,NULL,(gchar **)start24_xpm);
    exit16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mexit16,NULL,(gchar **)exit24_xpm);
  }
  if(SIZE==32){
    wall16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mwall16,NULL,(gchar **)wall_xpm);
    grass16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mgrass16,NULL,(gchar **)grass_xpm);
    step16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mstep16,NULL,(gchar **)step_xpm);
    start16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					 &mstart16,NULL,(gchar **)start_xpm);
    exit16=gdk_pixmap_create_from_xpm_d(glowne_okno->window,
					&mexit16,NULL,(gchar **)exit_xpm);
  }
    /*wywolujemy funkcje rysujaca lub (gdy opcja=1) rozwiazujaca labirynt*/
  maze=gtk_timeout_add(timeout,DrawMaze,(gpointer)obszar_rys);
}

/*obsluga wyskakujacyhc komunikatow w okienkach*/

void ZamknijOknoKomunikatu (GtkWidget *kontrolka, gpointer dane)
{
  GtkWidget *kontrolka_dialogowa = (GtkWidget *) dane;
  
  /* --- usuwamy kontrolkê okna dialogowego --- */
  gtk_widget_destroy (kontrolka_dialogowa);
}



void UsunOknoKomunikatu (GtkWidget *kontrolka, gpointer dane)
{
  gtk_grab_remove (kontrolka);
}



void PokazKomunikat (char *szTytul, char *szKomunikat)
{
  GtkWidget *etykieta;
  GtkWidget *przycisk;
  GtkWidget *okno_dialogowe;
  GtkWidget *image;
  
  okno_dialogowe = gtk_dialog_new ();
  gtk_signal_connect (GTK_OBJECT (okno_dialogowe), "destroy",
		      GTK_SIGNAL_FUNC (UsunOknoKomunikatu),
		      NULL);
  
  gtk_window_set_title (GTK_WINDOW (okno_dialogowe), szTytul);
  gtk_container_border_width (GTK_CONTAINER (okno_dialogowe), 0);
  przycisk = gtk_button_new_with_label ("OK");
  gtk_signal_connect (GTK_OBJECT (przycisk), "clicked",
              GTK_SIGNAL_FUNC (ZamknijOknoKomunikatu),
		      okno_dialogowe);
  
  GTK_WIDGET_SET_FLAGS (przycisk, GTK_CAN_DEFAULT);
  gtk_box_pack_start (GTK_BOX (
			       GTK_DIALOG (okno_dialogowe)->action_area), 
		      przycisk, TRUE, TRUE, 0);
  gtk_widget_grab_default (przycisk);
  gtk_widget_show (przycisk);

  image=gtk_image_new_from_file("pixmaps/dialog.png");
  gtk_misc_set_padding (GTK_MISC (image), 10, 10);
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG (okno_dialogowe)->vbox), 
                        image, TRUE, TRUE, 0);
  gtk_widget_show (image);
  if (kroki!=0){
    etykieta=gtk_label_new("Wyjscie jest w odleglosci\n");
    gtk_misc_set_padding (GTK_MISC (etykieta), 10, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (okno_dialogowe)->vbox), 
                        etykieta, TRUE, TRUE, 0);
    gtk_widget_show (etykieta);
    etykieta=gtk_label_new(szKomunikat);
    gtk_misc_set_padding (GTK_MISC (etykieta), 10, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (okno_dialogowe)->vbox), 
                        etykieta, TRUE, TRUE, 0);
    gtk_widget_show (etykieta);
    etykieta=gtk_label_new(" krokow z punktu startowego.");
    gtk_misc_set_padding (GTK_MISC (etykieta), 10, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (okno_dialogowe)->vbox), 
                        etykieta, TRUE, TRUE, 0);
    gtk_widget_show (etykieta);
  }else{
    etykieta=gtk_label_new(szKomunikat);
    gtk_misc_set_padding (GTK_MISC (etykieta), 10, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (okno_dialogowe)->vbox), 
                        etykieta, TRUE, TRUE, 0);
    gtk_widget_show (etykieta);
  }
  gtk_widget_show (okno_dialogowe);
  gtk_grab_add (okno_dialogowe);
}

void wybrano(GtkButton* button, gpointer window){
  GtkWidget* xpole;
  GtkWidget* lista;
  GList* child_list;
  
  xpole = gtk_bin_get_child(GTK_BIN(window));
  child_list = gtk_container_get_children(GTK_CONTAINER(xpole));
  lista = g_list_nth_data(child_list, 1);
  timeout = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lista));
  gtk_widget_destroy(GTK_WIDGET(window));
}

void UstawOpoznienie(void){
  GtkWidget* etykieta;
  GtkWidget* lista;
  GtkWidget* przycisk;
  GtkWidget* ypole;
  GtkWidget* okno;
  GtkAdjustment* adj;
  
  okno = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(okno),"OPOZNIENIE");
  gtk_widget_set_usize(okno,200,150);

  ypole = gtk_vbox_new(FALSE, 2);
  gtk_container_add(GTK_CONTAINER(okno), ypole);
  gtk_container_set_border_width(GTK_CONTAINER(ypole), 10);
  gtk_widget_show(ypole);

  etykieta = gtk_label_new("\nWybierz opoznienie     \nw milisekundach:\n");
  gtk_container_add(GTK_CONTAINER(ypole), etykieta);
  gtk_widget_show(etykieta);

  adj = (GtkAdjustment*)gtk_adjustment_new(timeout, 50.0, 10000.0, 50.0, 100.0, 100.0);
  lista = gtk_spin_button_new(adj, 1.0, 0);
  gtk_container_add(GTK_CONTAINER(ypole), lista);
  gtk_widget_show(lista);

  przycisk = gtk_button_new_with_label("OK");
  gtk_container_add(GTK_CONTAINER(ypole), przycisk);
  gtk_widget_show(przycisk);

  g_signal_connect(GTK_OBJECT(przycisk), "clicked",
		   G_CALLBACK(wybrano), (gpointer)okno);

  gtk_widget_show(okno);
}

void UstawPowiekszenie(void){
  if(SIZE==32)
    PokazKomunikat("Blad !","Niestety bardziej nie mozna\npowiekszyc tego labiryntu.\nTo jest maksymalne powiekszenie");
  if (SIZE==24){
    SIZE=32;
    OtworzPlik(NazwaPliku);
  }
  if (SIZE==16){
    SIZE=24;
    OtworzPlik(NazwaPliku);
  }
}

void UstawPomniejszenie(void){
  if(SIZE==16)
    PokazKomunikat("Blad !","Niestety bardziej nie mozna\npomniejszyc tego labiryntu.\nTo jest minimalne pomniejszenie");
  if (SIZE==24){
    SIZE=16;
    OtworzPlik(NazwaPliku);
  }
  if (SIZE==32){
    SIZE=24;
    OtworzPlik(NazwaPliku);
  }
}
