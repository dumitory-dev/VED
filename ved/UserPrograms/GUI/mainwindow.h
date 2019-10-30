#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_CreateNew_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_PathButton_clicked();

    void on_Add_clicked();

    void on_Remove_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
