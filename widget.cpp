#include"widget.h"
#include "ui_widget.h"
#include "maze.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include<QFileDialog>
#include<QSettings>
#include<QRandomGenerator>>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , mpmap(nullptr)
    , mrole(nullptr)
    , mtime(nullptr)
    , gameWon(false)
    , mazeRows(0)
    , mazeCols(0)
    , startX(0)
    , startY(0)
    , endX(0)
    , endY(0)
    ,propsx(0)
    ,propsy(0)
    ,mMedia(new QMediaPlayer(this))
    ,mMedia_2(new QMediaPlayer(this))
    ,mMedia_3(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
    ,audioOutput_2(new QAudioOutput(this))
    ,audioOutput_3(new QAudioOutput(this))
    ,showVictory(false)
    ,victoryScale(0.0)  // 胜利动画缩放比例
    , victorySoundPlayed(false) // 初始化标志
    ,failureScale(0.0)
    ,mMedia_4(new QMediaPlayer(this))    // 媒体播放器
    ,audioOutput_4(new QAudioOutput(this))// 音频输出
    ,settingwindow(settingWindow::instance(this))
    ,isPropCollected(false)
    , m_hasBanana(false)
    , m_isSpeedBoosted(false)
    , m_stepSize(1)
{
    ui->setupUi(this);

    setFixedSize(850, 600);

    // 添加胜利动画定时器
    victoryTimer = new QTimer(this);
    connect(victoryTimer, &QTimer::timeout, this, [this]() {
        if (victoryScale < 1.0) {
            victoryScale += 0.05;// 逐步增加缩放比例
            update();
        } else {
            victoryTimer->stop();
        }
    });

    // 添加失败动画定时器
    failureTimer_2 = new QTimer(this);
    connect(failureTimer_2, &QTimer::timeout, this, [this]() {
        if (failureScale < 1.0) {
            failureScale += 0.05;
            update();
        } else {
            failureTimer_2->stop();
        }
    });

    // 配置背景音乐
    mMedia->setAudioOutput(audioOutput); // 绑定音频输出
    mMedia->setSource(QUrl("qrc:/res/4.mp4")); // 使用资源路径
    audioOutput->setVolume(50); // 设置音量（0~100）
    settingwindow->registerAudioOutput(audioOutput);

    mMedia_2->setAudioOutput(audioOutput_2);
    mMedia_2->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput_2->setVolume(50);
    settingwindow->registerAudioOutput(audioOutput_2);

    mMedia_3->setAudioOutput(audioOutput_3);
    mMedia_3->setSource(QUrl("qrc:/res/victory_sound.mp3"));
    audioOutput_3->setVolume(50);
    settingwindow->registerAudioOutput(audioOutput_3);

    mMedia_4->setAudioOutput(audioOutput_4);
    mMedia_4->setSource(QUrl("qrc:/res/failure_sound.mp3"));
    audioOutput_4->setVolume(50);
    settingwindow->registerAudioOutput(audioOutput_4);

    connect(ui->But1, &QPushButton::clicked, this, &Widget::onBackButtonClicked);
    connect(ui->btu2, &QPushButton::clicked, this, &Widget::onAutoPathButtonClicked);
    connect(ui->btu3, &QPushButton::clicked, this, &Widget::onNoSolutionButtonClicked);

    //鼻涕怪
    monsterImageMap.insert({5, 0}, ":/res/Snorter.jpg");

    //大眼怪
    monsterImageMap.insert({6, 0}, ":/res/Big_Eyes_Monster.jpg");

    //胖怪兽
    monsterImageMap.insert({7, 0}, ":/res/Fat_Monster.jpg");

    //会喷火的龙宝宝
    monsterImageMap.insert({8, 0}, ":/res/dragon_baby.jpg");

    monsterImageMap.insert({9, 0}, ":/res/Hoppy_Monster1.jpg"); // 红色跳跳怪
    monsterImageMap.insert({9, 1}, ":/res/Hoppy_Monster2.jpg");// 蓝色跳跳怪

    // 第10关天使和恶魔
    monsterImageMap.insert({10,0}, ":/res/Angel.jpg");
    monsterImageMap.insert({10,1}, ":/res/Demon.jpg");

    //机器人
    monsterImageMap.insert({11,0}, ":/res/robot.jpg");
    monsterImageMap.insert({11,1}, ":/res/robot.jpg");

    //魔法师
    monsterImageMap.insert({12,0}, ":/res/enchanter.jpg");
    monsterImageMap.insert({12,1}, ":/res/enchanter.jpg");

    //大怪兽
    monsterImageMap.insert({13,0}, ":/res/Big_monster.jpg");
    monsterImageMap.insert({13,1}, ":/res/Big_monster.jpg");
    monsterImageMap.insert({13,2}, ":/res/Big_monster.jpg");

    //守卫
    monsterImageMap.insert({14,0}, ":/res/protector.jpg");
    monsterImageMap.insert({14,1}, ":/res/protector.jpg");
    monsterImageMap.insert({14,2}, ":/res/protector.jpg");

    //石头人
    monsterImageMap.insert({15,0}, ":/res/Malphite.jpg");
    monsterImageMap.insert({15,1}, ":/res/Malphite.jpg");
    monsterImageMap.insert({15,2}, ":/res/Malphite.jpg");

    //大魔王
    monsterImageMap.insert({16,0}, ":/res/big_devil.jpg");
    monsterImageMap.insert({16,1}, ":/res/big_devil.jpg");
    monsterImageMap.insert({16,2}, ":/res/big_devil.jpg");


    monsterTimer = new QTimer(this);
    connect(monsterTimer, &QTimer::timeout, this, &Widget::moveMonsters);

    initLevelDialogs();

    setFocusPolicy(Qt::StrongFocus);
    QTimer::singleShot(100, this, &Widget::setFocusToGame);

    // 初始化加速计时器
    m_speedBoostTimer = new QTimer(this);
    connect(m_speedBoostTimer, &QTimer::timeout, this, [this](){
        m_isSpeedBoosted = false;
        m_stepSize = 1;
        m_speedBoostTimer->stop();
    });
}
void Widget::setFocusToGame()
{
    this->setFocus();
    if(currentDialog){
        currentDialog->setFocusProxy(this);
    }
}
void Widget::setupMonstersForLevel(int level) {
    // 清空原有怪物
    qDeleteAll(m_monsters);
    m_monsters.clear();

    // 根据关卡配置怪物
    switch(level) {
    case 5: // 鼻涕怪直线巡逻
        m_monsters.append(new Monster());
        m_monsters[0]->setPatrolRoute({{8,14}, {12,14}});
        break;
    case 6:
        m_monsters.append(new Monster());
        m_monsters[0]->setPatrolRoute({{17,6}, {17,9}});
        break;
    case 7:
        m_monsters.append(new Monster());
        m_monsters[0]->setPatrolRoute({{8,8}, {10,8}});
        break;
    case 8:
        m_monsters.append(new Monster());
        m_monsters[0]->setPatrolRoute({{19,5}, {19,9}});
        break;
    case 9: { // 两个跳跳怪交叉巡逻
        // 红怪路线
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{9,1}, {12,1}});

        // 第二个跳跳怪（蓝色）
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{15,11}, {17,11}});
        break;
    }
    case 10: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{7,1}, {9,1}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{13,11}, {15,11}});
        break;
    }
    case 11: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{17,2}, {17,4}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{9,10}, {9,12}});
        break;
    }
    case 12: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{1,21}, {3,21}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{7,1}, {9,1}});
        break;
    }
    case 13: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{19,14}, {21,14}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{9,0}, {11,0}});
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{0,9}, {0,11}});
        break;
    }
    case 14: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{23,18}, {23,20}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{27,8}, {27,10}});
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{18,5}, {20,5}});
        break;
    }
    case 15: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{0,22}, {0,24}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{1,1}, {3,1}});
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{30,8}, {30,10}});
        break;
    }
    case 16: {

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{24,2}, {26,2}});

        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{17,0}, {19,0}});
        m_monsters.append(new Monster());
        m_monsters.last()->setPatrolRoute({{20,15}, {20,17}});
        break;
    }
    }
}
Widget::~Widget()
{

    // 清理旧资源
    if (mtime) {
        mtime->stop();
        delete mtime;
    }
    delete mpmap;
    delete mrole;
    delete ui;
    if(currentDialog) {
        currentDialog->deleteLater();
    }

    if (monsterTimer) {
        monsterTimer->stop();
        delete monsterTimer;
    }
}

