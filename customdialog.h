// CustomDialog.h
#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomDialog(const QStringList &messages, QWidget *parent = nullptr);

signals:
    void dialogFinished();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void showNextMessage();

    QLabel *messageLabel;
    QStringList messages;
    int currentIndex;
};

#endif // CUSTOMDIALOG_H
