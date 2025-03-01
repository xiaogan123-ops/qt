// CustomDialog.cpp
#include "CustomDialog.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>

CustomDialog::CustomDialog(const QStringList &messages, QWidget *parent)
    : QDialog(parent), messages(messages), currentIndex(0)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    messageLabel = new QLabel(this);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setWordWrap(true);
    messageLabel->setStyleSheet("QLabel {"
                                "color: #333333;"
                                "font-size: 16px;"
                                "padding: 20px;"
                                "}");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->setContentsMargins(10, 10, 10, 10);

    // 直接显示第一条消息
    showNextMessage();
}

void CustomDialog::showNextMessage()
{
    if(currentIndex >= messages.size()) {
        emit dialogFinished();
        deleteLater();
        return;
    }

    messageLabel->setText(messages[currentIndex]);
    currentIndex++;
}

void CustomDialog::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    showNextMessage();
}

void CustomDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制半透明白色背景
    painter.setBrush(QColor(255, 255, 255, 220));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 10, 10);
}
