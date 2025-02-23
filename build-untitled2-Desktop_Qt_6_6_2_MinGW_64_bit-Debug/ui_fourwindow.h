/********************************************************************************
** Form generated from reading UI file 'fourwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOURWINDOW_H
#define UI_FOURWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FourWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btu1;
    QSpinBox *spinBox_2;
    QPushButton *btu2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox;
    QComboBox *algorithmComboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FourWindow)
    {
        if (FourWindow->objectName().isEmpty())
            FourWindow->setObjectName("FourWindow");
        FourWindow->resize(800, 600);
        centralwidget = new QWidget(FourWindow);
        centralwidget->setObjectName("centralwidget");
        btu1 = new QPushButton(centralwidget);
        btu1->setObjectName("btu1");
        btu1->setGeometry(QRect(540, 420, 111, 51));
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
        spinBox_2 = new QSpinBox(centralwidget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(580, 130, 51, 31));
        btu2 = new QPushButton(centralwidget);
        btu2->setObjectName("btu2");
        btu2->setGeometry(QRect(540, 350, 111, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft PhagsPa")});
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setItalic(false);
        btu2->setFont(font1);
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
"    font: 20pt \"Microsoft PhagsPa\";\n"
"}"));
        spinBox_3 = new QSpinBox(centralwidget);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(580, 250, 51, 31));
        spinBox_4 = new QSpinBox(centralwidget);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setGeometry(QRect(580, 290, 51, 31));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(580, 90, 51, 31));
        algorithmComboBox = new QComboBox(centralwidget);
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->setObjectName("algorithmComboBox");
        algorithmComboBox->setGeometry(QRect(500, 40, 171, 41));
        QFont font2;
        font2.setPointSize(14);
        algorithmComboBox->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(520, 10, 121, 31));
        QFont font3;
        font3.setPointSize(12);
        label->setFont(font3);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(540, 90, 41, 31));
        label_2->setFont(font3);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(540, 130, 41, 21));
        label_3->setFont(font3);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(530, 250, 41, 31));
        label_4->setFont(font3);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(530, 290, 41, 21));
        label_5->setFont(font3);
        spinBox_5 = new QSpinBox(centralwidget);
        spinBox_5->setObjectName("spinBox_5");
        spinBox_5->setGeometry(QRect(580, 170, 51, 31));
        spinBox_6 = new QSpinBox(centralwidget);
        spinBox_6->setObjectName("spinBox_6");
        spinBox_6->setGeometry(QRect(580, 210, 51, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(530, 220, 41, 21));
        label_6->setFont(font3);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(530, 170, 41, 31));
        label_7->setFont(font3);
        FourWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FourWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        FourWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FourWindow);
        statusbar->setObjectName("statusbar");
        FourWindow->setStatusBar(statusbar);

        retranslateUi(FourWindow);

        QMetaObject::connectSlotsByName(FourWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FourWindow)
    {
        FourWindow->setWindowTitle(QCoreApplication::translate("FourWindow", "MainWindow", nullptr));
        btu1->setText(QCoreApplication::translate("FourWindow", "\350\277\224\345\233\236", nullptr));
        btu2->setText(QCoreApplication::translate("FourWindow", "\347\224\237\346\210\220\350\277\267\345\256\253", nullptr));
        algorithmComboBox->setItemText(0, QCoreApplication::translate("FourWindow", "Graph_DFS", nullptr));
        algorithmComboBox->setItemText(1, QCoreApplication::translate("FourWindow", "BruteForce_DFS", nullptr));
        algorithmComboBox->setItemText(2, QCoreApplication::translate("FourWindow", "PRIM", nullptr));

        label->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\350\277\267\345\256\253\347\224\237\346\210\220\347\256\227\346\263\225\357\274\232</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\350\241\214\345\210\227\357\274\232</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\347\253\226\345\210\227\357\274\232</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\347\273\210\347\202\271X\357\274\232</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\347\273\210\347\202\271Y\357\274\232</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\350\265\267\347\202\271Y</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("FourWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\350\265\267\347\202\271X</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FourWindow: public Ui_FourWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOURWINDOW_H
