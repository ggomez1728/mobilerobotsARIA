#include "pioneerrobot.h"
#include "crobotmap.h"
#define TURN_ANGLE 90.0
#include<iostream>


PioneerRobot:: PioneerRobot(int tipoConexion, char* info, int *suceso){
  int argc=0;char** argv;
  isInProcess = false;
  Aria::init();
  switch (tipoConexion) {
    case CONEXION_SERIAL:{
      char port1[4];
      strcpy(port1,info);
      int ret;
      std::string str;
      *suceso=((ret = con1.open(port1))== 0);
      if (*suceso){ robot.setDeviceConnection(&con1);}
      *suceso=robot.blockingConnect();
      break;
    }
    case CONEXION_RADIO: {
      argc=4;
      argv =(char **) new char[4];
      argv[0]=new char[4];
      argv[1]=new char[20];
      argv[2]=new char[20];
      argv[3]=new char[7];

      strcpy(argv[0],"-rh");
      strcpy(argv[1],info);
      strcpy(argv[2],"-remoteLaserTcpPort");
      strcpy(argv[3],"10002");
      parser=new ArArgumentParser(&argc, argv);
      robotConnector=new ArRobotConnector(parser,&robot);
      *suceso=robotConnector->connectRobot();
      if (!(*suceso)){Aria::shutdown();break;}
      robot.addRangeDevice(&sick);
      laserConnector=new ArLaserConnector(parser, &robot, robotConnector);
      laserConnector->setupLaser(&sick);
      break;
      }
      case CONEXION_SIMULADA: {
        argc=2;
        argv =(char **) new char[2];
        argv[0]=new char[4];

        argv[1]=new char[20];
        strcpy(argv[0],"-rh");
        strcpy(argv[1],"localhost");
        parser=new ArArgumentParser(&argc, argv);
        robotConnector=new ArRobotConnector(parser,&robot);
        *suceso=robotConnector->connectRobot();
        if (!(*suceso)) {
          Aria::shutdown();
          break;
        }
        robot.addRangeDevice(&sick);
        laserConnector=new ArLaserConnector(parser, &robot, robotConnector);
        laserConnector->setupLaser(&sick);
     }
  }
  if (*suceso) {
    robot.addRangeDevice(&sonarDev);
    if (*suceso){
      sick.runAsync();
      robot.setHeading(0);
      robot.runAsync(true);
      robot.enableMotors();
      robot.setRotVelMax(10);
      printf("Connecting...\n");
      if (!laserConnector->connectLaser(&sick)){
        printf("Could not connect to lasers... exiting\n");
        Aria::exit(2);
      }
      /* initialize sonars data attributes*/
/*
    for (int i = 0; i < NUM_OF_SONARS; i++)
        aSonares[i] = new CSonar(30, i * 180 / 7 - 15 - 75, 5);

    */
    }
    else Aria::shutdown();
  }
  else 	Aria::shutdown();
}

int PioneerRobot::isConnected(){ return (robot.isConnected()); }

void PioneerRobot::destroy() { desconectar();Aria::shutdown(); }

void PioneerRobot::pararMovimento() { robot.stop(); }

void PioneerRobot::desconectar() { robot.stopRunning(true); }

//adquisicion espacial

float PioneerRobot::getXPos() { return (robot.getX()/10);}
float PioneerRobot::getYPos() { return (robot.getY()/10);}
float PioneerRobot::getAngBase() { return (robot.getTh()); }

//movimientos
void PioneerRobot::initMov() { robot.setVel2(400,400);}
void PioneerRobot::Rotacion(double degrees){
  robot.setDeltaHeading(degrees);
  while (!(robot.isHeadingDone(2))) {};
/*  if (Sentido==0)
    robot.setVel(0);
  else if (Sentido==1)
    robot.setVel(50);
  else if (Sentido==2)
    robot.setVel(-50);
*/
}
void PioneerRobot::Move(double vl,double vr) {
  robot.setVel2(vl,vr);
}
//sensores

double PioneerRobot::getSonar(int sonarLeft, int sonarRight){
  return sonarDev.cumulativeReadingPolar(sonarLeft, sonarRight) - robot.getRobotRadius();
  }