//设置迷宫参数
void Widget::setMazeParameters(int rows, int cols, int startX, int startY, int endX, int endY) {
    this->mazeRows = rows;
    this->mazeCols = cols;
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
    mMedia->play();   // 播放背景音乐
    resetGame();  // 先重置游戏

    if (!mpmap) return; // 确保 mpmap 初始化成功


}


// 重置游戏状态
void Widget::resetGame()
{


    qDebug() << "正在重置游戏...";

    // 先停止定时器
    if (mtime) {
        mtime->stop();
        delete mtime;
        mtime = nullptr;
    }

    // 清理旧数据
    if (mpmap) {
        delete mpmap;
        mpmap = nullptr;
    }

    if (mrole) {
        qDebug() << "清理角色数据，最后位置:" << mrole->row() << "," << mrole->col();
        delete mrole;
        mrole = nullptr;
    }

    // 初始化游戏状态变量
    victorySoundPlayed = false; // 重置音效播放标志
    gameWon = false;
    showVictory = false;
    victoryScale = 0.0;
    victoryTimer->stop();

    solutionPath.clear();
    showingPath = false;

    // 创建新迷宫对象并加载文件
    Maze* maze=new(Maze);
    QString filePath = QFileDialog::getOpenFileName(this, "选择迷宫文件", "", "Text Files (*.txt);;All Files (*)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "错误", "未选择迷宫文件！");
        return;
    }

    if(maze->loadFromFile(filePath)){
        qDebug() << "迷宫成功加载";
    } else {
        QMessageBox::warning(this, "错误", "迷宫加载失败！");
        return;
    }

    mazeRows = maze->getmaze().size();
    mazeCols = (mazeRows > 0) ? maze->getmaze()[0].size() : 0;

    // 设置起始点和角色位置
    QPair<int, int> startPos = maze->findStartPosition();
    startX = startPos.first;
    startY = startPos.second;
    mrole = new Role(this);
    mrole->setPosition(startX, startY);  // 让角色在起点



    QPair<int, int> endPos = maze->findEndPosition();
    endX = endPos.first;
    endY = endPos.second;
    // 初始化地图和角色
    mpmap = new Gameman(this);
    mpmap->InitByData(maze->getmaze());

    // 检查终点是否有效
    if (endX == -1 || endY == -1) {
        QMessageBox::warning(this, "错误", "未找到迷宫终点！");
        return;
    }


    // 创建新计时器
    if (!mtime) {
        mtime = new QTimer(this);
    }
    gameWon = false;
    update();
    delete maze;


}

