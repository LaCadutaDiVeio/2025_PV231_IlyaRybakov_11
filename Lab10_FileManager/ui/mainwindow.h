#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include "controller/file_manager_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void chooseLeftDir(); // “Select left dir”
    void chooseRightDir(); // “Select right dir”
    void copyFiles(); // “===Copy==>”
    void onCopyFinished(int copied,int skipped,const QString& msg);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *leftModel  = nullptr;
    QFileSystemModel *rightModel = nullptr;
    FileManagerController controller;
};
#endif // MAINWINDOW_H
