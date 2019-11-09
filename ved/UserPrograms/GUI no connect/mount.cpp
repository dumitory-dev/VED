#include "mount.h"
#include "ui_mount.h"
#include <QFileDialog>

Mount::Mount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mount)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
}

Mount::~Mount()
{
    delete ui;
}

void Mount::on_PathButton_clicked()
{
    ui->File->setText(QFileDialog::getOpenFileName(this, "Get Any File","C://"));
}

void Mount::on_Ok_clicked()
{
    if(ui->File->text().isEmpty()||ui->FileName->text().isEmpty())
    ui->label->setVisible(true);
    else
    {
        emit signalToTable();
        close();
    }
}

void Mount::on_Cancel_clicked()
{
    close();
}
