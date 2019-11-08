#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include "source/classes/ved_manager/ved_manager.h"
#include "source/classes/exceptions/exception.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(600,280);
    w.show();
    ved::ved_manager ved{};
    //test library
    try {
        ved.mount(L"c:\\eerer","sdsd",L'D');
    } catch (const ved::c_win_api_exception & error) {
       // std::wcout<<error.GetMessageW()<<std::endl;

    }
    catch(const std::exception & error){
        QMessageBox msgBox;
        msgBox.setText(error.what());
        msgBox.exec();
    }

    return a.exec();
}
