#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
    FileManager *manager = new FileManager();
    this->students = manager->readIds();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::gotText()
{
    qDebug() << ui->numberEntry->text();
    qDebug() << this->findName(ui->numberEntry->text().toInt());
    ui->numberEntry->setText("");
}
QString MainWindow::findName(int id)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i).getId()==id)
        {
            return this->students.at(i).getName();
        }
    }
    return NULL;
}
int MainWindow::findId(QString &name)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i).getName()==name)
        {
            return this->students.at(i).getId();
        }
    }
    return -1;
}
