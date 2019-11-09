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
    connect(this,&MainWindow::signalToTable,this,&MainWindow::CreateTable);
    emit signalToTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunD_clicked()
{

}

void MainWindow::on_StopD_clicked()
{

}

void MainWindow::on_Create_clicked()
{
    CreateNew *NewDrive = new CreateNew(this);
    NewDrive->setFixedSize(500,220);
    NewDrive->setModal(true);
    NewDrive->exec();
}

void MainWindow::on_Copy_clicked()
{
    Copy *CopyFile = new Copy(this);
    connect(CopyFile,SIGNAL(signalToTable()),this,SLOT(CreateTable()));
    CopyFile->setFixedSize(400,125);
    CopyFile->setModal(true);
    CopyFile->exec();
}

void MainWindow::on_Mount_clicked()
{
    Mount *MountDrive = new Mount(this);
    MountDrive->setFixedSize(400,125);
    MountDrive->setModal(true);
    MountDrive->exec();
}

void MainWindow::on_Unmount_clicked()
{
    emit signalToTable();
}

void MainWindow::on_Refresh_clicked()
{
    emit signalToTable();
}

void MainWindow::CreateTable()
{
    QStandardItemModel *smodel = new QStandardItemModel;
    QStandardItem *Item;
    smodel->setHorizontalHeaderItem(0,new QStandardItem("Drive letter"));
    smodel->setHorizontalHeaderItem(1,new QStandardItem("File size"));
    smodel->setHorizontalHeaderItem(2,new QStandardItem("File path"));
    char k='0';
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            Item = new QStandardItem(QString(k++));
            smodel->setItem(i,j,Item);
        }

    this->ui->tableView->setModel(smodel);
    ui->tableView->resizeColumnsToContents();
}


