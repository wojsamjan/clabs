#include"mazelib.h"
#include"random.h"

/* funkcja zwraca punkt odleg³y o dwa pola od danego */
pointT NewPoint(pointT pt, directionT dir) {
  pointT newpt;
  newpt=pt;
  switch (dir) {
    case North: newpt.y-=2; break;
    case East: newpt.x+=2; break;
    case South: newpt.y+=2; break;
    case West: newpt.x-=2; break;    
  }
  return newpt;
}

/* funkcja odznaczaj±ca ¶cianê w danym punkcie i w punkcie z którego mo¿na
 * doj¶æ do niego z kierunku dir */
static void UnmarkWall(pointT pt, directionT dir) {
	Maze.maze[pt.y][pt.x]=' ';
	switch (dir){
		case North:	Maze.maze[pt.y+1][pt.x]=' '; break;
		case East: 	Maze.maze[pt.y][pt.x-1]=' '; break;
		case South:	Maze.maze[pt.y-1][pt.x]=' '; break;
		case West: 	Maze.maze[pt.y][pt.x+1]=' '; break;
	}
}

/* funkcja sprawdzaj±ca czy w danym punkcie jest ¶ciana */
static bool IsWall(pointT pt) {
	return (Maze.maze[pt.y][pt.x]=='#'); 
}

/* funkcja sprawdzaj±ca czy punkt jest poza labiryntem */
static bool OutOfMaze(pointT pt) {
	return (Maze.maze[pt.y][pt.x]=='@');
}

/* rekurencyjna funkcja do tworzenia labiryntu */
static void recursiveMaze(pointT pt, directionT dir)
{
	bool rand[4];
	int i,k;
	pointT newpt;	
	if (OutOfMaze(pt) || !IsWall(pt)) return;
	if (Maze.maze[pt.y-1][pt.x]==' ' || Maze.maze[pt.y+1][pt.x]==' ' ||
		Maze.maze[pt.y][pt.x-1]==' ' || Maze.maze[pt.y][pt.x+1]==' ')
		return;
	UnmarkWall(pt, dir);
	for(i=0; i<4; i++)
		rand[i]=FALSE;
	for(i=0; i<4; i++)
	{
		k=RandomInteger(0,3);	
		while(rand[k]==TRUE)
			k=(k+1)%4;
		rand[k]=TRUE;
		dir=k;
		newpt=NewPoint(pt,dir);	
		if (IsWall(newpt))
			recursiveMaze(newpt, dir);		
	}
	return;	
}

/* Funkcja tworz±ca nowy labirynt */
static void newMaze(pointT pt)
{
	recursiveMaze(pt,1);
	Maze.maze[pt.y][pt.x-1]='#';
}

/* Funkcja sprawdzaj±ca czy wyj¶cie jest prawid³owe - tzn. czy nie jest zablokowane
 * ¶cian± od strony labiryntu */
static bool CorrectExit(pointT pt)
{
	pt.y++;
	pt.x++;
	return (Maze.maze[pt.y+1][pt.x]==' ' || Maze.maze[pt.y-1 ][pt.x]==' ' ||
			Maze.maze[pt.y][pt.x-1]==' ' || Maze.maze[pt.y][pt.x+1]==' ');
}

/* funkcja tworz±ca wyj¶cie z labiryntu */
static void MakeExit(int lenX, int lenY)
{	
	pointT exitPos;
	int k1=RandomInteger(0,1);
	int k2=RandomInteger(0,1);
	if (k1)
	{
		if (k2) exitPos.x=0; 
		else exitPos.x=lenX-1;
		exitPos.y=RandomInteger(0,lenY-1);	
		while(!CorrectExit(exitPos))
			exitPos.y=(exitPos.y+1) % lenY;
	}
	else
	{
		if (k2) exitPos.y=0; 
		else exitPos.y=lenY-1;
		exitPos.x=RandomInteger(2,lenX-3);
		while(!CorrectExit(exitPos))
			exitPos.x=(exitPos.x+1) % lenX;	
	}
	Maze.maze[exitPos.y+1][exitPos.x+1]=' ';
}

/* funkcja tworz±ca punkt startowy w labiryncie */
static void MakeStart(int lenX, int lenY)
{
	pointT startPos={0,0};
	while(Maze.maze[startPos.y][startPos.x]!=' ')
	{
		startPos.x=RandomInteger(2,lenX-3);
		startPos.y=RandomInteger(2,lenY-2);	
	}
	Maze.maze[startPos.y][startPos.x]='S';
}	
/* Funkcja tworz±ca gotowy labirynt
 *  liczba kolumn i wierszy musi byæ nieparzysta */
void CreateMaze(int lenX, int lenY)
{
	int i,j;	
	pointT pt={2,2};
	lenY+=2;
	lenX+=4;
	Maze.maze=malloc(sizeof(char *)* lenY);
	Maze.lines=lenY;
	for(i=0; i<Maze.lines; i++)
		Maze.maze[i]=malloc(sizeof(char)*lenX);
	for(i=0; i<Maze.lines; i++)
		for(j=0; j<lenX-2; j++)
			Maze.maze[i][j]='#';
	for(i=0; i<Maze.lines; i++)
	{
		Maze.maze[i][0]='@';
		Maze.maze[i][lenX-3]='@';
		Maze.maze[i][lenX-2]='\n';
		Maze.maze[i][lenX-1]='\0';
	}
	for(i=1; i<lenX-3; i++)
	{
		Maze.maze[0][i]='@';
		Maze.maze[Maze.lines-1][i]='@';
	}
	Randomize();
	newMaze(pt);
	MakeStart(lenX, lenY);
	MakeExit(lenX-4,lenY-2);
}
/* Funkcja tworz±ca gotowy labirynt i zapisuj±ca go do pliku
 * liczba kolumn i wierszy musi byæ nieparzysta */
void CreateMazeInFile(char *filename, int lenX, int lenY)
{
	int i;
	FILE *file;
	CreateMaze(lenX,lenY);
	file=fopen(filename,"w+");
	for (i=0; i<Maze.lines; i++)
		fputs(Maze.maze[i],file);	
	fclose(file);
}