int PioneerRobot::getSonar(int i){
   //Position OwnPos = { getXPos(), getYPos() };
  //stMap.SetCone(OwnPos, 0, aSonares[i]->GetCone());
  return(aSonares[i].GetMeasure());
}


void PioneerRobot::getAllSonar() {
  //ubico nuestra posicion
  Position OwnPos = { getXPos() / 100 , getYPos() / 100 };
  for (int i = 0; i < 8; i++) {
    aSonares[i].SetMeasure((int)(robot.getSonarRange(i)));
    stMap.SetCone(OwnPos, getAngBase(), aSonares[i].GetCone(), aSonares[i].GetMeasure()/1000);
    ProcessSonarReading(&aSonares[i]);
  }
}

void PioneerRobot::getLaser()  {
  sick.getRawReadings();
  std::vector < ArSensorReading > *readings;
  std::vector < ArSensorReading > ::iterator it;
  FILE* dataFile;
  dataFile = fopen("Laser_log.txt", "w");
  sick.lockDevice();
  readings = sick.getRawReadingsAsVector();
  if(sick.isConnected())
    fprintf (dataFile, "sim");//,readings->size());
  else fprintf (dataFile, "nao");//,readings->size());
  fprintf (dataFile, "%f 2 \n",readings->size());
  for (it = readings->begin(); it!=readings->end(); it++){
    fprintf( dataFile, " %f %f\n" , (*it).getX(), (*it).getY());//,(*it).get );
  }
   sick.unlockDevice();
   fclose ( dataFile );
  }


