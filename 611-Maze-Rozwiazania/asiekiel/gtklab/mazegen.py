#!/usr/bin/python
# -*- coding: iso-8859-2 -*-

# Skrypt generujący doskonałe labirynty.
# Przy odpalaniu z linii komend wypisze na stdout
# losowy labirynt prostokątny

import random
import math

WALL = '#'
HARD_WALL = '@'
NORMAL = ' '
START = 'S'

def any(f, seq):
    "True if f(e) is true for some e from sequence seq"
    for e in seq:
	if f(e):
	    return True
    return False

def insideMaze(maze, pt):
    "Is 'pt' inside maze?"
    return pt[0] >= 0 and pt[1] >= 0 and pt[1] < len(maze) and pt[0] < len(maze[pt[1]])

def borderPoints(maze):
    return [ (0, i)  for i in range(0, len(maze)) ] +\
           [ (len(maze[i])-1, i) for i in range(0, len(maze)) ] +\
           [ (i, 0) for i in range(0, len(maze[0])) ] +\
           [ (i, len(maze)-1) for i in range(0, len(maze[-1])) ]

def neighbourPoints(maze, pt):
    (x, y) = pt
    xs = range(x-1, x+2)
    ys = range(y-1, y+2)
    allPoints = [ (a, b) for a in xs for b in ys ]
    allPoints.remove((x,y))
    return filter(lambda a: insideMaze(maze, a), allPoints)

def directNeighbours(maze, (x,y)):
    return filter(lambda a: insideMaze(maze, a), ((x-1,y),(x+1,y),(y-1,x),(y+1,x)))

def makeExit(maze):
    def borderWithoutCorners():
          return [ (0, i) for i in range(2, len(maze) - 2) ] +\
                 [ (len(maze[i])-1, i) for i in range(2, len(maze) - 2) ] +\
                 [ (i, 0) for i in range(2, len(maze[0]) - 2) ] +\
                 [ (i, len(maze)-1) for i in range(2, len(maze[-1]) - 2) ]

    def makeSuccFunction((x,y)):
          if x == 0:
                return lambda (x, y): (x+1, y)
          elif y == 0:
                return lambda (x, y): (x, y+1)
          elif x == len(maze[y]) - 1:
                return lambda (x, y): (x-1, y)
          else:
                return lambda (x, y): (x, y-1)
    bc = borderWithoutCorners()
    pt = bc[random.randrange(0, len(bc))]
    succ = makeSuccFunction(pt)
    while 1:
          maze[pt[1]][pt[0]] = NORMAL
          (xp, yp) = succ(pt)
          if maze[yp][xp] == NORMAL:
                break
          pt = (xp, yp)

def makeStart(maze):
    all = [ (x, y) for y in range(0, len(maze)) for x in range(0, len(maze[y]))]
    normals = filter(lambda (x,y): maze[y][x] == NORMAL, all)
    (a, b) = normals[random.randrange(0, len(normals))]
    maze[b][a] = START

def surroundMaze(maze):
    "Surround maze by hard wall"
    for (x, y) in borderPoints(maze):
          maze[y][x] = HARD_WALL

def Random2PointPaths(pt):
    "Gives random list of all 2-point paths from one of 4 directions"
    (x, y) = pt
    nearPaths = [ [(x-1, y),(x-2,y)], [(x+1, y),(x+2,y)],
		  [(x,y-1),(x,y-2)],  [(x,y+1),(x,y+2)] ]
    random.shuffle(nearPaths)
    return nearPaths

def surroundedByWall(maze, pt):
    "Is pt surrounded by wall?"
    return any(lambda (a,b): maze[b][a] == WALL, neighbourPoints(maze, pt))

def mazeBuilder(maze, pt):
    "Main building algorithm"
    for [(x1, y1), (x2,y2)] in Random2PointPaths(pt):
	if insideMaze(maze, (x2, y2)) and maze[y1][x1] == WALL and \
	   maze[y2][x2] == WALL and surroundedByWall(maze, (x2,y2)):
	       maze[y1][x1] = maze[y2][x2] = NORMAL
	       mazeBuilder(maze, (x2, y2))
	
def makeSquareMaze(x, y):
    maze = []
    for i in range(0, y):
	maze.append([ WALL for i in range(0, x) ])
    surroundMaze(maze)
    return maze

def makeCircleMaze(r):
    maze = makeSquareMaze(2*r, 2*r)
    all = [ (x, y) for x in range(0, 2*r) for y in range(0, 2*r) ]
    bad = filter(lambda (x,y): (x-r)**2 + (y-r)**2 > r*r + 6, all)
    lim = filter(lambda (x,y): (x-r)*(x-r) + (y-r)*(y-r) < r*r + 6, all)
    good =filter(lambda (x,y): (x-r)*(x-r) + (y-r)*(y-r) < r*r, all)
    for (x, y) in lim:
	maze[y][x] = HARD_WALL
    for (x, y) in bad:
	maze[y][x] = NORMAL
    for (x, y) in good:
	maze[y][x] = WALL
    return maze
    

def normalizeWalls(maze):
    "Change hard to normal walls"
    for e in maze:
	for i in range(0, len(e)):
	    if e[i] == HARD_WALL:
		e[i] = WALL

def printMaze(maze):
    for e in maze:
	print ''.join(e)

def main():
    import sys
    sys.setrecursionlimit(1000000)

    size1 = random.randrange(12, 50)
    size2 = random.randrange(12, 50)
    m = makeSquareMaze(size1, size2)

    mazeBuilder(m, (10,10))
    normalizeWalls(m)
    makeStart(m)
    makeExit(m)

    printMaze(m)

if __name__ == '__main__':
    main()
