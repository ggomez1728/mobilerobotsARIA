#include "celda.h"

Celda::Celda(int x, int y, int height, int width) : QGraphicsRectItem(x, y, height, width) {
  setMapped(false);
  this->sensada =false;
}

void Celda::setMapped(bool recorrida){
  this->recorrida = recorrida;
  setBrush(recorrida ? Qt:: green : Qt::gray );
}
void Celda::setSensada(bool sensada){
  this->sensada = sensada;
  if(!recorrida)setBrush(sensada ? Qt:: blue : Qt::gray );
}


void Celda::mousePressEvent(QGraphicsSceneMouseEvent *){
  setMapped(!recorrida);
}
