#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createnew.h"
#include "copy.h"
#include "mount.h"
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
    QStandardItem *Item3= new QStandardItem();
    int ID = 0;
    int test = 1000000;
     Item->setData (ID = test,Qt::DisplayRole);
     Item2->setData("B", Qt::DisplayRole);
     Item3->setData("C:\\Program Files (x86)\\Internet Explorer\\file.img", Qt::DisplayRole);

    smodel->setHorizontalHeaderItem(0,new QStandardItem("Drive letter"));
    smodel->setHorizontalHeaderItem(1,new QStandardItem("File size"));
    smodel->setHorizontalHeaderItem(2,new QStandardItem("File path"));
    smodel->setItem(0,1,Item);
    smodel->setItem(0,0,Item2);
    smodel->setItem(0,2,Item3);


    this->ui->tableView->setModel(smodel);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunD_clicked()
{
}

void MainWindow::on_Create_clicked()
{
    CreateNew NewDrive;
    NewDrive.setFixedSize(500,220);
    NewDrive.setModal(true);
    NewDrive.exec();
}

void MainWindow::on_Copy_clicked()
{
    Copy CopyFile;
    CopyFile.setFixedSize(400,125);
    CopyFile.setModal(true);
    CopyFile.exec();
}

void MainWindow::on_Mount_clicked()
{
    Mount Mount;
    Mount.setFixedSize(400,125);
    Mount.setModal(true);
    Mount.exec();
}
