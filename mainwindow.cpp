#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int mainTime;
    int startOrStop=0;
    ui->setupUi(this);
        ui->comboBox->setStyleSheet(" height: 7em; line-height: 7em; font: 13pt 'Ubuntu';");
        ui->label->setStyleSheet("font: 13pt 'Ubuntu'");
        ui->label_2->setStyleSheet("font: 13pt 'Ubuntu'");
        ui->label_3->setStyleSheet("font: 13pt 'Ubuntu'");
        ui->label_6->setStyleSheet("font: 20pt 'Ubuntu'");
        ui->label_7->setStyleSheet("font: 20pt 'Ubuntu'");
        ui->label_8->setStyleSheet("font: 11pt");
        ui->label_9->setStyleSheet("font: 11pt");
        ui->label_10->setStyleSheet("font: 11pt");
        ui->tabWidget->setTabText(0,"Action");
        ui->tabWidget->setTabText(1,"Info");
        QPixmap myPixmap( ":/switch_off.png" );
        ui->label_5->setPixmap( myPixmap );
        refreshPr();
        QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(refreshPr()) );
        QObject::connect(this, SIGNAL(refresh()), this, SLOT(refreshPr()) );
        QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(startTim()) );
        tmr = new QTimer();
        tmr->setInterval(1000);
        connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
        QObject::connect(this, SIGNAL(startT()),tmr , SLOT(start()) );
        QObject::connect(this, SIGNAL(stopT()),tmr , SLOT(stop()) );
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTime()
{
    if(mainTime!=0){
        mainTime=mainTime-1;
        ui->progressBar->setValue(mainTime);

    }else{
        QString command="kill $(pgrep "+ui->comboBox->currentText()+")";
        system(qPrintable(command));
        emit stopT();
        emit refresh();
    }

}

void MainWindow::refreshPr()
{
    for (int i = ui->comboBox->count(); i >= 0; --i) //removes all but newly selected index, seems to be working fine
        {
            ui->comboBox->removeItem(i);
        }
    QFile::copy(":/getAllUsersProgram.sh", "/tmp/getAllUsersProgram.sh");
    system("cd /tmp && chmod +x getAllUsersProgram.sh && ./getAllUsersProgram.sh");
    QFile file("/tmp/listFinal.txt");
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
       {
           while(!file.atEnd())
           {
               QString str = file.readLine();
               ui->comboBox->addItem(str);

           }

    }
}

void MainWindow::startTim()
{
    if(startOrStop==0){
    int hour=(ui->spinBox->cleanText()).toInt();
    int min=(ui->spinBox_2->cleanText()).toInt();
    int sec=(ui->spinBox_3->cleanText()).toInt();
    int day=(ui->spinBox_4->cleanText()).toInt();
    hour=hour+day*24;
    min=min+hour*60;
    sec=sec+min*60;
    if(sec!=0){
    ui->progressBar->setMaximum(sec);
    mainTime=sec;
    ui->pushButton_2->setText("Stop");
    startOrStop=1;
    emit startT();
        }
    }else{
        emit stopT();
        startOrStop=0;
        ui->pushButton_2->setText("Start");
    }
}


