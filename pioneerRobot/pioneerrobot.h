#include "Aria.h"
#include "csonar.h"
#include "crobotmap.h"
#include "math.h"
#ifndef PIONEERROBOT_H
#define PIONEERROBOT_H
#define GirarBase          1
//opciones de tipo de conexion
#define CONEXION_SERIAL      1
#define CONEXION_RADIO       2
#define CONEXION_SIMULADA    3

#define NUM_OF_SONARS	8
#include "grilla.h"
class PioneerRobot {

  bool isInProcess;
public:
  ArRobot robot;
  ArSonarDevice sonarDev;
  ArSick sick;

  ArLaserConnector *laserConnector;
  ArRobotConnector *robotConnector;
  ArArgumentParser *parser;
  ArSimpleConnector *simpleConnector;

    //ArAnalogGyro *gyro; //Not used
  ArSerialConnection con1;

  CRobotMap stMap;

    //int Sensores[8]; Substituido por Objeto CSonar
    CSonar aSonares[NUM_OF_SONARS];

    PioneerRobot(int tipoConexion, char* info, int *suceso);

    void destroy();
    void desconectar();
    void pararMovimento();

    double getSonar(int sonarLeft, int sonarRight);
    int  isConnected();

    float getXPos();
    float getYPos();
    float getAngBase();

    void turnRight();
    void turnLeft();
    bool turnCheked();

    void initMov();
    void Rotacion(double degrees);
    int  getSonar(int i);
    void getAllSonar();

    void Move(double vl,double vr);
    void getLaser();

    void ProcessSonarReading(CSonar* sonar);
};

#endif // PIONEERROBOT_H
