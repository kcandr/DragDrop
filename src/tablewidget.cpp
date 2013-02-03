#include "tablewidget.h"
#include <QtGui>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent), m_TableSize(0)
{
}

TableWidget::TableWidget(int tableSize, QWidget *parent) :
    QWidget(parent), m_TableSize(tableSize)
{
    setAcceptDrops(true);
    //TODO: set width and height of table
    setFixedSize(m_TableSize, m_TableSize);
}

void TableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/drag")) {
        event->accept();
    } else {
        event->ignore();
    }
}

void TableWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void TableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect;
    //QRect updateRect = highlightedRect.unite(targetSquare(event->pos(), 200));

    if (event->mimeData()->hasFormat("image/drag")) {
        QByteArray blankData = event->mimeData()->data("image/drag");
        QDataStream dataStream(&blankData, QIODevice::ReadOnly);
        QPixmap pixmap;
        int blankSize;

        dataStream >> pixmap >> blankSize;

        updateRect = highlightedRect.unite(targetSquare(event->pos(), blankSize));

        highlightedRect = targetSquare(event->pos(), blankSize);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void TableWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/drag")) {
        QByteArray blankData = event->mimeData()->data("image/drag");
        QDataStream dataStream(&blankData, QIODevice::ReadOnly);
        QPixmap pixmap;
        int blankSize;

        dataStream >> pixmap >> blankSize;

        QRect square = targetSquare(event->pos(), blankSize);
        blankPixmaps.append(pixmap);
        blankRects.append(square);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int TableWidget::findBlank(const QPoint &position) const
{
    for (int i = 0; i < blankRects.size(); ++i) {
        if (blankRects[i].contains(position)) {
            return i;
        }
    }
    return -1;
}

void TableWidget::mousePressEvent(QMouseEvent *event)
{
    int found = findBlank(event->pos());

    if (found == -1) {
        return;
    }

    QPixmap pixmap = blankPixmaps[found];
    QRect blankSquare = blankRects[found];
    //QRect square = targetSquare(event->pos(), );
    blankPixmaps.removeAt(found);
    blankRects.removeAt(found);

    update(blankSquare);

    QByteArray blankData;
    QDataStream dataStream(&blankData, QIODevice::WriteOnly);

    dataStream << pixmap << pixmap.size();

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/drag", blankData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        blankPixmaps.insert(found, pixmap);
        blankRects.insert(found, blankSquare);
        update(targetSquare(event->pos(), pixmap.width()));
    }

}

void TableWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor(255, 102, 0, 50));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }
    for (int i = 0; i < blankPixmaps.size(); ++i) {
        painter.drawPixmap(blankRects[i], blankPixmaps[i]);
    }
    painter.end();
}

const QRect TableWidget::targetSquare(const QPoint &position, const int size) const
{
    bool isIntersects = false;
    QRect target(position.x() / 50 * 50, position.y() / 50 * 50, size, size);

    for (int i = 0; i < blankRects.size(); ++i) {
        if (blankRects[i].intersects(target)) {
            isIntersects = true;
        }
    }
    if (!isIntersects) {
        return target;
    }
}
