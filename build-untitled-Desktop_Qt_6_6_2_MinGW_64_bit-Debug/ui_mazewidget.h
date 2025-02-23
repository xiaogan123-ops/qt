/********************************************************************************
** Form generated from reading UI file 'mazewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEWIDGET_H
#define UI_MAZEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MazeWidget
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MazeWidget)
    {
        if (MazeWidget->objectName().isEmpty())
            MazeWidget->setObjectName("MazeWidget");
        MazeWidget->resize(800, 600);
        centralwidget = new QWidget(MazeWidget);
        centralwidget->setObjectName("centralwidget");
        MazeWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MazeWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MazeWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(MazeWidget);
        statusbar->setObjectName("statusbar");
        MazeWidget->setStatusBar(statusbar);

        retranslateUi(MazeWidget);

        QMetaObject::connectSlotsByName(MazeWidget);
    } // setupUi

    void retranslateUi(QMainWindow *MazeWidget)
    {
        MazeWidget->setWindowTitle(QCoreApplication::translate("MazeWidget", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MazeWidget: public Ui_MazeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEWIDGET_H
