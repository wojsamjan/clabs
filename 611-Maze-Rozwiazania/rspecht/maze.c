#include "maze.h"

#include <stdio.h>
#include <stdlib.h>

char *MAZE_maze;

int MAZE_width, MAZE_heigth;

void error(char *msg)
{
    fprintf(stderr,"BLAD!: %s\n", msg);
    exit(1);
}

// funkcje 'lokalne'

int CountMazeOffset(pointT p)
{
  return MAZE_width * p.y + p.x;
}

pointT
MakePoint(int x, int y)
{
  pointT temp;
  temp.x = x;
  temp.y = y;
  return temp;
}

int IsInStr(char what, char *where)
{
  int i;
  i = strlen(where);
  while(--i >= 0)
    if (where[i] == what)
      return 1;
  return 0;
}

int IsInMaze(pointT p)
{
  if ((p.x >= 0) && (p.x < MAZE_width) && (p.y >= 0) && (p.y < MAZE_heigth))
    return 1;
  else
    return 0;
}

pointT
MAZE_go(pointT p, directionT d)
{
  pointT temp;
  temp = p;

  switch (d)
    {
    case N : temp.y--; break;
    case E : temp.x++; break;
    case S : temp.y++; break;
    case W : temp.x--; break; 
    }
  return temp;
}


void ReadMazeMap(filename, wall_chars, start_chars, exit_chars)
     char *filename, *wall_chars, *start_chars, *exit_chars;
     
{
  int i, position;
  FILE *maze_file;
  char c, type;

  maze_file = fopen(filename, "r");

  if (maze_file == NULL)
    error("Nie mozna otworzyc pliku z danymi wejsciowymi");

  // ile znakow w wierszu?

  MAZE_width = 0;
  while ((c = fgetc(maze_file)) != '\n' && c != EOF)
    MAZE_width++;

  if (MAZE_width == 0)
    error("Pusty plik z labiryntem");

  MAZE_maze = malloc(MAZE_width * sizeof(MAZE_maze));
  // no to mamy miejsce na pierwszy rzad

  if (MAZE_maze == NULL)
    error("Brak pamieci na pierwszy wiersz labiryntu!");

  // wracamy na poczatek pliku
  rewind(maze_file);

  // i wczytujemy sobie dane

  position = 0;   // pierwszy element tablicy

  while (!feof(maze_file))
    {
      MAZE_heigth++;        // jest kolejny rzad
      MAZE_maze = realloc(MAZE_maze, MAZE_heigth * MAZE_width * sizeof(MAZE_maze));
      if (MAZE_maze == NULL)
	error("Brak pamieci na kolejne wiersze labiryntu!");
      for (i = 0; i < MAZE_width; i++)
	{
	  c = fgetc(maze_file);
	  if (IsInStr(c, wall_chars))
	    type = WALL;
	  else
	    if (IsInStr(c, start_chars))
	      type = START;
            else
	      if (IsInStr(c, exit_chars))
		type = EXIT;
              else
                type = FREE;
	  MAZE_maze[position++] = type;
	}
      c = fgetc(maze_file);    // nowa linia
    }

}

pointT
GetStartPosition()
{
  int x, y;

  for (y = 0; y <= MAZE_heigth; y++)
    for (x = 0; x <= MAZE_width; x++)
      if (MAZE_maze[CountMazeOffset(MakePoint(x, y))] & START)
	return MakePoint(x, y);

  return MakePoint(-1, -1);
}

int WallExist(pointT p, directionT d)
{
  if (MAZE_maze[CountMazeOffset(MAZE_go(p, d))] & WALL)
    return 1;
  else
    return 0;
}

void MarkSquare(pointT p, int mask)
{
  MAZE_maze[CountMazeOffset(p)] |= mask;
}

void UnMarkSquare(pointT p, int mask)
{
  MAZE_maze[CountMazeOffset(p)] &= (255 - mask);
}

int IsMarked(pointT p, int mask)
{
  if ((MAZE_maze[CountMazeOffset(p)] & mask) == mask)
    return 1;
  else 
    return 0;
}

int OutsideMaze(pointT p)
{
  return ((IsMarked(p, EXIT)) || (!IsInMaze(p)));
}


int CountExits(pointT p)
{
  int exit_count;
  directionT d;
  pointT point;

  exit_count = 0;

  if (IsMarked(p, DEAD_END) || IsMarked(p, WALL) || IsMarked(p, START) || IsMarked(p, EXIT))
    exit_count = 100;          // tak na zapas :)
  else
    for (d = N; d <= W; d++)
      {
	point = MAZE_go(p, d);
	if (! (IsMarked(point, WALL) || IsMarked(point, DEAD_END)))
	  exit_count++;
      }

  return exit_count;
}

void EliminateDeadPath(pointT p)
{
  directionT d;

  if (CountExits(p) == 1)
    {
      MarkSquare(p, DEAD_END);
      for (d = N; d <= W; d++)
	EliminateDeadPath(MAZE_go(p, d));
    }
}


void EliminateDeadEnds()
{
  pointT p;

  for (p.y = 0; p.y < MAZE_heigth; p.y++)
    for (p.x = 0; p.x < MAZE_width; p.x++)
      EliminateDeadPath(p);
}
