#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);
    TableWidget(int tableSize, QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    int findBlank(const QPoint &blankRect) const;
    const QRect targetSquare(const QPoint &position, const int size) const;

    QList<QPixmap> blankPixmaps;
    QList<QRect> blankRects;
    QRect highlightedRect;
    int m_TableSize;
    
};

#endif // TABLEWIDGET_H
