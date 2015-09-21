#ifndef CROBOTMAP_H
#define CROBOTMAP_H

#include "math.h"
#include "Types.h"

class CRobotMap
{
public:
  Mapcell Map[MATRIX_X_SIZE][MATRIX_Y_SIZE];
  bool SetCellWalked(Position stPos, bool bWalked);
  bool SetCone(Position stPos, float fRobotAngle, Cone stCone, int distance);

  Index PositionToIndex(Position stPosition);
  Position IndexToPosition(Index stIndex);

  // Comprueba si el punto [pX, pY] está dentro del sector definido
  bool isInsideSector(Position origin, float R1, float R2, float ang1_deg, float ang2_deg, Position testpoint, float *rDist_m, float *rAngle_deg);
  //actualiza la probabilidad de ocupado o vacío de acuerdo con el teorema de Bayes
  float UpdateBayesFilter(float P_sn_H, float P_H_sn_Minus1, float P_sn_notH, float P_notH_sn_Minus1);


  CRobotMap();
  ~CRobotMap();
};

#endif // CROBOTMAP_H