void PioneerRobot::ProcessSonarReading(CSonar* sonar){

  Index stSweepSqStart_id, stSweepSqStop_id;
  Position stSweepSqStart_m, stSweepSqStop_m;
  Position GridOrigin, robotPos, cellCenter;
  int i, j;
  Index ij;
  bool bIsInsideRegion1, bIsInsideRegion2;
  Cone SonarCone = sonar->GetCone();

  robotPos.fX_m = getXPos();
  robotPos.fY_m = getYPos();

  stSweepSqStart_m.fX_m = robotPos.fX_m - (SonarCone.fRange_m + (float)SIZE_CELL_M);
  stSweepSqStart_m.fY_m = robotPos.fY_m - (SonarCone.fRange_m + (float)SIZE_CELL_M);
  stSweepSqStop_m.fX_m = robotPos.fX_m + (SonarCone.fRange_m + (float)SIZE_CELL_M);
  stSweepSqStop_m.fY_m = robotPos.fY_m + (SonarCone.fRange_m + (float)SIZE_CELL_M);

  // Sweep a square with size 2R_sonar + cellSize around the robot
  stSweepSqStart_id = stMap.PositionToIndex(stSweepSqStart_m);
  stSweepSqStop_id = stMap.PositionToIndex(stSweepSqStop_m);

  for (i = stSweepSqStart_id.iX; i < stSweepSqStop_id.iX; i++) {
    for (j = stSweepSqStart_id.iY; j < stSweepSqStop_id.iY; j++) {
      float r = 0, alpha = 0;
      float R, beta;
      R = SonarCone.fRange_m;
      beta = SonarCone.fViewAngle_deg / 2;
      ij.iX = i;
      ij.iY = j;
      cellCenter = stMap.IndexToPosition(ij);
      // Check if the cell center point is inside the REGION 1 sector
      // Compruebe si la celda central de células que hay dentro del sector REGIÓN 1
      bIsInsideRegion1 = stMap.isInsideSector(robotPos,
              sonar->GetMeasure() - sonar->ToleranceRegion1_m,
              sonar->GetMeasure() + sonar->ToleranceRegion1_m,
              getAngBase() + SonarCone.fAzimuth_deg + beta,
              getAngBase() + SonarCone.fAzimuth_deg - beta,
              cellCenter, &r, &alpha);
      if (bIsInsideRegion1) {
        /* This is a region 1 cell */
        /* Update Bayes probability of the cell here */
        float P_occup_region_1, P_empty_region_1;
        P_occup_region_1 = ((R - (r / 2)) / R +
                            (beta - abs(alpha / 2)) / beta) / 2 * sonar->MaxOccupied;
        /* P(sn|H) */
        P_empty_region_1 = 1 - P_occup_region_1;
        stMap.Map[i][j].prob.Occupied = stMap.UpdateBayesFilter( P_occup_region_1,
                                        stMap.Map[i][j].prob.Occupied,
                                        P_empty_region_1,
                                        stMap.Map[i][j].prob.Empty
                                        );
        // Limit to 0.98
        if (stMap.Map[i][j].prob.Occupied > 0.98) {
          stMap.Map[i][j].prob.Occupied = 0.98;
        }
        else if (stMap.Map[i][j].prob.Occupied < 0.02) {
          stMap.Map[i][j].prob.Occupied = 0.02;
        }
        stMap.Map[i][j].prob.Empty = 1 - stMap.Map[i][j].prob.Occupied;
      }
      else
      {
        // Check if the cell center point is inside the REGION 2 sector
        bIsInsideRegion2 = stMap.isInsideSector(robotPos, 0,
                      sonar->GetMeasure() - sonar->ToleranceRegion1_m,
                      getAngBase() + SonarCone.fAzimuth_deg + beta,
                      getAngBase() + SonarCone.fAzimuth_deg - beta,
                      cellCenter, &r, &alpha);
        if (bIsInsideRegion2) {
          /* This is a region 2 cell */
          /* Update Bayes probability of the cell here */
          float P_occup_region_2, P_empty_region_2;
          /* P(sn|H) */
          P_empty_region_2 = ((R - (r / 2)) / R + (beta - abs(alpha / 2)) / beta) / 2;
          P_occup_region_2 = 1 - P_empty_region_2;
          stMap.Map[i][j].prob.Occupied = stMap.UpdateBayesFilter(P_occup_region_2,
                                                stMap.Map[i][j].prob.Occupied,
                                                P_empty_region_2,
                                                stMap.Map[i][j].prob.Empty);
          // Limit to 0.98
          if (stMap.Map[i][j].prob.Occupied > 0.98) {
            stMap.Map[i][j].prob.Occupied = 0.98;
          }
          else if (stMap.Map[i][j].prob.Occupied < 0.02) {
            stMap.Map[i][j].prob.Occupied = 0.02;
          }
          stMap.Map[i][j].prob.Empty = 1 - stMap.Map[i][j].prob.Occupied;
        }
        else{
          // Check if the cell center point is inside the REGION 2 sector
          bIsInsideRegion2 = stMap.isInsideSector(robotPos,0,
                                                  sonar->GetMeasure() - sonar->ToleranceRegion1_m,
                                                  getAngBase() + SonarCone.fAzimuth_deg + beta,
                                                  getAngBase() + SonarCone.fAzimuth_deg - beta,
                                                  cellCenter,
                                                  &r,
                                                  &alpha);
          if (bIsInsideRegion2){
            /* This is a region 2 cell */
            /* Update Bayes probability of the cell here */
            float P_occup_region_2, P_empty_region_2;
            P_empty_region_2 = ((R - (r / 2)) / R + (beta - abs(alpha / 2)) / beta) / 2; /* P(sn|H) */
            P_occup_region_2 = 1 - P_empty_region_2;
            stMap.Map[i][j].prob.Occupied = stMap.UpdateBayesFilter(P_occup_region_2,
                                                   stMap.Map[i][j].prob.Occupied,
                                                   P_empty_region_2,
                                                   stMap.Map[i][j].prob.Empty);
            // Limit to 0.98
            if (stMap.Map[i][j].prob.Occupied > 0.98){
              stMap.Map[i][j].prob.Occupied = 0.98;
            }
            else if (stMap.Map[i][j].prob.Occupied < 0.02){
              stMap.Map[i][j].prob.Occupied = 0.02;
            }
            stMap.Map[i][j].prob.Empty = 1 - stMap.Map[i][j].prob.Occupied;
          }
        }
      }
    }
  }
}

void PioneerRobot::turnRight(){
  if (!isInProcess){
    robot.setHeading(TURN_ANGLE);
    Move(150, -150);
    isInProcess = true;
  }
}

void PioneerRobot::turnLeft(){
  if (!isInProcess){
    robot.setHeading(-TURN_ANGLE);
    Move(-150, 150);
    isInProcess = true;
  }
}

bool PioneerRobot::turnCheked(){
  if (isInProcess){
    if (robot.isHeadingDone(5)){
      robot.stop();
      isInProcess = false;
    }
  }
  return isInProcess;
}

