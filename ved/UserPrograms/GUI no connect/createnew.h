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

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_PathButton_clicked();
private:
    Ui::CreateNew *ui;
};

#endif // CREATENEW_H
