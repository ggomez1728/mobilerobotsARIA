#include "grilla.h"

Grilla::Grilla(QObject *parent) : QGraphicsScene(parent){
  setBackgroundBrush(Qt::white);

}

void Grilla::render(int height, int width){
  for (int y = 0; y < MATRIX_SIZE; y++) {
      for (int x = 0; x < MATRIX_SIZE; x++) {
          Celda *celda = new Celda(x * width, y * height, height, width);
          celdas[x][y] = celda;
          celda->setPen(Qt::NoPen);
          addItem(celda);
      }
  }
}

void Grilla::clearCells(){
  for (int y = 0; y < MATRIX_SIZE; y++)
      for (int x = 0; x < MATRIX_SIZE; x++)
          celdas[x][y]->setMapped(false);
}

void Grilla::simular(){
   celdas[200][200]->setMapped(true);
   celdas[200][201]->setMapped(true);
   celdas[200][202]->setMapped(true);
   celdas[200][203]->setMapped(true);
   celdas[201][200]->setMapped(true);
   celdas[201][201]->setMapped(true);
   celdas[201][202]->setMapped(true);
   celdas[201][203]->setMapped(true);

}

void Grilla::recorridoRobot(int x, int y){
  int xMap, yMap;
  xMap=(x/10)+ (MATRIX_SIZE/3);
  yMap=(-y/10)+ (MATRIX_SIZE/3);

  celdas[xMap+1][yMap+1]->setMapped(true);
  celdas[xMap+1][yMap]->setMapped(true);
  celdas[xMap][yMap+1]->setMapped(true);
  celdas[xMap][yMap]->setMapped(true);
  celdas[xMap][yMap-1]->setMapped(true);
  celdas[xMap-1][yMap]->setMapped(true);
  celdas[xMap-1][yMap-1]->setMapped(true);

}
