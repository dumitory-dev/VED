#include "mount.h"
#include "ui_mount.h"
#include <QFileDialog>

Mount::Mount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mount)
{
    ui->setupUi(this);
}

Mount::~Mount()
{
    delete ui;
}

void Mount::on_PathButton_clicked()
{
    ui->File->setText(QFileDialog::getOpenFileName(this, "Get Any File","C://"));
}

void Mount::on_buttonBox_accepted()
{
    close();
}

void Mount::on_buttonBox_rejected()
{
    close();
}
