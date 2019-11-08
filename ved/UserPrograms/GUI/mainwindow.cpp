#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createnew.h"
#include <QStandardItemModel>
#include <QStandardItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *smodel = new QStandardItemModel;
    QStandardItem *Item = new QStandardItem();
    QStandardItem *Item2 = new QStandardItem();
    int ID = 0;
    int test = 228;
     Item->setData (ID = test,Qt::DisplayRole);
     Item2->setData("Josh", Qt::DisplayRole);


   smodel->setHorizontalHeaderItem(0,new QStandardItem("File path"));
    smodel->setHorizontalHeaderItem(1,new QStandardItem("File size"));
    smodel->setHorizontalHeaderItem(2,new QStandardItem("Letter Disk"));
    smodel->setItem(0,1,Item);
    smodel->setItem(0,0,Item2);
    this->ui->tableView->setModel(smodel);


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
