#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

class BlankList;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openImage();

private:
    void setupWidgets();

    QPixmap blankImage;
    BlankList *blankList;
};

#endif // MAINWINDOW_H
