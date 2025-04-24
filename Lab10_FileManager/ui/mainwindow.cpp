#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- МОДЕЛЬ ЛЕВОЙ ПАНЕЛИ ---
    leftModel = new QFileSystemModel(this);
    leftModel->setFilter( QDir::AllEntries         // Файлы + папки
                         | QDir::NoDotAndDotDot );  // без . и ..
    leftModel->setNameFilters( QStringList() << "*" ); // показывать всё
    leftModel->setNameFilterDisables(false);          // не скрывать по фильтру
    ui->treeViewLeft->setModel(leftModel);

    // --- МОДЕЛЬ ПРАВОЙ ПАНЕЛИ ---
    rightModel = new QFileSystemModel(this);
    rightModel->setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );
    rightModel->setNameFilters( QStringList() << "*" );
    rightModel->setNameFilterDisables(false);
    ui->treeViewRight->setModel(rightModel);
    ui->treeViewRight->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //--- Сигналы/слоты кнопок ---
    connect(ui->btnSelectLeftDir,  &QPushButton::clicked,
            this, &MainWindow::chooseLeftDir);
    connect(ui->pushButton,        &QPushButton::clicked,
            this, &MainWindow::chooseRightDir);
    connect(ui->btnCopyFiles,      &QPushButton::clicked,
            this, &MainWindow::copyFiles);

    connect(&controller, &FileManagerController::copyFinished,
            this,        &MainWindow::onCopyFinished);
}

void MainWindow::chooseLeftDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose source");
    if(dir.isEmpty()) return;

    controller.setSourceDir(dir);
    leftModel->setRootPath(dir);
    ui->treeViewLeft->setRootIndex(leftModel->index(dir));
    statusBar()->showMessage("Source: " + dir, 3000);
}

void MainWindow::chooseRightDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose destination");
    if(dir.isEmpty()) return;

    controller.setDestDir(dir);
    rightModel->setRootPath(dir);
    ui->treeViewRight->setRootIndex(rightModel->index(dir));
    statusBar()->showMessage("Destination: " + dir, 3000);
}

void MainWindow::copyFiles()
{
    if(controller.sourceDir().isEmpty() || controller.destDir().isEmpty()) {
        QMessageBox::warning(this,"Dirs not selected",
                             "Select both source and destination folders first.");
        return;
    }

    QModelIndexList idxs = ui->treeViewLeft->selectionModel()->selectedRows();
    if(idxs.isEmpty()) return;

    QList<QString> paths;
    for(const QModelIndex& idx : idxs)
        paths << leftModel->filePath(idx);

    controller.copySelected(paths);
}

void MainWindow::onCopyFinished(int copied,int skipped,const QString& msg)
{
    statusBar()->showMessage(
        QString("Copied %1, skipped %2  (%3)")
            .arg(copied).arg(skipped).arg(msg), 5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
