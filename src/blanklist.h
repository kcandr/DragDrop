#ifndef BLANKLIST_H
#define BLANKLIST_H

#include <QListWidget>

class BlankList : public QListWidget
{
    Q_OBJECT
public:
    explicit BlankList(QWidget *parent = 0);
    BlankList(int size, QWidget *parent = 0);
    void addBlank(QPixmap pixmap);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);

    int m_Size;
    
};

#endif // BLANKLIST_H
