#ifndef CELDA_H
#define CELDA_H

#include <QGraphicsRectItem>
#include <QBrush>

class Celda: public QGraphicsRectItem{
  bool recorrida;
  bool sensada;
  double ponderacion;
public:
  Celda(int x, int y, int height, int width);
  void setMapped(bool recorrida);
  void setSensada(bool sensada);
  void mousePressEvent(QGraphicsSceneMouseEvent */*event*/);
};

#endif // CELDA_H
