#ifndef GRILLA_H
#define GRILLA_H

#define MATRIX_SIZE 1000

#include <QGraphicsScene>
#include "celda.h"

class Grilla : public QGraphicsScene{
  Q_OBJECT
protected:
  Celda *celdas[MATRIX_SIZE][MATRIX_SIZE];
public:
  Grilla(QObject *parent = 0);
  void render(int height, int width);
  void simular();
  void recorridoRobot(int x, int y);
public slots:
    void clearCells();

};

#endif // GRILLA_H