void Widget::onBackButtonClicked()
{

    isPropCollected = false;
    m_hasBanana = false;

    mMedia_2->play(); // 播放按钮音效

    if (mMedia) {
        mMedia->stop();  // 停止播放
    }


    // 重置失败相关状态
    failureScale = 0.0;           // 重置动画缩放比例
    failure_soundPlayed_2 = false; // 重置声音播放标志
    failureTimer_2->stop();        // 停止失败动画定时器




    this->hide();
    if (parentWidget()) {
        parentWidget()->show(); // 返回上一个窗口
    }

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景图片
    QImage background("://res/background.jpg");
    if (!background.isNull()) {
        painter.drawImage(QRect(0, 0, 850, 600), background);
    } else {
        qDebug() << "Failed to load background image.";
    }
    // 绘制地图
    if (mpmap) {
        mpmap->paint(&painter, QPoint(0, 0));
    }


    if(currentLevel == 3 && !isPropCollected){
        int cellWidth = 600 / mazeCols;
        int cellHeight = 600 / mazeRows;
        painter.drawImage(QRect(
                              1 * cellWidth,
                              13 * cellHeight,
                              cellWidth,
                              cellHeight),
                          QImage(":/res/props.jpg"));
    }


    if(currentLevel == 6 && m_hasBanana){
        int cellWidth = 600 / mazeCols;
        int cellHeight = 600 / mazeRows;
        painter.drawImage(QRect(
                              m_bananaPos.y() * cellWidth,
                              m_bananaPos.x() * cellHeight,
                              cellWidth,
                              cellHeight),
                          QImage(":/res/banana.jpg"));
    }
    // 角色绘制
    if (mrole) {
        int cellWidth = 600 / mazeCols;
        int cellHeight = 600 / mazeRows;
        mrole->Paint(&painter, QPoint(0, 0), cellWidth, cellHeight);
    }



    // 检查胜利状态
    if (mrole && mrole->row() == endX && mrole->col() == endY) {
        qDebug() << "到达终点! 角色位置("
                 << mrole->row() << "," << mrole->col()
                 << ") 终点位置(" << endX << "," << endY << ")";
        if (!gameWon) { // 添加未胜利状态检查
            levelComplete();
            gameWon = true;
            showVictory = true;
            victoryScale = 0.0;
            if (mtime) mtime->stop();
            victoryTimer->start(50);

            if (!victorySoundPlayed) {
                mMedia_3->play();
                victorySoundPlayed = true;
            }

            if (mMedia) {
                mMedia->stop();
            }
        }
    }

    // 绘制胜利标志
    if (showVictory) {



        QPixmap victoryPixmap("://res/2.jpg");
        if (!victoryPixmap.isNull()) {
            int baseWidth = 200;  // 适当放大基础尺寸
            int baseHeight = 200;

            qDebug() << "Drawing victory image at scale:" << victoryScale;

            int scaledWidth = baseWidth * victoryScale;
            int scaledHeight = baseHeight * victoryScale;

            QRect targetRect(
                (width() - scaledWidth) / 2,
                (height() - scaledHeight) / 2 - 50,
                scaledWidth,
                scaledHeight
                );


            painter.save();  // 保存当前绘制状态
            painter.setOpacity(victoryScale);
            painter.drawPixmap(targetRect, victoryPixmap);
            painter.restore();  // 恢复绘制状态
        } else {
            qDebug() << "Failed to load victory image!";
        }
    }


    for(int i=0; i<m_monsters.size(); ++i){
        Monster* monster = m_monsters[i];
        QString imgPath = monsterImageMap.value({currentLevel, i}, "");

        if(!imgPath.isEmpty()){
            QImage monsterImg(imgPath);
            int cellW = 600/mazeCols, cellH = 600/mazeRows;
            painter.drawImage(QRect(
                                  monster->col()*cellW,
                                  monster->row()*cellH,
                                  cellW, cellH), monsterImg);
        }
    }

    if (failureTimer_2->isActive() || failureScale > 0) {
        QPixmap failurePixmap("://res/3.jpg");
        if (!failurePixmap.isNull()) {
            int baseWidth = 200;
            int baseHeight = 200;
            int scaledWidth = baseWidth * failureScale;
            int scaledHeight = baseHeight * failureScale;
            QRect targetRect(
                (width() - scaledWidth) / 2,
                (height() - scaledHeight) / 2 - 50,
                scaledWidth,
                scaledHeight
                );
            painter.save();
            painter.setOpacity(failureScale);
            painter.drawPixmap(targetRect, failurePixmap);
            painter.restore();
        }
    }


    // 绘制路径（排除角色当前位置）
    if (showingPath && !solutionPath.isEmpty()) {

        int cellWidth = 600 / mazeCols;
        int cellHeight = 600 / mazeRows;

        QPoint rolePos(mrole->row(), mrole->col()); // 获取当前角色位置

        foreach (QPoint p, solutionPath) {
            // 跳过角色当前位置和终点
            if (p == rolePos || p == QPoint(endX, endY)) continue;

            painter.drawImage(QRect(
                                  p.y() * cellWidth,
                                  p.x() * cellHeight,
                                  cellWidth,
                                  cellHeight
                                  ), QImage("://res/destination.jpg")); // 使用专用路径标记图片
        }
    }




}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (!mrole || gameWon || isDialogActive) return; // 新增isDialogActive检查


    int dRow = 0, dCol = 0;
    switch(event->key()) {
    // 方向键控制
    case Qt::Key_Up:    dRow = -1; break;
    case Qt::Key_Down:  dRow = 1;  break;
    case Qt::Key_Left:  dCol = -1; break;
    case Qt::Key_Right: dCol = 1;  break;
    // WASD 控制
    case Qt::Key_W:     dRow = -1; break; // W 上
    case Qt::Key_S:     dRow = 1;  break; // S 下
    case Qt::Key_A:     dCol = -1; break; // A 左
    case Qt::Key_D:     dCol = 1;  break; // D 右
    default: QWidget::keyPressEvent(event); return;
    }


    // 检查是否吃到香蕉皮
    if(currentLevel == 6 && m_hasBanana &&
        mrole->row() == m_bananaPos.x() &&
        mrole->col() == m_bananaPos.y())
    {

        m_hasBanana = false;
        m_isSpeedBoosted = true;
        m_stepSize = 2; // 加速时每次移动2格
        m_speedBoostTimer->start(5000); // 加速持续5秒
    }


    if(currentLevel!=6){
        int newRow = mrole->row() + dRow;
        int newCol = mrole->col() + dCol;
        if (mpmap->isValid(newRow, newCol) && mpmap->isRoad(newRow, newCol)) {
            mrole->setPosition(newRow, newCol); // 直接设置新位置
            if (showingPath) {
                solutionPath.clear();
                showingPath = false;
            }
            update();
        }
    }else {
        for(int i=0; i<m_stepSize; i++){
            int newRow = mrole->row() + dRow;
            int newCol = mrole->col() + dCol;

            if(mpmap->isValid(newRow, newCol) && mpmap->isRoad(newRow, newCol)){
                mrole->setPosition(newRow, newCol);
                checkMonsterCollisions();
                if (showingPath) {
                    solutionPath.clear();
                    showingPath = false;
                }
            } else {
                break; // 如果遇到墙或者边界，停止后续移动
            }

        }
        qDebug()<<"abc";
        update();
    }

    if (currentLevel == 3 && !isPropCollected &&
        mrole->row() == 13 && mrole->col() == 1)
    {
        isPropCollected = true;
        qDebug()<<"abc";
        onAutoPathButtonClicked();
        return;
    }

}

