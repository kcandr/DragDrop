#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

class BlankList;
class TableWidget;
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
    TableWidget *tableWidget;
};

#endif // MAINWINDOW_H
