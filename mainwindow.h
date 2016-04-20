#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int mainTime;
    int startOrStop;
private:
    Ui::MainWindow *ui;
    QTimer *tmr;
signals:
    void startT();
    void stopT();
public slots:
    void updateTime();
    void refreshPr();
    void startTim();
};

#endif // MAINWINDOW_H
