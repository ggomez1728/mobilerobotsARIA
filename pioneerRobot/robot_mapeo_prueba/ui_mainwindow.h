/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *xTxtLine;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *yTxtLine;
    QGraphicsView *graphicsView;
    QPushButton *iniciarButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QPlainTextEdit *MensajeTxtEdit;
    QPushButton *conectarButon;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *leftButton;
    QPushButton *rigthButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 500);
        MainWindow->setMaximumSize(QSize(700, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 151, 112));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        xTxtLine = new QLineEdit(groupBox);
        xTxtLine->setObjectName(QStringLiteral("xTxtLine"));

        horizontalLayout_2->addWidget(xTxtLine);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        yTxtLine = new QLineEdit(groupBox);
        yTxtLine->setObjectName(QStringLiteral("yTxtLine"));

        horizontalLayout->addWidget(yTxtLine);


        verticalLayout->addLayout(horizontalLayout);

        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(270, 10, 400, 400));
        graphicsView->setMaximumSize(QSize(550, 16777215));
        iniciarButton = new QPushButton(widget);
        iniciarButton->setObjectName(QStringLiteral("iniciarButton"));
        iniciarButton->setGeometry(QRect(170, 70, 71, 31));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 260, 231, 161));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        MensajeTxtEdit = new QPlainTextEdit(groupBox_2);
        MensajeTxtEdit->setObjectName(QStringLiteral("MensajeTxtEdit"));

        verticalLayout_2->addWidget(MensajeTxtEdit);

        conectarButon = new QPushButton(groupBox_2);
        conectarButon->setObjectName(QStringLiteral("conectarButon"));

        verticalLayout_2->addWidget(conectarButon);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 120, 121, 121));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        leftButton = new QPushButton(widget_2);
        leftButton->setObjectName(QStringLiteral("leftButton"));

        horizontalLayout_3->addWidget(leftButton);

        rigthButton = new QPushButton(widget_2);
        rigthButton->setObjectName(QStringLiteral("rigthButton"));

        horizontalLayout_3->addWidget(rigthButton);


        verticalLayout_4->addWidget(widget_2);


        verticalLayout_3->addWidget(widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(yTxtLine, xTxtLine);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Robot de Mapeo", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Desplazamiento:", 0));
        label_2->setText(QApplication::translate("MainWindow", "X:", 0));
        label->setText(QApplication::translate("MainWindow", "Y:", 0));
        iniciarButton->setText(QApplication::translate("MainWindow", "Iniciar", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Robot Pioneer", 0));
        label_3->setText(QApplication::translate("MainWindow", "Mensaje", 0));
        MensajeTxtEdit->setPlainText(QString());
        conectarButon->setText(QApplication::translate("MainWindow", "Conectar", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Control Manual", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        leftButton->setText(QApplication::translate("MainWindow", "<<", 0));
        rigthButton->setText(QApplication::translate("MainWindow", ">>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
