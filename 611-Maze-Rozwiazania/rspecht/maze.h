#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED


#define     FREE      0
#define     WALL      1
#define     START     2
#define     EXIT      4
#define     DEAD_END  8
#define     VISITED   16
#define     ON_PATH   32

typedef struct
{
  int x, y;
} pointT;

typedef enum {N, E, S, W} directionT;

void ReadMazeMap(char *filename, char *wall_chars, char *start_chars, char *exit_chars);

pointT
MAZE_go(pointT p, directionT d);

pointT
GetStartPosition();

int WallExist(pointT p, directionT d);

void MarkSquare(pointT p, int mask);

void UnMarkSquare(pointT p, int mask);

int IsMarked(pointT p, int mask);

void EliminateDeadEnds();

int OutsideMaze(pointT p);

pointT 
MakePoint(int x, int y);

int IsInMaze(pointT p);

void EliminateDeadEnds();

#endif
