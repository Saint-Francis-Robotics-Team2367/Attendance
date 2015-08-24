#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::gotText()
{
    qDebug() << ui->numberEntry->text();
    ui->numberEntry->setText("");
}
