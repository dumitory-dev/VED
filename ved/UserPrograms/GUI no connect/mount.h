#ifndef MOUNT_H
#define MOUNT_H

#include <QDialog>

namespace Ui {
class Mount;
}

class Mount : public QDialog
{
    Q_OBJECT

public:
    explicit Mount(QWidget *parent = nullptr);
    ~Mount();

private slots:
    void on_PathButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Mount *ui;
};

#endif // MOUNT_H
