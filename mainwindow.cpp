#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basictransceiver.h"
#include "mycv.h"
#include "widget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textEdit1 = new LTextEdit(ui->tab);
    layout = new QGridLayout(ui->tab);

    layout->addWidget(textEdit1,0,1,1,1);
    layout->addWidget(ui->textEdit_2,1,1,1,1);
    layout->addWidget(ui->label,0,0,1,1);
    layout->addWidget(ui->label_2,1,0,1,1);

    layout->addWidget(ui->pushButton,2,0,1,1);
    layout->addWidget(ui->comboBox_code,2,1,1,1);

    ui->textEdit_2->setAcceptDrops(false);
    ui->centralWidget->setLayout(layout);


    /**********TAB2**********/
    dirtextEdit = new LTextEdit(ui->tab_2);
    filetextEdit = new LTextEdit(ui->tab_2);

    layouttab2 = new QGridLayout(ui->tab_2);
    layouttab2->setSpacing(6);
    layouttab2->setContentsMargins(11, 11, 11, 11);
    layouttab2->setObjectName(QString::fromUtf8("gridLayout_5"));
    dirtextEdit->setMaximumHeight(40);
    filetextEdit->setMaximumHeight(40);
    layouttab2->addWidget(dirtextEdit, 0, 0, 1, 2);
    layouttab2->addWidget(filetextEdit, 1, 0, 1, 2);


    layouttab2->addWidget(ui->label_3, 2, 0, 1, 1);
    layouttab2->addWidget(ui->label_4, 3, 0, 1, 1);
    layouttab2->addWidget(ui->filelabel, 2, 1, 1, 1);
    layouttab2->addWidget(ui->md5label, 3, 1, 1, 1);

    layouttab2->addWidget(ui->dirlistWidget, 4, 0, 1, 1);
    layouttab2->addWidget(ui->exitlistWidget, 4, 1, 1, 1);
    layouttab2->addWidget(ui->commandLinkButton, 5, 0, 1, 1);

    file1OK = false;
    file2OK = false;


    connect(dirtextEdit,SIGNAL(textChanged()),this,SLOT(on_dirltextedit_changed()));
    connect(filetextEdit,SIGNAL(textChanged()),this,SLOT(on_fileltextedit_changed()));

    HashTab = new map<string, string>;


}

MainWindow::~MainWindow()
{
    delete HashTab;
    delete textEdit1;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

        //qDebug()<<QStringLiteral("开始点击");
        ui->textEdit_2->clear();
        ui->textEdit_2->update();
        QProcess myProcess(this);
        QString program = "FILEHASH.exe";

        QStringList arguments;
        arguments<<HSHCmd<<textEdit1->toPlainText().trimmed();//传递到exe的参数
        myProcess.start(program,arguments);
        while (myProcess.waitForFinished(1) == false) {
            QByteArray qByteRead = myProcess.readAllStandardOutput();
            if (!qByteRead.isEmpty()) {
                repaint();
            }
        }
        QByteArray qByteRead = myProcess.readAllStandardOutput();
        ui->textEdit_2->moveCursor(QTextCursor::Up,QTextCursor::MoveAnchor);
        ui->textEdit_2->append(HSHCmd+":"+QString::fromLocal8Bit(qByteRead));
        qDebug()<<QString::fromLocal8Bit(qByteRead);
       // qDebug()<<"结束点击";
}


void MainWindow::on_comboBox_code_currentIndexChanged(const QString &arg1)
{
    HSHCmd = arg1;
    on_pushButton_clicked();
}

void MainWindow::on_commandLinkButton_clicked()
{
    //qDebug()<<"on_commandLinkButton_clicked"<<endl;
    QString runPath = QCoreApplication::applicationDirPath();       //获取exe路径。
    //qDebug()<<runPath<<endl;
    openDir(runPath+"\\cache");
}

void MainWindow::on_dirltextedit_changed()
{
    qDebug()<<"on_dirltextedit_changed";

    file1OK = true;

    QProcess myProcess(this);
    QString program = "HashTableCPP1.exe";

    QStringList arguments;
    arguments<<dirtextEdit->toPlainText().trimmed()<<"1.txt";//传递到exe的参数
    myProcess.start(program,arguments);
    while (myProcess.waitForFinished(1) == false) {
        QByteArray qByteRead = myProcess.readAllStandardOutput();
        if (!qByteRead.isEmpty()) {
            repaint();
        }
    }
    QByteArray qByteRead = myProcess.readAllStandardOutput();

    qDebug()<<QString::fromLocal8Bit(qByteRead);

}

