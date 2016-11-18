#include "kikboard.h"
#include "game-rules.h"
#include "eval-pos.h"
#include "minimax.h"
#include <qdrawutil.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qimage.h>
#include <qmessagebox.h>
#include <iostream>
#include <qpopupmenu.h>

namespace {
      const int TILE_WIDTH = 65;
      const int TILE_HEIGHT = 65;

      QImage X_IMAGE(QString("ex.gif"));
      QImage O_IMAGE(QString("oh.gif"));

      QImage& imageOfPlayer(KIK::playerT player)
      {
            switch (player) {
                  case KIK::Human: return X_IMAGE;
                  case KIK::Computer: return O_IMAGE;
            }
            return X_IMAGE;
      }

      QPoint clickedToLogical(QPoint clicked)
      {
            return QPoint(clicked.x() / TILE_WIDTH, clicked.y() / TILE_HEIGHT);
      }

      QPoint logicalToClicked(QPoint logical)
      {
            return QPoint(logical.x() * TILE_WIDTH, logical.y() * TILE_HEIGHT);
      }
}

KIKBoard::KIKBoard(QWidget* parent): QScrollView(parent), m_board(6, 6, KIK::Human)
{

      this->setResizePolicy(Manual);
      this->prepareNewGame();
}

void KIKBoard::announceNewGame()
{
      QString info;
      if (KIK::checkForWin(m_board, KIK::Computer))
            info = QString::fromLocal8Bit("Wygra³ komputer...");
      else if (KIK::checkForWin(m_board, KIK::Human))
            info = QString::fromLocal8Bit("Gratulujê, wygra³e¶!");
      else
            info = QString("Remis!");
      QMessageBox::information(this, "kik", info);
      this->newGame();
}

void KIKBoard::prepareNewGame()
{
      this->resizeContents(m_board.width() * TILE_WIDTH, m_board.height() * TILE_HEIGHT);
      this->setMaximumSize(this->contentsWidth() + 50, this->contentsHeight() + 50);
      this->m_main_pixmap.resize(this->contentsWidth(), this->contentsHeight());
      this->m_main_pixmap.fill(Qt::lightGray);
      QPainter p(&this->m_main_pixmap);
      for (int i = 0; i < m_board.height(); ++i)
            for (int j = 0; j < m_board.width(); ++j)
                  qDrawShadePanel(&p, j * TILE_WIDTH, i * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT,
                                  this->viewport()->colorGroup(), false, 5);
}

void KIKBoard::newGame()
{
      emit shortInfo(QString::fromLocal8Bit("Witam w grze!"));
      this->m_board.clean();
      this->prepareNewGame();
      this->viewport()->repaint();
}

void KIKBoard::drawContents(QPainter* p, int x, int y, int w, int h)
{
      p->drawPixmap(x, y, this->m_main_pixmap, x, y, w, h);
}

void KIKBoard::contentsMousePressEvent(QMouseEvent* e)
{
      QPoint l = clickedToLogical(e->pos());

      KIK::Move m(l.x(), l.y());
      if (KIK::legalMove(this->m_board, m)) {
            this->handleUserMove(m);
            if (KIK::gameOver(this->m_board)) {
                  this->announceNewGame();
                  return;
            }
            this->doComputerMove();
            if (KIK::gameOver(this->m_board))
                  this->announceNewGame();
      }
}

void KIKBoard::handleUserMove(Move m)
{
            this->m_board.makeMove(m);
            this->updateAtLogicalPosition(logicalToClicked(QPoint(m.x, m.y)));
            qApp->processEvents();
}

void KIKBoard::doComputerMove()
{
            emit shortInfo(QString::fromLocal8Bit("My¶lê nad ruchem..."));
            qApp->processEvents();

            KIK::Move best = FindBestMove(this->m_board);
            this->m_board.makeMove(best);
            this->updateAtLogicalPosition(logicalToClicked(QPoint(best.x, best.y)));
            emit shortInfo(QString::fromLocal8Bit
                           ("Ruch na pozycjê (%1, %2), przeanalizowa³em %3 pozycji")
                           .arg(best.x).arg(best.y).arg(::evaluated_positions));
}

void KIKBoard::updateAtLogicalPosition(QPoint cl)
{
            QPainter p(&this->m_main_pixmap);
            p.drawImage(cl, imageOfPlayer(this->m_board.whoseTurn()));
            int rx, ry;
            this->contentsToViewport(cl.x(), cl.y(), rx, ry);
            this->viewport()->update(rx, ry, TILE_WIDTH, TILE_HEIGHT);
}

void KIKBoard::resizeBoard(int w, int h)
{
      m_board.resize(w, h);
      this->newGame();
}
