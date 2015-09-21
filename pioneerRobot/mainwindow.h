#include "Aria.h"
#include "pioneerrobot.h"

#define INIT_STATE 0
#define RUN_PARALLEL 1
#define TURN_LEFT 2
#define RUN_STRAIGHT 3
#define TURN_RIGHT 4
#define RUN_STRAIGHT_FOR_PARALELL 5


#define DISTANCIA_MIN 550
#define DISTANCIA_MAX 800
#define STRAIGHT_DIST_LIMIT 500


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>


#include "grilla.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  Ui::MainWindow *ui;
  QTimer *timer;
  QTimer *timerRobot;
  int leftRobot, rightRobot, frontRobot;
  int getCellHeight();
  int getCellWidth();
  int conexionRobot;
  int s[8];
  int diff[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int diff2[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int state;
public:

  int g_argc;
  char **g_argv;
  Grilla *grilla;
  PioneerRobot* robot;


  explicit MainWindow(QWidget *parent = 0);
  void showEvent(QShowEvent *event);
  ~MainWindow();

private slots:
  void conectarRobot();
  void iniciarRobot();
  void datosRobot();
  void accionesRobot();


  //movimiento manual
  bool girarDerecha();
  bool girarIzquierda();
  void moverAdelante();
  void detener();
  void handleSensors();

  int keepDistRightWall();
  int getRobotDist(int n, int m);
};

#endif // MAINWINDOW_H
