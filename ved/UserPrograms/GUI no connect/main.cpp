#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "source/classes/copy_sparse/copy_sparse.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(600,280);
    w.show();
    try {
        ved::copy_sparse::copy(L"sdf",L"sdf");
    } catch (const ved::c_win_api_exception & error) {
        QMessageBox tmp;

        tmp.setText(QString::fromWCharArray(error.GetMessageW().c_str()));
        tmp.exec();
    }

    return a.exec();
}
