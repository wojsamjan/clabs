/*  File: mazelib.c
 *
    Implementacja interfejsu z `mazelib.h'.
 */
#define _GNU_SOURCE
#include "mazelib.h"
#include<string.h>

/* LinesCount: funkcja zliczaj±ca ilo¶æ linii w pliku ¼ród³owym */
static int LinesCount(FILE *file)
{
	int i=0;
	char c;
	while((c=fgetc(file))!=EOF)
		if (c == '\n') i++;
	return i;
}
/* Implementacje ekportowanych funkcji. */

void ReadMazeMap(string filename) {
	FILE *file;
	int i, len;
	unsigned int n;
	file=fopen(filename,"r");
	Maze.lines=LinesCount(file);
	Maze.maze=malloc(sizeof(char*) * Maze.lines);
	fseek(file,0,SEEK_SET);
	for(i=0; i<Maze.lines; i++)
	{
		len = getline(&Maze.maze[i],&n,file);
		if (Maze.maze[i][len-1]=='\n')
			Maze.maze[i][len-1]='\0';
	}
	fclose(file);	
}

pointT GetStartPosition(void) {
	int i,j;
	pointT pt = {-1,0};
	for(i=0; i<Maze.lines; i++)
		for(j=0; Maze.maze[i][j]!='\0'; j++)
			if (Maze.maze[i][j]=='S')
			{
				pt.x=j;
				pt.y=i;
				return pt;
			}
	return pt;
}

bool OutsideMaze(pointT pt) {
	return (Maze.maze[pt.y][pt.x]=='@');
}

bool WallExists(pointT pt, directionT dir) {
	pointT newpt=AdjacentPoint(pt,dir);
	return (Maze.maze[newpt.y][newpt.x]=='#');
}

void MarkSquare(pointT pt) {
	Maze.maze[pt.y][pt.x]='.';
}

void UnmarkSquare(pointT pt) {
	Maze.maze[pt.y][pt.x]=' ';
}

bool IsMarked(pointT pt) {
	return (Maze.maze[pt.y][pt.x]=='.'); 
}

pointT AdjacentPoint(pointT pt, directionT dir) {
  pointT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y++; break;
    case East: newpt.x++; break;
    case South: newpt.y--; break;
    case West: newpt.x--; break;    
  }
  return newpt;
}

