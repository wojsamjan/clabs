
#include <stdlib.h>
#include "mazelib.h"
#include "maze.h"

/* Funkcja `SolveMaze(pt)' próbuje znale¼æ drogê do wyj¶cia 
   z labiryntu z podanego punktu `pt'. Funkcja zwraca true 
   je¶li jest taka droga, a false w przeciwnym wypadku.
   Funkcja korzysta z rekurencji do rozwi±zania podlabiryntów
   powstaj±cych przez zaznaczenie bie¿±cego punktu 
   i przej¶cie o jeden krok dalej niezablokowanym przej¶ciem. */

bool SolveMaze(pointT pt);
int FindPath(pointT pt, pointT path[], int pathSize);
int ShortestPathLength(pointT pt);

const char* MazeFile = "labirynt.txt";  /* nazwa pliku z labiryntem */
directionT all_directions[] = { North, East, South, West };

bool SolveMaze(pointT pt) {
      int i;
      
      if (OutsideMaze(pt))
            return true;
      if (IsMarked(pt))
            return false;
      MarkSquare(pt);
      for (i = 0; i < 4; ++i)
            if (!WallExists(pt, all_directions[i]))
                  if (SolveMaze(AdjacentPoint(pt, all_directions[i])))
                      return true;
      UnmarkSquare(pt);
      return false;
}


static int ShortestPathFinder(pointT pt, int cur_length) {
  int i;
  int min = NoSolution;
  int solution;

  if (OutsideMaze(pt))
    return cur_length;
  if (IsMarked(pt))
    return NoSolution;
  MarkSquare(pt);
  for (i = 0; i < 4; ++i)
    if (!WallExists(pt, all_directions[i])) {
      solution = ShortestPathFinder(AdjacentPoint(pt, all_directions[i]), cur_length + 1);
      if (solution < min)
        min = solution;
    }
  UnmarkSquare(pt);
  return min;
}

int ShortestPathLength(pointT pt) {
      return ShortestPathFinder(pt, 0);
}


static int PathFinder(pointT pt, pointT path[], int pathSize, int current) {
  int i;
  int pathlen;
  
  if (current >= pathSize)
    return 0;
  path[current] = pt;
  if (OutsideMaze(pt))
    return current;
  if (IsMarked(pt))
    return 0;
  MarkSquare(pt);
  for (i = 0; i < 4; ++i)
    if (!WallExists(pt, all_directions[i])) {
      pathlen = PathFinder(AdjacentPoint(pt, all_directions[i]), path, pathSize, current + 1);
      if (pathlen > 0)
        return pathlen;
    }
  return 0;
}

int FindPath(pointT pt, pointT path[], int pathSize) {
  return PathFinder(pt, path, pathSize, 0);
}
