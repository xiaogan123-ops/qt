/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btu1;
    QPushButton *btu2;
    QPushButton *btu3;
    QPushButton *btu4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btu1 = new QPushButton(centralwidget);
        btu1->setObjectName("btu1");
        btu1->setGeometry(QRect(360, 350, 131, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft PhagsPa")});
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        btu1->setFont(font);
        btu1->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    /* \345\210\206\345\261\202\350\203\214\346\231\257\357\274\232\345\233\276\347\211\207\345\234\250\344\270\213\357\274\214\346\270\220\345\217\230\345\234\250\344\270\212 */\n"
"    background-image: url(:/res/ground.jpg),\n"
"                     qradialgradient(spread:repeat,\n"
"                                    cx:0.5, cy:0.5, radius:0.077,\n"
"                                    fx:0.5, fy:0.5,\n"
"                                    stop:0 rgba(0, 169, 255, 58),\n"
"                                    stop:0.5 rgba(0, 0, 0, 58),\n"
"                                    stop:1 rgba(0, 169, 255, 58));\n"
"    \n"
"    /* \350\203\214\346\231\257\346\267\267\345\220\210\346\250\241\345\274\217 */\n"
"    background-blend-mode: overlay;\n"
"    \n"
"    /* \345\244\207\347\224\250\350\203\214\346\231\257\350\211\262 */\n"
"    background-color: rgb(85, 170, 127);\n"
"    \n"
"    /* \345\255\227\344\275\223\350\256\276\347\275\256 */\n"
"    font: 24pt \"Microsoft PhagsPa\";\n"
"}"));
        btu2 = new QPushButton(centralwidget);
        btu2->setObjectName("btu2");
        btu2->setGeometry(QRect(20, 350, 131, 81));
        btu2->setFont(font);
        btu2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    /* \345\210\206\345\261\202\350\203\214\346\231\257\357\274\232\345\233\276\347\211\207\345\234\250\344\270\213\357\274\214\346\270\220\345\217\230\345\234\250\344\270\212 */\n"
"    background-image: url(:/res/ground.jpg),\n"
"                     qradialgradient(spread:repeat,\n"
"                                    cx:0.5, cy:0.5, radius:0.077,\n"
"                                    fx:0.5, fy:0.5,\n"
"                                    stop:0 rgba(0, 169, 255, 58),\n"
"                                    stop:0.5 rgba(0, 0, 0, 58),\n"
"                                    stop:1 rgba(0, 169, 255, 58));\n"
"    \n"
"    /* \350\203\214\346\231\257\346\267\267\345\220\210\346\250\241\345\274\217 */\n"
"    background-blend-mode: overlay;\n"
"    \n"
"    /* \345\244\207\347\224\250\350\203\214\346\231\257\350\211\262 */\n"
"    background-color: rgb(85, 170, 127);\n"
"    \n"
"    /* \345\255\227\344\275\223\350\256\276\347\275\256 */\n"
"    font: 24pt \"Microsoft PhagsPa\";\n"
"}"));
        btu3 = new QPushButton(centralwidget);
        btu3->setObjectName("btu3");
        btu3->setGeometry(QRect(520, 350, 131, 81));
        btu3->setFont(font);
        btu3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    /* \345\210\206\345\261\202\350\203\214\346\231\257\357\274\232\345\233\276\347\211\207\345\234\250\344\270\213\357\274\214\346\270\220\345\217\230\345\234\250\344\270\212 */\n"
"    background-image: url(:/res/ground.jpg),\n"
"                     qradialgradient(spread:repeat,\n"
"                                    cx:0.5, cy:0.5, radius:0.077,\n"
"                                    fx:0.5, fy:0.5,\n"
"                                    stop:0 rgba(0, 169, 255, 58),\n"
"                                    stop:0.5 rgba(0, 0, 0, 58),\n"
"                                    stop:1 rgba(0, 169, 255, 58));\n"
"    \n"
"    /* \350\203\214\346\231\257\346\267\267\345\220\210\346\250\241\345\274\217 */\n"
"    background-blend-mode: overlay;\n"
"    \n"
"    /* \345\244\207\347\224\250\350\203\214\346\231\257\350\211\262 */\n"
"    background-color: rgb(85, 170, 127);\n"
"    \n"
"    /* \345\255\227\344\275\223\350\256\276\347\275\256 */\n"
"    font: 24pt \"Microsoft PhagsPa\";\n"
"}"));
        btu4 = new QPushButton(centralwidget);
        btu4->setObjectName("btu4");
        btu4->setGeometry(QRect(190, 350, 131, 81));
        btu4->setFont(font);
        btu4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    /* \345\210\206\345\261\202\350\203\214\346\231\257\357\274\232\345\233\276\347\211\207\345\234\250\344\270\213\357\274\214\346\270\220\345\217\230\345\234\250\344\270\212 */\n"
"    background-image: url(:/res/ground.jpg),\n"
"                     qradialgradient(spread:repeat,\n"
"                                    cx:0.5, cy:0.5, radius:0.077,\n"
"                                    fx:0.5, fy:0.5,\n"
"                                    stop:0 rgba(0, 169, 255, 58),\n"
"                                    stop:0.5 rgba(0, 0, 0, 58),\n"
"                                    stop:1 rgba(0, 169, 255, 58));\n"
"    \n"
"    /* \350\203\214\346\231\257\346\267\267\345\220\210\346\250\241\345\274\217 */\n"
"    background-blend-mode: overlay;\n"
"    \n"
"    /* \345\244\207\347\224\250\350\203\214\346\231\257\350\211\262 */\n"
"    background-color: rgb(85, 170, 127);\n"
"    \n"
"    /* \345\255\227\344\275\223\350\256\276\347\275\256 */\n"
"    font: 24pt \"Microsoft PhagsPa\";\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "maze", nullptr));
        btu1->setText(QCoreApplication::translate("MainWindow", "\345\205\263 \344\272\216", nullptr));
        btu2->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        btu3->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        btu4->setText(QCoreApplication::translate("MainWindow", "\345\210\266\344\275\234\350\277\267\345\256\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
