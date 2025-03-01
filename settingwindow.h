#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPointer>

namespace Ui {
class settingWindow;
}

class settingWindow : public QMainWindow
{
    Q_OBJECT

public:

    // 单例访问接口，传递父对象参数
    static settingWindow* instance(QWidget *parent = nullptr);
    ~settingWindow();

    void paintEvent(QPaintEvent *event);

    // 全局音频控制接口
    static void registerAudioOutput(QAudioOutput *output);
   void setGlobalMute(bool muted);
    void updateSoundIcon();

    static void setMainWindow(QWidget* mainWindow); // 新增

signals:
     void globalMuteChanged(bool muted);

private slots:
    void onBackButtonClicked();
    void toggleSound(bool checked);
    void onAboutButtonClicked();
    void onMapSizeButtonClicked();

private:
    // 构造函数设为私有
    explicit settingWindow(QWidget *parent = nullptr);
    Ui::settingWindow *ui;

    QMediaPlayer *mMedia;
    QAudioOutput *audioOutput;

     static QWidget* s_mainWindow; // 静态成员保存主窗口

    static QVector<QPointer<QAudioOutput>> globalOutputs;
    static settingWindow* m_instance;
    static bool isMuted; // 改为静态成员变量
};

#endif // SETTINGWINDOW_H