void MainWindow::on_fileltextedit_changed()
{


    file2OK = true;

        if(file1OK && file2OK)
        {
            /***********生成被查找文件的MD5码******************/
            QString NAME = filetextEdit->toPlainText().trimmed().section('/',-1);
            QString KEY;

            QProcess myProcess(this);
            QString program = "FILEHASH";

            QStringList arguments;
            qDebug()<<"keyFILE="<<filetextEdit->toPlainText().trimmed()<<endl;
            arguments<<"MD5"<<filetextEdit->toPlainText().trimmed();//传递到exe的参数
            myProcess.start(program,arguments);

            while (myProcess.waitForFinished(1) == false) {
                QByteArray qByteRead = myProcess.readAllStandardOutput();
                if (!qByteRead.isEmpty()) {
                    repaint();
                }
            }
            QByteArray qByteRead = myProcess.readAllStandardOutput();
            KEY = QString::fromLocal8Bit(qByteRead);
            ui->md5label->setText(KEY);
            ui->filelabel->setText(NAME);


            /****************装载查询到的MD5码*******************/

            loadHashTable(HashTab,"./cache/1.txt");
            QStringList FileNames;
            map<string,string>::iterator it;
            for(it = HashTab->begin(); it != HashTab->end(); it++) {
                //cout<<it->first<<" "<<it->second<<endl;
                FileNames<< QString(QString::fromLocal8Bit(it->second.c_str()));
            }


            /*********装载到listwidget**********/
             //方法1  整体添加
            //    ui->listWidget->addItems(FileNames);

             //方法2  逐个添加
             int index=0,count=0;
            //    QListWidgetItem *item = new QListWidgetItem;  //…………注释1
             count = FileNames.count();              //获取打开文件的总数目

            //    for(index = 0;index<count;index++)    //这样会报错，无法先取出栈底元素  //注释2
            for(index=count-1;index>=0;index--)     //QList<QString>的数据结构是栈，只能从栈顶取元素
            {
                 QListWidgetItem *item = new QListWidgetItem;
                 item->setText(FileNames.takeAt(index)); //逐个设置列表项的文本
            //        qDebug()<<FileNames.takeAt(index);        //…………注释3
                 ui->dirlistWidget->addItem(item);      //加载列表项到列表框
            }

            /*************判断文件是否存在********************/
            QStringList existNames;
            qDebug()<<KEY.trimmed().toStdString().c_str()<< endl;
            if (HashTab->find(KEY.trimmed().toStdString().c_str()) == HashTab->end())
            {

                existNames<<"该文件不存在";
                ui->exitlistWidget->addItems(existNames);
                cout << (*HashTab)[KEY.trimmed().toStdString().c_str()] << endl;
            }
            else {

                existNames<<QString::fromStdString(NAME.toStdString());
                ui->exitlistWidget->addItems(existNames);

            }

            file2OK = false;
        }
}

void MainWindow::openDir(const QString &path)
{
        QFile bfilePath(path);
        if(bfilePath.exists()){
            QString filePath = "file:///" + path;
            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

            }else {
            QMessageBox::warning(this, tr("错误！"),
                        tr("文件夹丢失！"),
                        QMessageBox::Yes);
         }

}

void MainWindow::on_dirlistWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::information(this,tr("MD5"),item->text());
}

void MainWindow::on_actionFusion_triggered()
{
    QApplication::setStyle(QStyleFactory::create("fusion"));
}

void MainWindow::on_actionWindows_triggered()
{
    QApplication::setStyle(QStyleFactory::create("windows"));
}

void MainWindow::on_actionMotif_triggered()
{
    QApplication::setStyle(QStyleFactory::create("macintosh"));
}

void MainWindow::on_actionCde_triggered()
{
    QApplication::setStyle(QStyleFactory::create("windowsvista"));
}


void MainWindow::on_commandLinkButton_2_clicked()
{
    BasicTransceiver *uart = new BasicTransceiver(this);
    uart->setWindowTitle(QStringLiteral("串口助手"));
    uart->show();
}

void MainWindow::on_commandLinkButton_6_clicked()
{
    sport();
}

void MainWindow::on_commandLinkButton_7_clicked()
{
    color();
}

void MainWindow::on_commandLinkButton_3_clicked()
{
    face();
}

void MainWindow::on_commandLinkButton_4_clicked()
{
    QMainWindow *bluetoothmain = new QMainWindow(this);
    Widget *bluetooth = new Widget(bluetoothmain);
    bluetooth->setWindowIcon(QIcon(":/images/bluetooth.png"));
    bluetoothmain->setMinimumSize(QSize(594,564));
    bluetoothmain->setWindowTitle(QStringLiteral("蓝牙调试助手"));
    bluetoothmain->setCentralWidget(bluetooth);
    bluetoothmain->show();
}
