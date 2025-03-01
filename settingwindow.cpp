#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QIcon>
#include <QDebug>
#include<QPointer>

// 初始化静态成员
QVector<QPointer<QAudioOutput>> settingWindow::globalOutputs;
settingWindow* settingWindow::m_instance = nullptr;
QWidget* settingWindow::s_mainWindow = nullptr;
bool settingWindow::isMuted = false;

settingWindow* settingWindow::instance(QWidget *parent) {
    if (!m_instance) {
        m_instance = new settingWindow(parent);
    }
    return m_instance;
}

settingWindow::settingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::settingWindow)
    , mMedia(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    setMinimumSize(850, 600);
     setFixedSize(850, 600);

    // 初始化音频
    mMedia->setAudioOutput(audioOutput);
    mMedia->setSource(QUrl("qrc:/res/ButtonSound.wav"));
    audioOutput->setVolume(50);
    registerAudioOutput(audioOutput);



    // 按钮初始状态与静音状态同步
    ui->btu2->setChecked(isMuted);
    updateSoundIcon();
     ui->btu2->setIconSize(QSize(48, 48)); // 调整图标尺寸

    // 连接信号槽
    connect(ui->btu2, &QPushButton::toggled, this, &settingWindow::toggleSound);
    connect(this, &settingWindow::globalMuteChanged, this, &settingWindow::updateSoundIcon);
    connect(ui->btu1, &QPushButton::clicked, this, &settingWindow::onBackButtonClicked);
    connect(ui->btu3, &QPushButton::clicked, this, &settingWindow::onAboutButtonClicked);

}

void settingWindow::registerAudioOutput(QAudioOutput *output) {
    if (output && !globalOutputs.contains(output)) {
        globalOutputs.append(output);
        output->setMuted(isMuted); // 应用当前静音状态
        connect(output, &QObject::destroyed, [output]() {
            globalOutputs.removeAll(output);
        });
    }
}

void settingWindow::updateSoundIcon() {
    QIcon icon(isMuted ? ":/res/sound_2.jpg" : ":/res/sound_1.jpg");
    ui->btu2->setIcon(icon);
}

void settingWindow::toggleSound(bool checked) {
    mMedia->play();
    isMuted = checked;
    setGlobalMute(isMuted);
}

void settingWindow::setGlobalMute(bool muted) {
    for (auto &output : globalOutputs) {
        if (!output.isNull()) {
            output->setMuted(muted);
        }
    }
    emit globalMuteChanged(muted);
    qDebug() << "全局静音：" << muted;
}




void settingWindow::onBackButtonClicked(){
    mMedia->play();
    qDebug() << "Back button clicked";
    this->hide();                      // 隐藏当前窗口
    if (s_mainWindow) {
        s_mainWindow->show(); // 直接显示主窗口
    } else {
        qDebug() << "Parent widget is null";
    }

}

void settingWindow::setMainWindow(QWidget* mainWindow) {
    s_mainWindow = mainWindow;
}
void settingWindow::onAboutButtonClicked(){
    mMedia->play();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("关于"));  // 窗口标题
    msgBox.setIcon(QMessageBox::Information);

    // 格式化输出信息（注意换行符的使用）
    QString info = QStringLiteral("%1\n\n%2\n\n%3")
                       .arg(tr("游戏作者：xiaogan       "))
                       .arg(tr("使用语言：C++ && Qt     "))
                       .arg(tr("制作时间：2025.2        "));

    msgBox.setText(info);
    msgBox.setStandardButtons(QMessageBox::Ok);  // 确认按钮
     msgBox.resize(600, 400);  // 宽度400，高度200
    msgBox.exec();


}
settingWindow::~settingWindow()
{
    delete ui;
}
// 绘制窗口背景

void settingWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    QImage background("://res/5.jpg");
    if (!background.isNull()) {
        painter.drawImage(QRect(0, 0, 850, 600), background);
    } else {
        qDebug() << "Failed to load background image.";
    }
}
void settingWindow::onMapSizeButtonClicked()
{
    mMedia->play();

    QMessageBox sizeDialog(this);
    sizeDialog.setWindowTitle(tr("地图大小设置"));
    sizeDialog.setText(tr("请选择地图显示模式："));

    QPushButton *fullscreenButton = sizeDialog.addButton(tr("全屏"), QMessageBox::AcceptRole);
    QPushButton *customSizeButton = sizeDialog.addButton(tr("任意大小"), QMessageBox::RejectRole);
    sizeDialog.addButton(QMessageBox::Cancel);

    sizeDialog.exec();

    if(sizeDialog.clickedButton() == fullscreenButton) {
        if(s_mainWindow) {
            // 临时允许窗口尺寸变化
            s_mainWindow->setMinimumSize(0, 0);
            s_mainWindow->showFullScreen();
            qDebug() << "已切换至全屏模式";
        }
    } else if(sizeDialog.clickedButton() == customSizeButton) {
        if(s_mainWindow) {
            // 恢复默认尺寸限制
            s_mainWindow->setMinimumSize(700, 500);
            s_mainWindow->resize(700, 500);
            s_mainWindow->showNormal();
            qDebug() << "已切换至自定义尺寸模式";
        }
    }
}
