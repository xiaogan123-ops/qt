/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *But1;
    QLabel *label;
    QPushButton *btu2;
    QPushButton *btu3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        But1 = new QPushButton(Widget);
        But1->setObjectName("But1");
        But1->setGeometry(QRect(520, 420, 151, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft PhagsPa")});
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        But1->setFont(font);
        But1->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(510, 0, 261, 231));
        btu2 = new QPushButton(Widget);
        btu2->setObjectName("btu2");
        btu2->setGeometry(QRect(520, 340, 151, 71));
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
"    font: 20pt \"Microsoft PhagsPa\";\n"
"}"));
        btu3 = new QPushButton(Widget);
        btu3->setObjectName("btu3");
        btu3->setGeometry(QRect(520, 260, 151, 71));
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
"    font: 20pt \"Microsoft PhagsPa\";\n"
"}"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        But1->setText(QCoreApplication::translate("Widget", "\350\277\224\345\233\236\344\270\212\344\270\200\351\241\265", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:14pt; color:#5500ff;\">\346\214\211</span><span style=\" font-size:14pt; color:#ffff00;\">WASD\351\224\256</span><span style=\" font-size:14pt; color:#5500ff;\">\346\235\245\346\216\247\345\210\266\344\272\272\347\211\251</span></p><p><span style=\" font-size:14pt; color:#5500ff;\">\347\232\204\347\247\273\345\212\250</span></p><p><span style=\" font-size:14pt; color:#5500ff;\">\345\205\266\344\270\255</span><span style=\" font-size:14pt; color:#ffff00;\">\346\230\237\346\230\237</span><span style=\" font-size:14pt; color:#5500ff;\">\344\270\272\350\277\267\345\256\253\345\207\272\345\217\243</span></p><p><span style=\" font-size:14pt; color:#5500ff;\">\350\277\267\345\256\253\350\265\267\347\202\271\345\210\260\347\273\210\347\202\271\345\217\257\350\203\275</span></p><p><span style=\" font-size:14pt; color:#5500ff;\">\346\262\241\346\234\211\351\200\232\350\267\257\357\274\214\350\277\231\344\270\252\346\203\205\345\206\265</span></p><p><span style=\" font-size:"
                        "14pt; color:#5500ff;\">\345\217\257\344\273\245\346\214\211\344\270\213\351\235\242\347\232\204\350\277\267\345\256\253\346\227\240\350\247\243</span></p></body></html>", nullptr));
        btu2->setText(QCoreApplication::translate("Widget", "\350\207\252\345\212\250\345\257\273\350\267\257", nullptr));
        btu3->setText(QCoreApplication::translate("Widget", "\350\277\267\345\256\253\346\227\240\350\247\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
