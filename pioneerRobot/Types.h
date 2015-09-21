#ifndef TYPES_H
#define TYPES_H
#define PI (float)3.14159
#define MATRIX_X_SIZE	1000
#define MATRIX_Y_SIZE	1000
#define SIZE_CELL_M 0.2

struct Prob{
  float Occupied;
  float Empty;
};

struct Mapcell{
  bool bWalkedOver;    //recorrido por el Pioneer
  bool bSonarViewed;   //visto por el sonar
  bool bLaserViewed;
  // Added by Fernando
  Prob prob;
};

struct Position {
  float fX_m;
  float fY_m;
};
struct Index {
  int iX;
  int iY;
};

struct Cone{
  float fViewAngle_deg; // opening angle (full, 2*beta)
  float fAzimuth_deg;  // with respect to robot heading
  float fRange_m; // Maximum range of the sonar
};

struct Distance{
  int Value_m;
  float fError;
};







#endif // TYPES_H



