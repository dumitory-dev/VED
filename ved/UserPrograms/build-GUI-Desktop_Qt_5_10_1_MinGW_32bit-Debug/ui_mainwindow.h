/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *CreateNew;
    QPushButton *Add;
    QPushButton *Remove;
    QPushButton *Mount;
    QPushButton *Unmount;
    QTableWidget *tableWidget;
    QWidget *page_2;
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *PathButton;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *DiskSize;
    QLabel *label;
    QLineEdit *Path;
    QLineEdit *Password;
    QLabel *label_6;
    QLineEdit *DiskLetter;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(592, 238);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, -20, 601, 411));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(460, 40, 121, 161));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        CreateNew = new QPushButton(verticalLayoutWidget);
        CreateNew->setObjectName(QStringLiteral("CreateNew"));

        verticalLayout_2->addWidget(CreateNew);

        Add = new QPushButton(verticalLayoutWidget);
        Add->setObjectName(QStringLiteral("Add"));

        verticalLayout_2->addWidget(Add);

        Remove = new QPushButton(verticalLayoutWidget);
        Remove->setObjectName(QStringLiteral("Remove"));

        verticalLayout_2->addWidget(Remove);

        Mount = new QPushButton(verticalLayoutWidget);
        Mount->setObjectName(QStringLiteral("Mount"));

        verticalLayout_2->addWidget(Mount);

        Unmount = new QPushButton(verticalLayoutWidget);
        Unmount->setObjectName(QStringLiteral("Unmount"));

        verticalLayout_2->addWidget(Unmount);

        tableWidget = new QTableWidget(page);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 441, 161));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        buttonBox = new QDialogButtonBox(page_2);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(400, 180, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(page_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 50, 471, 129));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PathButton = new QToolButton(widget);
        PathButton->setObjectName(QStringLiteral("PathButton"));

        gridLayout->addWidget(PathButton, 1, 2, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        DiskSize = new QLineEdit(widget);
        DiskSize->setObjectName(QStringLiteral("DiskSize"));

        gridLayout->addWidget(DiskSize, 2, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Path = new QLineEdit(widget);
        Path->setObjectName(QStringLiteral("Path"));

        gridLayout->addWidget(Path, 1, 1, 1, 1);

        Password = new QLineEdit(widget);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setMaxLength(16);
        Password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Password, 3, 1, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 2, 1, 1);

        DiskLetter = new QLineEdit(widget);
        DiskLetter->setObjectName(QStringLiteral("DiskLetter"));
        DiskLetter->setMaxLength(1);

        gridLayout->addWidget(DiskLetter, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 592, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        CreateNew->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        Add->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Remove->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        Mount->setText(QApplication::translate("MainWindow", "\320\234\320\276\320\275\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        Unmount->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\276\320\275\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        PathButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\232\320\261", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\221\321\203\320\272\320\262\320\260 \320\264\320\270\321\201\320\272\320\260", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "*\320\224\320\276 16 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
