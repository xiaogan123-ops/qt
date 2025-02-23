#include <QApplication>
#include "MazeWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MazeWidget widget;
    // 设置窗口大小（根据行列数和单元大小）
    widget.resize(20 * 20, 20 * 20);
    widget.show();

    return app.exec();
}
