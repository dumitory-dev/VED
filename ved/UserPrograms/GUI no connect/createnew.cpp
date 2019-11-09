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
    ui->label->setVisible(false);
}

CreateNew::~CreateNew()
{
    delete ui;
}

void CreateNew::on_Ok_clicked()
{
    if(ui->FileName->text().isEmpty()||ui->Path->text().isEmpty()||ui->Password->text().isEmpty())
    ui->label->setVisible(true);
    else
    close();
}

void CreateNew::on_Cancel_clicked()
{
    close();
}

void CreateNew::on_PathButton_clicked()
{
    ui->Path->setText(QFileDialog::getExistingDirectory(this, "Get Any File","C://"));
}
