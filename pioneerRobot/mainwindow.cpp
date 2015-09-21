#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  conexionRobot=0;
  state=0;
  timer = new QTimer(this);
  timerRobot = new QTimer(this);
  grilla = new Grilla(this);
  ui->graphicsView->setScene(grilla);
  connect(ui->conectarButon,SIGNAL(clicked()),this,SLOT(conectarRobot()));
  connect(ui->iniciarButton,SIGNAL(clicked()),this,SLOT(iniciarRobot()));
  connect(ui->leftButton,SIGNAL(clicked()), this, SLOT(girarIzquierda()));
  connect(ui->rightButton,SIGNAL(clicked()), this, SLOT(girarDerecha()));
  connect(ui->upButton,SIGNAL(clicked()), this,SLOT(moverAdelante()));
  connect(ui->stopButon, SIGNAL(clicked()), this, SLOT(detener()));
  connect(timer, SIGNAL(timeout()), this, SLOT(datosRobot()));
  connect(timerRobot, SIGNAL(timeout()), this, SLOT(accionesRobot()));
}


void MainWindow::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  grilla->render(getCellHeight(), getCellWidth());
}

int MainWindow::getCellHeight() {
    return ui->graphicsView->geometry().height() / MATRIX_SIZE;
}

int MainWindow::getCellWidth() {
    return ui->graphicsView->geometry().width() / MATRIX_SIZE;
}

void MainWindow::conectarRobot(){
  int status;

  if(conexionRobot==0){
    robot = new PioneerRobot(CONEXION_SIMULADA, "", &status);
    if(status != 0){
      conexionRobot = status;
      ui->MensajeTxtEdit->setPlainText("Se a conectado con Exito.");
      ui->conectarButon->setText("Desconectar");
      grilla->recorridoRobot(robot->getXPos(),robot->getYPos());
    }
    else {
         conexionRobot = 0;
         ui->MensajeTxtEdit->setPlainText("No se ha podido realizar conexion.");
      }
  }
  else{
      robot->desconectar();
      conexionRobot = robot->isConnected();
      ui->MensajeTxtEdit->setPlainText("Se a Desconectado con Exito.");

      ui->conectarButon->setText("Conectar");
      timer->stop();
      timerRobot->stop();
  }
}
//acciones del temporizador
void MainWindow::datosRobot(){
  //CAPTURA Y MUESTRA DE INFORMACION
  robot->getAllSonar();
  for (int i = 0; i < 8; i++){
    //carga al arreglo s las lecturas del sonar
    s[i] = robot->aSonares[i].GetMeasure();
    //carga en diff2 el diferencial de la medicion anterior (diff) - la lectura actual)
    diff2[i] = diff[i] - s[i];
    //Almacena el diferencial para el siguiente comparador.
    diff[i] = s[i];
  }

  cout << "anterior " <<diff2[7] << "nueva" << s[7] << std::endl;
  leftRobot = getRobotDist(0,1);
  frontRobot = getRobotDist(3,4);
  rightRobot = getRobotDist(6,7);

  ui->xTxtLine->setText(QString::number(robot->getXPos(), 'f', 2));
  ui->yTxtLine->setText(QString::number(robot->getYPos(), 'f', 2));
  ui->anguloTxtLine->setText(QString::number(robot->getAngBase(), 'f', 2));

  ui->leftTxtLine->setText(QString::number(leftRobot, 'f', 2));
  ui->frontTxtLine->setText(QString::number(frontRobot, 'f', 2));
  ui->rightTxtLine->setText(QString::number(rightRobot, 'f', 2));
 // robot->ProcessSonarReading(robot->aSonares);
  grilla->recorridoRobot(robot->getXPos(),robot->getYPos());
}
void MainWindow::accionesRobot(){
  //TOMA DE DESICION Y MOVIMIENTOS DEL ROBOT
  static int m=0;
  handleSensors();

}


void MainWindow::iniciarRobot(){
  if(conexionRobot!=0){
      timerRobot->start(1000);
      timer->start(300);
  }

}

bool MainWindow::girarDerecha(){
  if(conexionRobot!=0){
    robot->pararMovimento();
    robot->Rotacion(-90);
    robot->pararMovimento();
  }
  return true;
}


bool MainWindow::girarIzquierda(){
  if(conexionRobot!=0){
    robot->pararMovimento();
    robot->Rotacion(90);
    robot->pararMovimento();
  }
  return true;
}

