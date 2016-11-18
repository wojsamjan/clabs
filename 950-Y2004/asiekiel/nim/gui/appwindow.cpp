#include "appwindow.h"
#include "kikboard.h"
#include "config.h"
#include <qstatusbar.h>
#include <qpopupmenu.h>
#include <qapplication.h>
#include <qmenubar.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>

KIKSettings::KIKSettings(AppWindow* win): QDialog(), m_win(win)
{
      KIKBoard* board = static_cast<KIKBoard*>(m_win->centralWidget());
      QGridLayout* g = new QGridLayout(this, 5, 5);
      g->setColStretch(0, 10);

      QLabel* wi = new QLabel(QString::fromLocal8Bit("D³ugo¶æ wygrywaj±cej linii"), this);
      g->addWidget(wi, 0, 0, Qt::AlignHCenter);

      m_winning = new QSpinBox(3, 999, 1, this);
      m_winning->setValue(KIK::Config::winning_line_length);
      g->addWidget(m_winning, 0, 1, Qt::AlignHCenter);

      QLabel* dei = new QLabel(QString::fromLocal8Bit("G³êboko¶æ rekurencjnego wyszukiwania ruchów"), this);
      g->addWidget(dei, 1, 0, Qt::AlignHCenter);

      m_rec_depth = new QSpinBox(1, 10, 1, this);
      m_rec_depth->setValue(KIK::Config::max_recursion_depth);
      g->addWidget(m_rec_depth, 1, 1, Qt::AlignHCenter);

      QLabel* wii = new QLabel(QString::fromLocal8Bit("Szeroko¶æ planszy"), this);
      g->addWidget(wii, 2, 0, Qt::AlignHCenter);

      m_width = new QSpinBox(3, 99, 1, this);
      m_width->setValue(board->boardSize().width());
      g->addWidget(m_width, 2, 1, Qt::AlignHCenter);

      QLabel* hei = new QLabel(QString::fromLocal8Bit("Wysoko¶æ planszy"), this);
      g->addWidget(hei, 3, 0, Qt::AlignHCenter);

      m_height = new QSpinBox(3, 99, 1, this);
      m_height->setValue(board->boardSize().height());
      g->addWidget(m_height, 3, 1, Qt::AlignHCenter);

      QPushButton* button = new QPushButton("OK", this);
      g->addMultiCellWidget(button, 4, 4, 0, 1, Qt::AlignHCenter);
      connect(button, SIGNAL(clicked()), this, SLOT(setSettingsAndExit()));
}

void KIKSettings::setSettingsAndExit()
{
      KIKBoard* board = static_cast<KIKBoard*>(m_win->centralWidget());
      QSize new_size(m_width->value(), m_height->value());
      if (new_size != board->boardSize()) {
            board->resizeBoard(new_size.width(), new_size.height());
            m_win->setMaximumSize(board->maximumSize());
      }

      KIK::Config::winning_line_length = m_winning->value();

      KIK::Config::max_recursion_depth = m_rec_depth->value();

      delete this;
}

AppWindow::AppWindow()
{
      this->kb = new KIKBoard(this);
      this->setCentralWidget(this->kb);
      this->setMaximumSize(this->kb->maximumSize());

      connect(this->kb, SIGNAL(shortInfo(const QString&)),
              this->statusBar(), SLOT(message(const QString&)));

      QPopupMenu* gra = new QPopupMenu(this);
      this->menuBar()->insertItem("&Gra", gra);
      gra->insertItem("Nowa gra", this->kb, SLOT(newGame()), CTRL+Key_N);
      gra->insertItem("Ustawienia", this, SLOT(showSettings()));
      gra->insertItem(QString::fromLocal8Bit("Wyj¶cie"), qApp, SLOT(quit()));
}

void AppWindow::showSettings()
{
      KIKSettings* s = new KIKSettings(this);
      s->show();
}
