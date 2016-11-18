#ifndef INCLUDED__APPWINDOW_H
#define INCLUDED__APPWINDOW_H

#include <qmainwindow.h>
#include <qvbox.h>
#include <qspinbox.h>
#include <qdialog.h>
#include <qframe.h>
#include <qgrid.h>

class KIKBoard;

// G³ówne okno programu
class AppWindow: public QMainWindow {
      Q_OBJECT
public:
      AppWindow();
private:
      KIKBoard* kb;
private slots:
      void showSettings();
};

// Okienko z ustawieniami
class KIKSettings: public QDialog {
      Q_OBJECT
      AppWindow* m_win;
      QSpinBox* m_winning;
      QSpinBox* m_width;
      QSpinBox* m_height;
      QSpinBox* m_rec_depth;
public:
      KIKSettings(AppWindow* win);
private slots:
      void setSettingsAndExit();
};

#endif

