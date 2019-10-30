#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList Header;
    Header<<"Активность"<<"Диск"<<"Размер"<<"Путь";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(Header);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CreateNew_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_buttonBox_accepted()
{
    int NewRow;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    NewRow=ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(NewRow,0,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(NewRow,1,new QTableWidgetItem(ui->DiskLetter->text()));
    ui->tableWidget->setItem(NewRow,2,new QTableWidgetItem(ui->DiskSize->text()));
    ui->tableWidget->setItem(NewRow,3,new QTableWidgetItem(ui->Path->text()));
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonBox_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_PathButton_clicked()
{
    ui->Path->setText(QFileDialog::getExistingDirectory(this, "Get Any File","C://"));
}

void MainWindow::on_Add_clicked()
{

}

void MainWindow::on_Remove_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}
