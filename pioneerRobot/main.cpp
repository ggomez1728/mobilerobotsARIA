#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[]){

  QApplication a(argc, argv);
  MainWindow w;
  w.g_argc=argc;
  w.g_argv=argv;
  w.show();


  return a.exec();
}
