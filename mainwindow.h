#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QList>
#include <QDebug>
#include <qprocess.h>
#include <QDir>
#include <QTabWidget>
#include "ltextedit.h"
#include <QGridLayout>
#include <qfiledialog.h>
#include "hashtable.h"
#include <QFile>
#include <QDesktopServices>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QStyleFactory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend bool loadHashTable(map<string, string>* HashTab, string path);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_comboBox_code_currentIndexChanged(const QString &arg1);

    void on_commandLinkButton_clicked();

    void on_dirltextedit_changed();

    void on_fileltextedit_changed();

    //打开一个文件夹窗口
    void openDir(const QString& path);

    void on_dirlistWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionFusion_triggered();

    void on_actionWindows_triggered();

    void on_actionMotif_triggered();

    void on_actionCde_triggered();


    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_6_clicked();

    void on_commandLinkButton_7_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

private:
    Ui::MainWindow *ui;

    QString HSHCmd = "MD5";

    LTextEdit *textEdit1;
    QGridLayout*layout;


    /*TAB2*/
    LTextEdit *dirtextEdit;
    LTextEdit *filetextEdit;
    bool file1OK;
    bool file2OK;
    QGridLayout*layouttab2;
    map<string, string> *HashTab;
    QString cacheDirPath;


};

#endif // MAINWINDOW_H
