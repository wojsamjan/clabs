#ifndef INCLUDED__KIKBOARD_H
#define INCLUDED__KIKBOARD_H

#include <qpainter.h>
#include <qscrollview.h>
#include <qpixmap.h>
#include "game-repr.h"

// Graficzna reprezentacja tablicy pól -- opakowanie klasy GameBoard
class KIKBoard: public QScrollView {
      Q_OBJECT
public:
      void drawContents(QPainter* p, int x, int y, int w, int h);
      void contentsMousePressEvent(QMouseEvent* e);
      KIKBoard(QWidget* parent);

public slots:
      void newGame();
      void resizeBoard(int w, int h);
      QSize boardSize() { return QSize(m_board.width(), m_board.height()); }
signals:
      void shortInfo(const QString&);
private:
      QPixmap m_main_pixmap;
      KIK::GameBoard m_board;

      void doComputerMove();
      void handleUserMove(KIK::Move m);

      void announceNewGame();
      void prepareNewGame();
      void updateAtLogicalPosition(QPoint l);
};

#endif

