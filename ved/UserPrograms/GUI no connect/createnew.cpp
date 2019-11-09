#include "createnew.h"
#include "ui_createnew.h"
#include <QFileDialog>

CreateNew::CreateNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNew)
{
    ui->setupUi(this);
    ui->Crypt->addItem("RC4");
    ui->Crypt->addItem("AEC");
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
