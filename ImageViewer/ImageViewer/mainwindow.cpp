#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    resize(800, 600);
    createAction();
    createMenu();
    createStatusBar();
    initToolBar();


    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    setCentralWidget(imageView);


}

void MainWindow::createAction()
{
    openAction = new QAction("&Open", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage_Slot);
    saveAsAction = new QAction("&Save As", this);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsAction_Slot);

    zoomInAction = new QAction("Zoom In", this);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomInAction_Slot);
    zoomOutAction = new QAction("Zoom Out", this);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOutAction_Slot);

    prevAction = new QAction("Prev Img", this);
    connect(prevAction, &QAction::triggered, this, &MainWindow::prevImage_Slot);
    nextAction = new QAction("Next Img", this);
    connect(nextAction, &QAction::triggered, this, &MainWindow::nextImage_Slot);

}

void MainWindow::createMenu()
{
    fileMenu = new QMenu("&Files");
    ui->menubar->addMenu(fileMenu);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAsAction);

    viewMenu = new QMenu("&View");
    ui->menubar->addMenu(viewMenu);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(prevAction);
    viewMenu->addAction(nextAction);

}

void MainWindow::createStatusBar()
{
//    statusBar()->showMessage("Ready");
    ui->statusbar->showMessage("Ready");
}

void MainWindow::initToolBar()
{
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAsAction);

    viewToolBar = addToolBar("View");
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(prevAction);
    viewToolBar->addAction(nextAction);
}

void MainWindow::openImage_Slot()
{
    qDebug() << "OpenImage";
    QStringList filePaths = QFileDialog::getOpenFileNames(this, "Open Image", QDir::homePath(), "Images (*.png *.bmp *.jpg)");
//    qDebug() << filePaths.at(0);
    if(!filePaths.isEmpty())
    {
        QString currentPath = filePaths.at(0);
        showImage(currentPath);
    }
}

void MainWindow::saveAsAction_Slot()
{
    qDebug() << "Save As";
    if(currentImage == nullptr)
    {
        QMessageBox::information(this, "Information", "Nothing to save.");
        return;
    }
    QString savePath = QFileDialog::getSaveFileName(this, "Save As an Image.", QDir::homePath(), "Image (*.png *.bmp *.jpg)");
    if(!savePath.isEmpty())
    {
        // 此处最好通过扩展名判断是否合法
        currentImage->pixmap().save(savePath);
    }
    else
    {
        //
    }

}

void MainWindow::zoomInAction_Slot()
{
    imageView->scale(1.2, 1.2);
}

void MainWindow::zoomOutAction_Slot()
{
    imageView->scale(1/1.2, 1/1.2);
}

void MainWindow::prevImage_Slot()
{
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << ".bmp" << ".jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    if(idx > 0)
        showImage(dir.absoluteFilePath(fileNames.at(idx-1)));
    else
        QMessageBox::information(this, "Information", "Current image is the first one.");
}

void MainWindow::nextImage_Slot()
{
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << ".bmp" << ".jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    if(idx < fileNames.size()-1)
        showImage(dir.absoluteFilePath(fileNames.at(idx+1)));
    else
        QMessageBox::information(this, "Information", "Current image is the last one.");
}

void MainWindow::showImage(const QString &imagePath)
{
    imageScene->clear();
    imageView->resetMatrix();
    QPixmap image(imagePath);
    currentImage = imageScene->addPixmap(image);
    imageScene->update();
    imageView->setSceneRect(image.rect());
    QString status = QString("%1, %2x%3, %4 Bytes").arg(imagePath).arg(image.width()).arg(image.height()).arg(QFile(imagePath).size());
    ui->statusbar->showMessage(status);
    currentImagePath = imagePath;
}


