#include "crobotmap.h"

CRobotMap::CRobotMap(){
  for (int i = 0; i < MATRIX_X_SIZE; i++)
    for (int j = 0; j < MATRIX_Y_SIZE; j++) {
      Map[i][j].prob.Empty = 0.5;
      Map[i][j].prob.Occupied = 0.5;
    }
}

CRobotMap::~CRobotMap(){

}

bool CRobotMap::SetCellWalked(Position stPos, bool bWalked) {
  Index tempIndex = PositionToIndex(stPos);
  if (tempIndex.iX < MATRIX_X_SIZE && tempIndex.iY < MATRIX_Y_SIZE) {
    Map[tempIndex.iX][tempIndex.iY].bWalkedOver = bWalked;
    return true;
  }
  else return false;
}

Index CRobotMap::PositionToIndex(Position stPosition){
  Index Result;
  Result.iX = -999999;
  Result.iY = -999999;
  int tempX = (MATRIX_X_SIZE/2) + floor(stPosition.fX_m / SIZE_CELL_M);
  int tempY = (MATRIX_Y_SIZE/2)+floor(stPosition.fX_m / SIZE_CELL_M);
  if ((tempX < MATRIX_X_SIZE) || (tempY< MATRIX_Y_SIZE)) {
    Result.iX = tempX;
    Result.iY = tempY;
  }
  return Result;
}

Position CRobotMap::IndexToPosition(Index stIndex){
  Position Result;
  Result.fX_m = (float)((stIndex.iX - (MATRIX_X_SIZE / 2)) * SIZE_CELL_M) - SIZE_CELL_M / 2;
  Result.fY_m = (float)((stIndex.iY - (MATRIX_Y_SIZE / 2)) * SIZE_CELL_M) - SIZE_CELL_M / 2;
  return Result;
}

bool CRobotMap::SetCone(Position stPos, float fRobotAngle, Cone stCone, int distance){
  Position fMinPos, fMaxPos;
  Index iMinIndex, iMaxIndex;
  fRobotAngle = -fRobotAngle;

  /*fMinPos.fX_m = stPos.fX_m - stCone.fRange_m;
  fMinPos.fY_m = stPos.fY_m - stCone.fRange_m;
  fMaxPos.fX_m = stPos.fX_m + stCone.fRange_m;
  MaxPos.fY_m = stPos.fY_m + stCone.fRange_m;*/

  fMinPos.fX_m = stPos.fX_m - distance;
  fMinPos.fY_m = stPos.fY_m - distance;
  fMaxPos.fX_m = stPos.fX_m + distance;
  fMaxPos.fY_m = stPos.fY_m + distance;

  iMinIndex = PositionToIndex(fMinPos);
  iMaxIndex = PositionToIndex(fMaxPos);

  //Check if it is -1
  for (int y = iMinIndex.iY; y <= iMaxIndex.iY; y++) {
    for (int x = iMinIndex.iX; x <= iMaxIndex.iX; x++) {
      Index tempIndex;
      Position tempPosition;
      tempIndex.iX = x;
      tempIndex.iY = y;
      tempPosition = IndexToPosition(tempIndex);
      float CO = tempPosition.fX_m - stPos.fX_m;
      float CA = tempPosition.fY_m - stPos.fY_m;
      float H = sqrt((CO * CO) + (CA * CA));
      float RelativeAngle = -(atan2(CA,CO) * 180 / 3.1415); //TODO fix constants
      float fBeamAngle_deg = (((int)(fRobotAngle) % 360) +
                              fRobotAngle - ((float)((int)fRobotAngle))
                              + stCone.fAzimuth_deg); /* precisao corrigida*/
      if (RelativeAngle > (fBeamAngle_deg - stCone.fViewAngle_deg / 2) &&
          RelativeAngle < (fBeamAngle_deg + stCone.fViewAngle_deg / 2) &&
                        //(H < stCone.fRange_m))
          (H < distance)) {
        Map[x][y].bSonarViewed = true;
      }
    }
  }
  return true;
}


bool CRobotMap::isInsideSector(Position origin, float R1, float R2, float ang1_deg, float ang2_deg, Position testpoint, float *rDist_m, float *rAngle_deg) {
  bool bIsInside;
  // Calculate the distance and angle from the origin
  *rDist_m = sqrt(powf((origin.fX_m - testpoint.fX_m), 2) + powf((origin.fY_m - testpoint.fY_m), 2));
  *rAngle_deg = atan2((testpoint.fY_m - origin.fY_m), (testpoint.fX_m - origin.fX_m)) * 180 / PI;
  if ((ang1_deg > -180) && (ang1_deg <= 180)) {
    //Correct angles to be[-180, 180]
    if (ang2_deg > 180)	{
      ang2_deg = ang2_deg - 360;
    }
    else if (ang1_deg <= -180) {
      // Correct angles to be[-360, 0]
      if (ang2_deg > 0)
      ang2_deg = ang2_deg - 360;
      if (*rAngle_deg > 0)*rAngle_deg = *rAngle_deg - 360;
    }
    else{
      // Correct angles to be[0, 360]
      if (ang2_deg < 0) ang2_deg = ang2_deg + 360;
      if (*rAngle_deg < 0) *rAngle_deg = *rAngle_deg + 360;
    }
  }
  if ((*rDist_m >= R1) && (*rDist_m <= R2)){
    if ((ang1_deg >= *rAngle_deg) && (*rAngle_deg >= ang2_deg))
      bIsInside = true;
    else bIsInside = false;
  }
  else	bIsInside = false;
  return bIsInside;
}



float CRobotMap::UpdateBayesFilter(float P_sn_H, float P_H_sn_Minus1, float P_sn_notH, float P_notH_sn_Minus1){
  /*UPDATEBAYESFILTER This function updates the bayes filter
  INPUT ARGS :
  P_sn_H is P(sn | H), the prob of having a reading given occup or empty
  P_H_sn_Minus1 is P(H | sn - 1), the prob of being occup or empty given the reading
  P_sn_notH is P(sn | not(H))
  P_notH_sn_Minus1 is P(not(H) | sn - 1)
  OUTPUT ARGS :
  P_H_sn is P(H | sn), the prob of being occup / empty given all readings

  H is the event(hypotesis) of sending the acoustic sonar wave.The
  outcomes can be OCCUPIED or EMPTY
  */
  float P_H_sn;
  P_H_sn = (P_sn_H * P_H_sn_Minus1) / ((P_sn_H * P_H_sn_Minus1) +
            (P_sn_notH * P_notH_sn_Minus1));
  return P_H_sn;
}

