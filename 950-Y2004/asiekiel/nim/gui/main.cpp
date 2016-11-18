#include "appwindow.h"
#include <qapplication.h>
#include <iostream>

int main(int argc, char** argv)
{
      //std::cout.sync_with_stdio(false);
      QApplication a(argc, argv);
      AppWindow app;
      a.setMainWidget(&app);
      app.show();
      return a.exec();
}
