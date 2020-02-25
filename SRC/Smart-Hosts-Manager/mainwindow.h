#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>
#include <QtConcurrent>
#include <QProcess>
#include <QTime>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //========================
    void Init_Table();
    int curRow=-1;
    QStandardItemModel *Table_model = new QStandardItemModel();
    QString BestIP ="";
    void Ping(QStringList IP_List);
    void TestAndOutput();
    QStringList OutPut_List;

    //========================
    ~MainWindow();

private slots:
    void on_pushButton_AddWebSite_clicked();

    void on_pushButton_AddIP_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_TestAndOutput_clicked();

    void on_pushButton_CopyHosts_clicked();

signals:
    void Send_TestAndOutput_Fin();
    void Send_TextBrowser_NewMSG(QString msg);

public slots:
    void TestAndOutput_Fin();
    void TextBrowser_NewMSG(QString msg);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