void Widget::checkMonsterCollisions()
{
    foreach (Monster* monster, m_monsters) {
        if(monster->row() == mrole->row() &&
            monster->col() == mrole->col())
        {
            handleGameFailure();
            return;
        }
    }
}
// 角色移动逻辑
void Widget::moveRole(int dRow, int dCol)
{
    if (!mrole || gameWon) return;

    // 计算新位置
    QMutexLocker locker(&moveMutex);
    int newRow = mrole->row() + dRow;
    int newCol = mrole->col() + dCol;


    // 边界检查和碰撞检测
    if (newRow < 0 || newRow >= mazeRows || newCol < 0 || newCol >= mazeCols) return;
    if (mpmap->isWall(newRow, newCol)) return;

    mrole->Move(dRow, dCol);
    if (showingPath) {
        solutionPath.clear();
        showingPath = false;
    }
    update(); // 触发重绘以检测胜利条件

    if (newRow == endX && newCol == endY) {
        mrole->setPosition(newRow, newCol);  // 强制到达终点
        levelComplete(); // 触发胜利逻辑
        return;
    }


}

void Widget::closeEvent(QCloseEvent* event) {
    // 停止所有音乐播放
    if (mMedia) mMedia->stop();
    if (mMedia_2) mMedia_2->stop();
    if (mMedia_3) mMedia_3->stop();
    if (mMedia_4) mMedia_4->stop();



    // 释放定时器
    if (victoryTimer) {
        victoryTimer->stop();
        delete victoryTimer;
    }
    if (failureTimer_2) {
        failureTimer_2->stop();
        delete failureTimer_2;
    }
    if (mtime) {
        mtime->stop();
        delete mtime;
    }
    if (monsterTimer) {
        monsterTimer->stop();
        delete monsterTimer;
    }

    // 调用基类的关闭事件
    QWidget::closeEvent(event);
}

