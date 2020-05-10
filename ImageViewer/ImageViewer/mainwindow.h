#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QToolBar>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void initUI();
    void createAction();
    void createMenu();
    void createStatusBar();
    void initToolBar();

    QMenu *fileMenu;
    QMenu *viewMenu;

    QToolBar * fileToolBar;
    QToolBar * viewToolBar;

    QGraphicsScene *imageScene;
    QGraphicsView *imageView;

    QGraphicsPixmapItem *currentImage;
    QString currentImagePath;
    QLabel *mainStatusLabel;

    QAction *openAction;
    QAction *saveAsAction;
    void openImage_Slot();
    void saveAsAction_Slot();

    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *prevAction;
    QAction *nextAction;
    void zoomInAction_Slot();
    void zoomOutAction_Slot();

    void prevImage_Slot();
    void nextImage_Slot();


    void showImage(const QString &imagePath);


};
#endif // MAINWINDOW_H
