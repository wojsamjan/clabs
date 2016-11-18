#!/bin/ch
#include <cgi.h>
#include <chplot.h>

int main() {
  double MinX, MaxX, Step, x, y;
  int pointsX, pointsY, i, num;
  chstrarray name, value;
  class CResponse Response;
  class CRequest Request;
  class CPlot plot;

  num=Request.getFormNameValue(name,value);
  MinX=atof(value[1]);
  MaxX=atof(value[2]);
  pointsX=atoi(value[3]);

  double x1[pointsX], y1[pointsX];
  
  Step=(MaxX-MinX)/(pointsX-1);
  for (i=0; i<pointsX; i++) {
    x=MinX+(i*Step);
    y=streval(value[0]);
    x1[i]=x;
    y1[i]=y;
  }
  Response.setContentType("image/png");
  Response.begin();
  plotxy(x1,y1,value[0],"X","Y",&plot);
  plot.outputType(PLOT_OUTPUTTYPE_STREAM,"png color");
  //  Zapis do pliku:
  //  plot.outputType(PLOT_OUTPUTTYPE_FILE,"png color","plot.png");
  plot.plotting();
  Response.end();
}