void Widget::onAutoPathButtonClicked() {
    solutionPath.clear();
    showingPath = false;
    mMedia_2->play();
    if (findPathDFS(solutionPath)) { // 使用DFS算法找路径
        showingPath = true;
        update(); // 触发重绘
        qDebug()<<"aaa";
    } else {
        QMessageBox::warning(this, "提示", "当前迷宫无解！");
    }
}

void Widget::onNoSolutionButtonClicked() {
    mMedia_2->play();
    QList<QPoint> dummyPath;
    if (!findPathDFS(dummyPath)) {
        failureScale = 0.0;
        failure_soundPlayed_2 = false; // 重置标志以允许再次播放
        if (mtime) mtime->stop();
        failureTimer_2->start(50);

        if (!failure_soundPlayed_2) {
            mMedia_4->play();
            failure_soundPlayed_2 = true;
        }
        if (mMedia) mMedia->stop();
        update();
    } else {
        QMessageBox::information(this, "提示", "存在可行路径");
    }
}

//关卡
void Widget::setMaze(int level, int rows, int cols, int startX, int startY, int endX, int endY) {
    currentLevel = level; // 关键！设置当前关卡
    this->mazeRows = rows;
    this->mazeCols = cols;
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;

    resetGame1(level);  // 传递关卡号

    if(level==1){
        qDebug() << "1...";
    }
    if(level==2){
        qDebug() << "2...";
    }
    if (!mpmap) return;

    if(level == 6){
        m_bananaPos = QPoint(1, 12); // 设置香蕉皮位置（根据实际迷宫调整）
        m_hasBanana = true;
    }else{
        m_hasBanana = false;
    }


}
void Widget::resetGame1(int level) {
    // 清理旧资源
    delete mpmap;
    mpmap = nullptr;
    delete mrole;
    mrole = nullptr;
    mMedia->play();

    victorySoundPlayed = false; // 重置音效播放标志
    gameWon = false;
    showVictory = false;
    victoryScale = 0.0;
    victoryTimer->stop();

    isDialogActive = false;
    gameWon = false;

    isPropCollected = false;  // 新增：重置第三关道具状态
    m_hasBanana = false;      // 新增：重置第六关香蕉状态

    setupMonstersForLevel(level); // 初始化怪物
    monsterTimer->start(800); // 启动怪物定时器

    if(level == 6){
        m_hasBanana = true;
        m_bananaPos = QPoint(1, 12); // 根据实际迷宫调整坐标
        m_isSpeedBoosted = false;
        m_stepSize = 1;
    }else{
        m_hasBanana = false;
    }


    // 动态生成文件名
    QString fileName = QString("新建文件夹/taxt%1.txt").arg(level);
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(appDir).filePath(fileName);

    solutionPath.clear();
    showingPath = false;


    Maze* maze = new Maze;
    if (!maze->loadFromFile(filePath)) {
        QMessageBox::warning(this, "错误", QString("迷宫%1加载失败！").arg(level));
        delete maze;
        return;
    }

    // 初始化角色和地图
    mazeRows = maze->getmaze().size();
    mazeCols = (mazeRows > 0) ? maze->getmaze()[0].size() : 0;

    QPair<int, int> startPos = maze->findStartPosition();
    startX = startPos.first;
    startY = startPos.second;
    mrole = new Role(this);
    mrole->setPosition(startX, startY);

    QPair<int, int> endPos = maze->findEndPosition();
    endX = endPos.first;
    endY = endPos.second;

    mpmap = new Gameman(this);
    mpmap->InitByData(maze->getmaze());





    if(levelDialogs.contains(currentLevel)){
        showLevelDialog(levelDialogs[currentLevel]);
    }



    if (endX == -1 || endY == -1) {
        QMessageBox::warning(this, "错误", "未找到迷宫终点！");
        return;
    }

    if (!mtime) {
        mtime = new QTimer(this);
    }
    gameWon = false;
    update();
    delete maze;
}

