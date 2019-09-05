﻿#include "ltextedit.h"

LTextEdit::LTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

LTextEdit::~LTextEdit()
{

}

void LTextEdit::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
    else {
        event->ignore();
    }
}

void LTextEdit::dropEvent(QDropEvent *event)
{
    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //往文本框中追加文件名
    foreach(QUrl url, urls)
    {
        QString file_name = url.toLocalFile();
        this->setText(file_name);
    }
}
