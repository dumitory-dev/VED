#include "copy.h"
#include "ui_copy.h"
#include <QFileDialog>

Copy::Copy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Copy)
{
    ui->setupUi(this);
}

Copy::~Copy()
{
    delete ui;
}

void Copy::on_buttonBox_accepted()
{
    close();
}

void Copy::on_buttonBox_rejected()
{
    close();
}

void Copy::on_PathButton_clicked()
{
    ui->File->setText(QFileDialog::getOpenFileName(this, "Get Any File","C://"));
}

void Copy::on_PathButton_2_clicked()
{
    ui->Dir->setText(QFileDialog::getExistingDirectory(this, "Get Any File","C://"));
}