//寻路
bool Widget::findPathDFS(QList<QPoint>& path) {
    if (!mpmap || !mrole) return false;


    // 使用栈实现的DFS算法
    QStack<QPoint> stack;
    QVector<QVector<bool>> visited(mazeRows, QVector<bool>(mazeCols, false));

    QPoint start(mrole->row(), mrole->col());
    QPoint end(endX, endY);

    stack.push(start);
    visited[start.x()][start.y()] = true;

    // 用于记录路径的父节点
    QHash<QPoint, QPoint> parent;

    while (!stack.isEmpty()) {
        QPoint current = stack.pop();

        // 找到终点
        if (current == end) {
            // 回溯路径
            QPoint p = end;
            while (p != start) {
                path.prepend(p);
                p = parent[p];
            }
            path.prepend(start);
            return true;
        }

        // 四个方向：右，上，左，下
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; ++i) {
            int newRow = current.x() + dx[i];
            int newCol = current.y() + dy[i];

            if (newRow >= 0 && newRow < mazeRows &&
                newCol >= 0 && newCol < mazeCols &&
                !mpmap->isWall(newRow, newCol) &&
                !visited[newRow][newCol]) {

                visited[newRow][newCol] = true;
                parent[QPoint(newRow, newCol)] = current;
                stack.push(QPoint(newRow, newCol));
            }
        }
    }
    return false;
}

