#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init_Table();
    connect(this, SIGNAL(Send_TestAndOutput_Fin()), this, SLOT(TestAndOutput_Fin()));
    connect(this, SIGNAL(Send_TextBrowser_NewMSG(QString)), this, SLOT(TextBrowser_NewMSG(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init_Table()
{
    Table_model->setColumnCount(2);
    Table_model->setHeaderData(0, Qt::Horizontal, "网址");
    Table_model->setHeaderData(1, Qt::Horizontal, "IP");
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->setModel(Table_model);
    //=============================================
    //将横向表头设置为可见
    ui->tableView->horizontalHeader()->setVisible(1);
}

void MainWindow::on_pushButton_AddWebSite_clicked()
{
    ui->tableView->setUpdatesEnabled(false);
    int rowNum = Table_model->rowCount();
    Table_model->setItem(rowNum, 0, new QStandardItem(ui->lineEdit_addWebSite->text()));
    //========
    QAbstractItemModel *modessl = Table_model;
    QModelIndex indextemp = modessl->index(rowNum, 1);
    ui->tableView->scrollTo(indextemp);
    //========
    ui->tableView->setUpdatesEnabled(true);
}

void MainWindow::on_pushButton_AddIP_clicked()
{
    if(curRow!=-1)
    {
        ui->tableView->setUpdatesEnabled(false);
        int rowNum = curRow;
        Table_model->setItem(rowNum, 1, new QStandardItem(ui->lineEdit_addIP->text()));
        //========
        QAbstractItemModel *modessl = Table_model;
        QModelIndex indextemp = modessl->index(rowNum, 1);
        ui->tableView->scrollTo(indextemp);
        //========
        ui->tableView->setUpdatesEnabled(true);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int curRow_new = ui->tableView->currentIndex().row();
    if(curRow_new == curRow)
    {
        curRow = -1;
        ui->tableView->clearSelection();
    }
    else
    {
        curRow = curRow_new;
    }
}

void MainWindow::on_pushButton_TestAndOutput_clicked()
{
    ui->pushButton_TestAndOutput->setEnabled(0);
    OutPut_List.clear();
    ui->textBrowser_progress->append("开始测试选优, 请耐心等待.");
    QtConcurrent::run(this, &MainWindow::TestAndOutput);
}
void MainWindow::TestAndOutput()
{
    int MAXrowNum = Table_model->rowCount();
    QAbstractItemModel *modessl = Table_model;
    for(int rowNum=0; rowNum<MAXrowNum; rowNum++)
    {
        BestIP="";
        QModelIndex indextemp = modessl->index(rowNum, 0);
        QVariant datatemp = modessl->data(indextemp);
        QString WebSite = datatemp.toString();
        //===============
        indextemp = modessl->index(rowNum, 1);
        datatemp = modessl->data(indextemp);
        QString IP_str = datatemp.toString();
        QStringList IP_List = IP_str.split(",");
        IP_List.removeAll("");
        //===============
        QtConcurrent::run(this, &MainWindow::Ping,IP_List);
        while (BestIP=="")
        {
            QThread::msleep(500);
        }
        OutPut_List.append(BestIP+" "+WebSite+"\n");
    }
    emit Send_TestAndOutput_Fin();
}

void MainWindow::TestAndOutput_Fin()
{
    for(int i=0; i<OutPut_List.size(); i++)
    {
        ui->textBrowser_hosts->append(OutPut_List.at(i));
    }
    ui->pushButton_TestAndOutput->setEnabled(1);
}

void MainWindow::Ping(QStringList IP_List)
{
    QString BestIP_tmp = "";
    qint64 MinTimeCost = 9999999999;
    qint64 timeCost;
    for(int i=0; i<IP_List.size(); i++)
    {
        timeCost =0 ;
        QString IP = IP_List.at(i);
        IP = IP.trimmed();
        QProcess Ping_cmd;
        qint64 StartTime = QDateTime::currentMSecsSinceEpoch();
        Ping_cmd.start("ping "+IP);
        Ping_cmd.waitForStarted(10000);
        Ping_cmd.waitForFinished(10000);
        qint64 EndTime = QDateTime::currentMSecsSinceEpoch();
        timeCost = EndTime-StartTime;
        emit Send_TextBrowser_NewMSG("IP:["+IP+"]  耗时:["+QString::number(timeCost,10)+"]");
        if(timeCost<=MinTimeCost)
        {
            MinTimeCost= timeCost;
            BestIP_tmp = IP;
        }
    }
    BestIP = BestIP_tmp;
}

void MainWindow::TextBrowser_NewMSG(QString msg)
{
    ui->textBrowser_progress->append(msg);
}

void MainWindow::on_pushButton_CopyHosts_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    clip->setText(ui->textBrowser_hosts->toPlainText());
}