void MainWindow::moverAdelante(){
  if(conexionRobot!=0){
    robot->Move(100,100);
  }
}

void MainWindow::detener(){
  if(conexionRobot!=0){
  robot->pararMovimento();
  }
}



void MainWindow::handleSensors(){
  timerRobot->stop();

  cout << "estado: " << state << endl;
  switch (state){
  case INIT_STATE:
  case RUN_STRAIGHT:
    ui->MensajeTxtEdit->setPlainText("Mover Adelante");
    if (frontRobot < (STRAIGHT_DIST_LIMIT)){
      state = TURN_LEFT;
      break;
    }
    else robot->initMov();
    if (rightRobot <= DISTANCIA_MAX) state = RUN_PARALLEL;
    break;
  case RUN_PARALLEL:
    ui->MensajeTxtEdit->setPlainText("Alinear a la pared");

    switch (keepDistRightWall()) {
      case 1:
        cout << "contra la pared" << endl;
        state = RUN_PARALLEL;
        break;
      case 2:
        cout << "izquierda" << endl;
        robot->pararMovimento();
        state = TURN_LEFT;
        break;
      case 3:
        cout << "derecha" << endl;
        robot->pararMovimento();
        state = TURN_RIGHT;
      default:
        cout << "nada" << endl;
        break;
    }
    break;
  case TURN_LEFT:
    ui->MensajeTxtEdit->setPlainText("Girar a la izquierda ");
    girarIzquierda();
    state = RUN_PARALLEL;
    break;
  case TURN_RIGHT:
    ui->MensajeTxtEdit->setPlainText("Girar a la derecha");
    girarDerecha();
    state = RUN_STRAIGHT;
    break;
  }
  timerRobot->start();

}


int MainWindow::keepDistRightWall(){

  int left, right;
  //cambiar la velocidad de desplazamiento
  if (frontRobot > 2000){
    left = 400, right = 400;
  }
  else if(frontRobot > 1000){
    left = 250, right = 250;
  }
  else{
      left = 150, right = 150;
  }
  //si hay pared gire a la izquierda
  if (frontRobot < STRAIGHT_DIST_LIMIT){
    ui->MensajeTxtEdit->setPlainText("PARED ENFRENTE, girar a la izquierda");
    robot->pararMovimento();
    if (rightRobot<=DISTANCIA_MAX){
      cout << "pared de enfrente->giro izquierda" << endl;
      return 2;
    }
    else{
      cout << "pared de enfrente->giro derecha" << endl;
      return 3;
    }
  }
  else if (rightRobot>DISTANCIA_MAX) return 3;
  //si distancia anterior es menor a 100
  else {
    if (diff2[7] < 0){
        left += 5;
        right -= 5;
    }
    else if (diff2[7] > 0){
        left -= 5;
        right += 5;
    }

  }
  cout << left << " " << right << std::endl;
  robot->Move(left, right);
  return 1;
}

  /*
  //si se encuentra un octaculo de frente cambia de estado
  int left, right;
  if (frontRobot > 2000){
    left = 250, right = 250;
  }
  else if(frontRobot > 1000){
    left = 150, right = 150;
  }
  else{
      left = 100, right = 100;
  }

  if (frontRobot < DISTANCIA_MIN ){
    ui->MensajeTxtEdit->setPlainText("PARED ENFRENTE");
    //gira a la derecha si hay espacio sufiente
    if (rightRobot > DISTANCIA_MAX ) return 3;
    //gira a la izquierda
    else  return 2;
  }
  else if (rightRobot  > DISTANCIA_MAX){
    //debe girar a la derecha
    return 3;
  }
  else {  //Si la distancia derecha es menor a DISTANCIA_MAX
      //Acercandose
      left -= diff2[7];
      right += diff2[7];
      std::cout << "ajustando movimiento " << std::endl;
      std::cout << "left" << left << " right" << right << std::endl;
      robot->Move( right,left);
      return 4;
  }
}
 /*else{
    if ((s[7] < 5000) || (diff[7]>1000)){
      return RUN_STRAIGHT;
    }
     /* No puede hacerse ninguna accion. La distance de la pared es desconocida
    else return 0;
  }
}
*/

//calcula una medida de la distancia frontal del pioneer
int  MainWindow::getRobotDist(int n, int m){
  int i = 99999;
  //i = s[2] < i ? s[2] : i;
  i = s[n] < i ? s[n] : i;
  i = s[m] < i ? s[m] : i;
  return i;
}

MainWindow::~MainWindow(){
  delete ui;
}


