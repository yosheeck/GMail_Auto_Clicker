/*
 * Copyright by yosh from Ke.mu Studio 2013
 * Contact y@ke.mu for questions
 */
#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include <QMainWindow>
#include <QTime>

namespace Ui {
class KMainWindow;
}

class KMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit KMainWindow(QWidget *parent = 0);
    ~KMainWindow();
    
public Q_SLOTS:
    void onFrameLoadFinished(bool ok);
    void onTimer1s();

private:
    bool checkForMailButton();
    bool tryClickingMailCheck();
    void uiUpdate();

    void log(QString msg);

    /* some ui->logic */
    bool isMailButton;
    bool isMailButtonClickingOn;
    qint64 timeOfLastMailCheck;

    Ui::KMainWindow *ui;
};

#endif // KMAINWINDOW_H
