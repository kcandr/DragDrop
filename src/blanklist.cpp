#include "blanklist.h"
#include <QtGui>

BlankList::BlankList(QWidget *parent) :
    QListWidget(parent)
{
}

BlankList::BlankList(int size, QWidget *parent) :
    QListWidget(parent), m_Size(size)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_Size, m_Size));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void BlankList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/drag")) {
        event->accept();
    } else {
        event->ignore();
    }
}

void BlankList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/drag")) {
        event->setDropAction(Qt::MoveAction);
        event->setAccepted(true);
    } else {
        event->ignore();
    }
}

void BlankList::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/drag")) {
        QByteArray blankData = event->mimeData()->data("image/drag");
        QDataStream dataStream(&blankData, QIODevice::ReadOnly);
        QPixmap pixmap;
        dataStream >> pixmap;

        addBlank(pixmap);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void BlankList::addBlank(QPixmap pixmap)
{
    QListWidgetItem *blankItem = new QListWidgetItem(this);
    blankItem->setIcon((QIcon(pixmap)));
    blankItem->setData(Qt::UserRole, QVariant(pixmap));
    blankItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}


void BlankList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));

    dataStream << pixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/drag", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
}