void Widget::levelComplete() {
    int nextLevel = currentLevel + 1;
    if(currentLevel==1){
        nextLevel = currentLevel + 1;
    }
    if (nextLevel <= 17) {
        emit levelUnlocked(nextLevel); // 直接发射信号，由SecondWindow处理
    }
}




void Widget::handleGameFailure()
{
    // 停止游戏计时器和怪物移动
    if (mtime) mtime->stop();
    monsterTimer->stop();

    // 触发失败动画
    failureScale = 0.0;
    failure_soundPlayed_2 = false;
    failureTimer_2->start(50);

    // 播放失败音效
    if (!failure_soundPlayed_2) {
        mMedia_4->play();
        failure_soundPlayed_2 = true;
    }

    // 停止背景音乐
    if (mMedia) {
        mMedia->stop();
    }

    update();
}
void Widget::showLevelDialog(const QStringList &messages)
{
    // 确保旧对话框已清理
    if(currentDialog) {
        currentDialog->deleteLater();
        currentDialog = nullptr;
    }


    if (monsterTimer && monsterTimer->isActive()) {
        monsterTimer->stop();
    }

    // 设置对话框激活状态
    isDialogActive = true;

    currentDialog = new CustomDialog(messages, this);
    if (monsterTimer && monsterTimer->isActive()) {
        monsterTimer->stop();
    }
    if (mtime && mtime->isActive()) {
        mtime->stop();
    }

    // 设置对话框位置（底部1/3区域）
    currentDialog->setGeometry(
        width()*0.1,
        height()*2/3,
        width()*0.8,
        height()/3 - 20
        );

    connect(currentDialog, &CustomDialog::dialogFinished, this, [=](){
        isDialogActive = false;
        // 新增强制焦点设置
        this->setFocus();
        QApplication::processEvents(); // 处理挂起的事件

        // 新增延迟状态检查
        QTimer::singleShot(50, this, [this](){
            qDebug() << "对话框关闭后焦点状态:" << this->hasFocus();
            if(mrole && mrole->row() == endX && mrole->col() == endY) {
                qDebug() << "触发延迟胜利检测";
                levelComplete();
            }
        });
        // 强制更新游戏状态
        QTimer::singleShot(0, this, [this](){
            if(mrole && mrole->row() == endX && mrole->col() == endY) {
                levelComplete();
            }
        });

        if(mtime) mtime->start(1000);
        if (monsterTimer) monsterTimer->start(800);
        currentDialog->deleteLater();
        currentDialog = nullptr;
        this->setFocus();
    });

    // 暂停游戏计时
    if(mtime) mtime->stop();
    currentDialog->show();
    currentDialog->setFocus();
}
void Widget::initLevelDialogs()
{
    levelDialogs[1] = {
        "哈喽~ 第一关到啦！",
        "看到终点小星星了吗？",
        "摇摇晃晃走过去就行啦！"
    };

    levelDialogs[2] = {
        "哇哦~ 第二关耶！",
        "这次路有点弯弯绕绕",
        "但也不难，加油，走叭~"
    };

    levelDialogs[3] = {
        "第三关！第三关！",
        "迷宫开始打圈圈啦",
        "记得吃路上的小蛋糕然后就知道终点啦！"
    };

    levelDialogs[4] = {
        "终极简单关！",
        "走直线都能到终点",
        "闭着眼睛都能过~ 嘻嘻！"
    };

    levelDialogs[5] = {
        "注意！注意！",
        "有个鼻涕怪在溜达",
        "趁它打瞌睡时溜过去！"
    };

    levelDialogs[6] = {
        "第六关有惊喜！",
        "大眼怪会追着你跑",
        "快用香蕉皮滑行逃跑！"
    };

    levelDialogs[7] = {
        "第七关迷宫转圈圈",
        "打呼噜的胖怪兽",
        "悄悄从它背后绕过去~"
    };

    levelDialogs[8] = {
        "哇！会喷火的龙宝宝",
        "等它打喷嚏时冲刺",
        "记得走Z字型路线！"
    };

    levelDialogs[9] = {
        "两只跳跳怪出现！",
        "一个红一个蓝",
        "它们会互相撞晕哦~"
    };

    levelDialogs[10] = {
        "第十关！双倍危险",
        "白天使和黑恶魔",
        "让它们自己打架去！"
    };

    levelDialogs[11] = {
        "迷宫开始转圈圈啦",
        "两个巡逻机器人",
        "躲进墙角等他们过去"
    };

    levelDialogs[12] = {
        "最终双怪关卡！",
        "可怕的魔法师",
        "称他们不注意走"
    };

    levelDialogs[13] = {
        "三只！三只大怪兽！",
        "迷宫像大漩涡",
        "贴着墙边慢慢挪~"
    };

    levelDialogs[14] = {
        "第十四关超级难！",
        "三个会飞的守卫",
        "趁他们转头时冲刺！"
    };

    levelDialogs[15] = {
        "终极关卡前奏！",
        "迷宫会自己转动",
        "三个石头人追你",
        "快找到星星吧！"
    };

    levelDialogs[16] = {
        "最终决战！",
        "三个大魔王把守",
        "冲鸭！终点在发光！"
    };
}
void Widget::moveMonsters() {
    foreach (Monster* monster, m_monsters) {
        monster->move();

        // 碰撞检测
        if(monster->row() == mrole->row() &&
            monster->col() == mrole->col())
        {
            handleGameFailure();
            return;
        }
    }
    update();
}
