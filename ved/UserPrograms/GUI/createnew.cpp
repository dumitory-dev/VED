#include "createnew.h"
#include "ui_createnew.h"
#include <QFileDialog>

CreateNew::CreateNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNew)
{
    ui->setupUi(this);
    ui->Crypt->addItem("Без шифрования");
    ui->Crypt->addItem("XOR");
    ui->Crypt->addItem("Режим шифрования 1");
    ui->Crypt->addItem("Режим шифрования 2");
    ui->SizeType->addItem("Мбайт");
    ui->SizeType->addItem("Гбайт");
}

CreateNew::~CreateNew()
{
    delete ui;
}

void CreateNew::on_buttonBox_accepted()
{
    close();
}

void CreateNew::on_buttonBox_rejected()
{
    close();
}

void CreateNew::on_PathButton_clicked()
{
    ui->Path->setText(QFileDialog::getExistingDirectory(this, "Get Any File","C://"));
}
