#include "fourwindow.h"
#include "ui_fourwindow.h"
#include<qpainter.h>
#include<qdebug.h>
#include<QMessageBox>
#include<QDir>
#include <QStandardPaths>

FourWindow::FourWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FourWindow)
    ,mpmap(nullptr)
    , mazeRows(13)
    , mazeCols(13)
    ,endX(9)
    ,endY(9)
    ,startx(1)
    ,starty(1)
    ,mMedia(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
    ,settingwindow(settingWindow::instance(this))

{

    ui->setupUi(this);

     setFixedSize(700, 500);

    connect(ui->btu1,&QPushButton::clicked,this,&FourWindow::onBackButtonClicked);
    ui->spinBox->setRange(11, 50); // 设置迷宫行数的范围
    ui->spinBox_2->setRange(11, 50); // 设置迷宫列数的范围
    ui->spinBox->setValue(mazeRows); // 设置初始行数为13
    ui->spinBox_2->setValue(mazeCols); // 设置初始列数为13
    ui->spinBox_3->setRange(1,88);
    ui->spinBox_3->setValue(endX);
    ui->spinBox_4->setRange(1,88);
    ui->spinBox_4->setValue(endY);
    ui->spinBox_5->setRange(1,88);
    ui->spinBox_5->setValue(startx);
    ui->spinBox_6->setRange(1,88);
    ui->spinBox_6->setValue(starty);



    drawMaze();
    // 连接 QSpinBox 信号到槽函数
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged);
    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged_2);

    connect(ui->spinBox_3, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged_3);
    connect(ui->spinBox_4, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged_4);
    connect(ui->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged_5);
    connect(ui->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &FourWindow::onSpinBoxValueChanged_6);

    connect(ui->btu2,&QPushButton::clicked,this,&FourWindow::onGenerateMazeClicked);


    mMedia->setAudioOutput(audioOutput);
    mMedia->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput->setVolume(50);

    settingwindow->registerAudioOutput(audioOutput);


}

FourWindow::~FourWindow()
{
    delete ui;
}


void FourWindow::onSpinBoxValueChanged(int value){
    mazeRows=value;
    qDebug()<<mazeRows;
    drawMaze();
}
void FourWindow::onSpinBoxValueChanged_2(int value){
    mazeCols=value;
    drawMaze();
}
//终点x
void FourWindow::onSpinBoxValueChanged_3(int value){
    endX=value;
}
//终点y
void FourWindow::onSpinBoxValueChanged_4(int value){
    endY=value;
}

void FourWindow::onBackButtonClicked(){
    qDebug() << "Back button clicked";
    this->hide();                      // 隐藏当前窗口
    if (parentWidget()) {
        parentWidget()->show();        // 显示父窗口（MainWindow）
    } else {
        qDebug() << "Parent widget is null";
    }
    mMedia->play();
} // 处理返回上一个界面的按钮点击事件
void FourWindow::onGenerateMazeClicked(){
    mMedia->play();
    drawMaze1();

}

//初始画地图
void FourWindow::drawMaze() {
    if (mpmap) delete mpmap; // 释放旧对象

    Maze *maze = new Maze(mazeRows, mazeCols, this); // 迷宫大小修正
    mpmap = new Gameman(this);
    mpmap->InitByData(maze->getmaze());

    update(); // 触发 paintEvent 进行绘制
}


//生成地图
void FourWindow::drawMaze1() {
    if (mpmap) {
        delete mpmap;
        mpmap = nullptr;
    }


    QString selectedAlgorithm = ui->algorithmComboBox->currentText();
    Maze::Algorithm algorithmType_2=Maze::Graph_DFS;

    if (selectedAlgorithm == "Graph_DFS") {
        algorithmType_2 =  Maze::Graph_DFS;
    } else if (selectedAlgorithm == "PRIM") {
        algorithmType_2 =  Maze::PRIM;
    } else if (selectedAlgorithm == "Kruskal") {
        algorithmType_2 =  Maze::Kruskal;
    }

    // 创建新的迷宫
    Maze *maze = new Maze(mazeRows, mazeCols, startx, starty, endX, endY, algorithmType_2, this);
    mpmap = new Gameman(this);

    // 初始数据载入
    mpmap->InitByData(maze->getmaze());

    // 生成迷宫并实时更新数据
    if(algorithmType_2 == Maze::Graph_DFS){
        maze->generateMazeDFSVisual(this);
    }else if(algorithmType_2 == Maze::PRIM){
        maze->generateMazeprimVisual(this);
    }else if(algorithmType_2 == Maze::Kruskal){
        maze->generateMazeKruskalVisual(this);
    }

    // 确保终点正确设置
    mpmap->InitByData(maze->getmaze());
    update();



    // 保存文件处理
    QString saveDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << "保存路径: " << saveDirectory;  // 打印保存路径

    QDir dir(saveDirectory);
    if (!dir.exists()) {
        qDebug() << "目录不存在，正在创建目录...";
        dir.mkpath(".");  // 创建目录
    }
    QString filePath = QDir::currentPath() + "/maze.txt";  // 使用当前工作目录

    qDebug() << "文件路径: " << filePath;  // 打印文件路径

    if (!maze->saveToFile(filePath)) {
        qDebug() << "保存失败";
        QMessageBox::warning(this, "错误", "保存迷宫文件失败");
        return;
    }
}

//重新定义迷宫数据
void FourWindow::updateMazeData(const QVector<QVector<int>>& data) {
    if (mpmap) {
        mpmap->InitByData(data);
    }
}

void FourWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // 绘制背景
    QImage background("://res/background.jpg");
    if (!background.isNull()) {
        painter.drawImage(QRect(0, 0, 700, 500), background);
    } else {
        qDebug() << "Failed to load background image.";
    }

    // 绘制迷宫
    if (mpmap) {
        mpmap->paint(&painter, QPoint(0, 0));
    }
}

//起点x
void FourWindow::onSpinBoxValueChanged_5(int value){
    startx=value;
}
//起点y
void FourWindow::onSpinBoxValueChanged_6(int value){
    starty=value;
}
