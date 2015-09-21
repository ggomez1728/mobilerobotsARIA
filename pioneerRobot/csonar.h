#ifndef CSONAR_H
#define CSONAR_H

#include "Types.h"
class CSonar{
  Position SonarOffsetPosition;
  float RelativeAngle;
  Cone SonarCone;
  Distance stMeasure;

public:
  CSonar();
  CSonar(float alfa, float bearing, float range);

  float ToleranceRegion1_m; //  [m] this is the tolerance or thickness of region 1
  float MaxOccupied;        // the maximum set for P(sn|O)
  //Accessors
  int GetMeasure();
  void SetMeasure(int iMeasure);
  void SetCone(Cone stCone);
  Cone GetCone();
  Position GetOffsetPosition();


};

#endif // CSONAR_H
