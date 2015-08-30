#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
    connect(ui->actionNewUser,SIGNAL(triggered(bool)),this,SLOT(newUser()));
    manager = new FileManager();
    this->students = manager->readIds();
    this->setWindowTitle("SFRT Attendance");
    this->setWindowIcon(QIcon("icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::gotText()
{
    QString name = this->findName(ui->numberEntry->text().toInt());

    ui->numberEntry->setText("");
    if(name==NULL)
    {
        ui->log->append("Invalid ID: Please try again");
        return 0;

    }
    Student *currStudent = findStudent(name);
    if(currStudent->getLastSignIn()->elapsed()==0 || (currStudent->getCorrectSignIn() && currStudent->getLastSignIn()->elapsed()>57600000))
    {
        currStudent->setCorrectSignOut(false);
        ui->log->append("Signed in: " + name);
        currStudent->getLastSignIn()->start();
    }
    else if(!currStudent->getCorrectSignIn() && currStudent->getLastSignIn()->elapsed()>57600000)//57600000
    {
        currStudent->setCorrectSignOut(false);
        ui->log->append("You did not sign-out last time, resigning-in");
        ui->log->append("Signed in: " + name);
        currStudent->getLastSignIn()->restart();
    }

    else if(currStudent->getLastSignIn()->elapsed()<5400000)//5400000
    {
        int elapsed = currStudent->getLastSignIn()->elapsed();
        int seconds = (int) (elapsed / 1000) % 60 ;
        int minutes = (int) ((elapsed / (1000*60)) % 60);
        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        ui->log->append("Signed out: " + name + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));
        currStudent->getLastSignIn()->restart();

        QString name = currStudent->getName();
        QString signIN = currStudent->getLastSignIn()->toString();
        QString signOUT = (QTime::currentTime().toString());
        //int date = (const int QDate::month());
        QString s = QDate::currentDate().toString();
        QFile file("data.csv");
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
        QTextStream stream(&file);
        stream << name << "," << signIN << "," << signOUT <<"," << s << "\r\n"; // this writes first line with two columns
        file.close();
    }
    else if(currStudent->getLastSignIn()->elapsed()>5400000)
    {
        currStudent->setCorrectSignOut(true);
        int elapsed = currStudent->getLastSignIn()->elapsed();
        int seconds = (int) (elapsed / 1000) % 60 ;
        int minutes = (int) ((elapsed / (1000*60)) % 60);
        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        ui->log->append("Signed out: " + name + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));
        currStudent->getLastSignIn()->restart();
        this->manager->changeStatus(name);        
    }
    return 1;



    }
}

QString MainWindow::findName(int id)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getId()==id)
        {
            return this->students.at(i)->getName();
        }
    }
    return NULL;
}
int MainWindow::findId(QString &name)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getName()==name)
        {
            return this->students.at(i)->getId();
        }
    }
    return -1;
}
Student *MainWindow::findStudent(int id)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getId()==id)
        {
            return (this->students.at(i));
        }
    }
}
Student *MainWindow::findStudent(QString &name)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getName()==name)
        {
            return (this->students.at(i));
        }
    }
}
void MainWindow::newUser()
{
    QString name = QInputDialog::getText(this, tr("What is your name"),tr("Name:"), QLineEdit::Normal,"John Doe");
    QString id = QInputDialog::getText(this, tr("What is your id #"),tr("Id #:"), QLineEdit::Normal,"1234");
    this->manager->addUser(name,id);
    this->students.append(new Student(name,id.toInt()));
}
