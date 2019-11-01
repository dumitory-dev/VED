#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createnew.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    CreateNew NewDisk;
    NewDisk.setFixedSize(500,220);
    NewDisk.setModal(true);
    NewDisk.exec();
}
