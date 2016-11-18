#include <stdio.h>
#include <unistd.h>
#include <ncurses/ncurses.h>
#include "maze.h"
#include "config.h"

void error(char *msg);

char DetermineFloorChar(pointT p)
{
  char c;
  
  c = cfgOutputFloorChar[0];
  if (IsMarked(p, WALL))
    c = cfgOutputWallChar[0];
  if (IsMarked(p, VISITED))
    c = cfgOutputVisitedChar[0];
  if (IsMarked(p, ON_PATH))
    c = cfgOutputOnPathChar[0];
  if (IsMarked(p, DEAD_END))
    c = cfgOutputDeadEndChar[0];
  if (IsMarked(p, START))
    c = cfgOutputStartChar[0];
  if (IsMarked(p, EXIT))
    c = cfgOutputExitChar[0];
  return c;
}

void print_maze(pointT walker)
{
   pointT p;

  for (p.y = 0; p.y < 24; p.y++)
    {
      for (p.x = 0; p.x < 79; p.x++)      
	if (IsInMaze(p))
	  {
	    int color = 0;
	    if (DetermineFloorChar(p) == *cfgOutputDeadEndChar) color = cfgOutputDeadEndColPair;
	    if (DetermineFloorChar(p) == *cfgOutputOnPathChar) color = cfgOutputOnPathColPair;
	    if (DetermineFloorChar(p) == *cfgOutputVisitedChar) color = cfgOutputVisitedColPair;
	    if (color) attron(COLOR_PAIR(color)|A_BOLD);
		mvprintw(p.y, p.x, "%c", DetermineFloorChar(p));
	    if (color) attroff(COLOR_PAIR(color)|A_BOLD);
	  }
    }   

  if (cfgDelay)
    usleep(cfgDelay * 1000);
  refresh();

  nodelay(stdscr, TRUE);
  if (getch() != ERR)
    {
      endwin();
      exit(0);
    }
  nodelay(stdscr, FALSE);
}

void
write_maze()
{
  FILE *outfile;
  pointT p;

  outfile = fopen(outputfilename, "w");
  if (!outfile)
    error("Blad otwarcia pliku wynikowego!");

  p.x = 0;
  p.y = 0;

  while (IsInMaze(p))
  {
    p.x = 0;
    while (IsInMaze(p))
      {
	fprintf(outfile, "%c", DetermineFloorChar(p));
	p.x++;
      }
    p.x = 0;
    p.y++;
    fprintf(outfile, "\n");
  }
  fclose(outfile);
}

int
SolveMaze(pointT p, int printit)
{
  directionT dir;

  if (!cfgUseExtendedFlags)
    {
      if (OutsideMaze(p))
        return 1;

      if (IsMarked(p, ON_PATH))
        return 0;

      MarkSquare(p, ON_PATH);

      if (printit)
        print_maze(p);

      for (dir = N; dir <= W; dir++)
        {
          if (!WallExist(p, dir))
	  if (SolveMaze(MAZE_go(p, dir), printit))
	    return 1;
        }

     UnMarkSquare(p, ON_PATH);
     if (printit)
       print_maze(p);

     return 0;
    }
  else
    {
      if (OutsideMaze(p))
        return 1;
   
      if ((IsMarked(p, VISITED)) || IsMarked(p, DEAD_END))
        return 0;

      MarkSquare(p, VISITED);  // 'tu bylem - Tony Halik'

      if(printit)
        print_maze(p);

      for (dir = N; dir <= W; dir++)
        if (!WallExist(p, dir))
          {
	    if (SolveMaze(MAZE_go(p, dir), printit))
	      {
	        MarkSquare(p, ON_PATH);

		if (printit)
      	          print_maze(p);

       	        return 1;
	      }
          }
      return 0;
    }
}

int
main(int argc, char *argv[])
{
  pointT p;

  SetConfig(argc, argv);

  if (inputfilename == NULL)
    error("Nie podano pliku wejsciowego!");

  ReadMazeMap(inputfilename, cfgInputWallChars, cfgInputStartChars, cfgInputExitChars);
  p = GetStartPosition();
  if (p.x == -1)
    error("Brak punktu startowego!");

  if (cfgUseExtendedFlags && cfgEliminateDeadEnds)  
    EliminateDeadEnds();
  
  if (outputfilename != NULL)
    if (!SolveMaze(p, 0))
      error("Brak rozwiazania!");
    else
      write_maze(outputfilename);
  else
    {
      initscr();
      noecho();
      start_color();
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      init_pair(2, COLOR_RED, COLOR_BLACK);
      init_pair(3, COLOR_YELLOW, COLOR_BLACK);
      
      if (!SolveMaze(p, 1))
	{
  	  endwin();
	  error("Brak rozwiazania!");
	}
      getch();
      endwin();
    }
  
  
  return 0;
}
