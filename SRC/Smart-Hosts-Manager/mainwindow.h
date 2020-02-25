/*
    Copyright (C) 2020  Aaron Feng

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    My Github homepage: https://github.com/AaronFeng753
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>
#include <QtConcurrent>
#include <QProcess>
#include <QTime>
#include <QClipboard>
#include <QDesktopServices>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFuture>

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
    void Ping(QString WebSite,QStringList IP_List);
    void TestAndOutput();
    QStringList OutPut_List;
    QString Current_Path = qApp->applicationDirPath();//当前路径
    void closeEvent(QCloseEvent* event);//关闭事件,包含所有关闭时执行的代码
    int Force_close();
    QFuture<void> Ping_MAIN;//监视自动ping调度线程
    //========================
    ~MainWindow();

private slots:
    void on_pushButton_AddWebSite_clicked();

    void on_pushButton_AddIP_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_TestAndOutput_clicked();

    void on_pushButton_CopyHosts_clicked();

    void on_pushButton_GetIP_clicked();

    void on_pushButton_ClearList_clicked();

    void on_pushButton_checkUpdate_clicked();

    void on_pushButton_OfficalWebSite_clicked();

    void on_pushButton_SaveList_clicked();

    void on_pushButton_ReadList_clicked();

    void on_pushButton_DeleteItem_clicked();

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
