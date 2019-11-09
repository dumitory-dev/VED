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

signals:

private slots:
    void on_PathButton_clicked();

    void on_Ok_clicked();

    void on_Cancel_clicked();

private:
    Ui::Mount *ui;
};

#endif // MOUNT_H
