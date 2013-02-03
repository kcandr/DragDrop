#include "mainwindow.h"
#include "blanklist.h"
#include "tablewidget.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWidgets();

    setWindowTitle(tr("Packing"));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::openImage()
{
    QString fileName(":/images/square.jpg");
    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QPixmap newImage;
        if (!newImage.load(fileName)) {
            QMessageBox::warning(this, tr("Open Image"),
                                  tr("The image file could not be loaded."),
                                  QMessageBox::Cancel);
            return;
        }
        blankImage = newImage;
        blankList->addBlank(blankImage);
        blankList->addBlank(blankImage);
        blankList->addBlank(blankImage.scaled(50, 50));
    }
}

void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    blankList = new BlankList(200, this);
    tableWidget = new TableWidget(600, this);

    frameLayout->addWidget(blankList);
    frameLayout->addWidget(tableWidget);
    setCentralWidget(frame);
}
