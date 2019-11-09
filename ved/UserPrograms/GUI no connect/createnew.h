#ifndef CREATENEW_H
#define CREATENEW_H

#include <QDialog>

namespace Ui {
class CreateNew;
}

class CreateNew : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNew(QWidget *parent = nullptr);
    ~CreateNew();

signals:
    void signalToTable();

private slots:
    void on_Ok_clicked();

    void on_Cancel_clicked();

    void on_PathButton_clicked();
private:
    Ui::CreateNew *ui;
};

#endif // CREATENEW_H
