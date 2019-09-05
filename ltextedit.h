#ifndef LTEXTEDIT_H
#define LTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
class LTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit LTextEdit(QWidget *parent = nullptr);
    ~LTextEdit();
    //当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
    void dragEnterEvent(QDragEnterEvent *event);
    //当用户放下这个文件后，就会触发dropEvent事件
    void dropEvent(QDropEvent *event);
signals:

public slots:

};

#endif // LTEXTEDIT_H
