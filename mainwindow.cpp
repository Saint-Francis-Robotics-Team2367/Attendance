#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
    // connect(ui->actionNewUser,SIGNAL(triggered(bool)),this,SLOT(newUser()));
    manager = new FileManager();
    this->students = manager->readIds();
    this->setWindowTitle("SFRT Attendance");
    this->setWindowIcon(QIcon("icon.png"));

    //code for testing because i cannot manually add users
    students.append(new Student("Nilay Pachauri",2171048));
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
    Student *currStudent = findStudent(name); //gets the student object

    QString name = currStudent->getName();
    QString time = (QTime::currentTime().toString());
    //int date = (const int QDate::month());
    QString date = QDate::currentDate().toString();

    if (!currStudent->isSignedIn())
    {   //if the user is not signed in

        currStudent->setSignedIn(true);   //sign him in
        ui->log->append("Signed in: " + name);
        currStudent->getLastSignIn()->start();  //and start the timer for how long he is there

        QFile file("data.csv");
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << name << "," << time <<"," << "Sign In," << date << "\r\n"; // this writes first line with two columns
            file.close();
        }

    }
    else if (currStudent->isSignedIn()) {   //if the user is signed in

        currStudent->setSignedIn(false);  //sign him out
        int elapsed = currStudent->getLastSignIn()->elapsed();  //magically get the numbers for how long he has been there
        int seconds = (int) (elapsed / 1000) % 60 ;
        int minutes = (int) ((elapsed / (1000*60)) % 60);
        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        ui->log->append("Signed out: " + name + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));  //display it to him
        currStudent->getLastSignIn()->restart();    //and restart the timer?


        QFile file("data.csv");
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << name << "," << time <<"," << "Sign Out," << date << "\r\n"; // this writes first line with two columns
            file.close();
        }

        //if(currStudent->getLastSignIn()->elapsed()==0 || (currStudent->getCorrectSignIn() && currStudent->getLastSignIn()->elapsed()>57600000))
        //    {
        //        currStudent->setCorrectSignOut(false);
        //        ui->log->append("Signed in: " + name);
        //        currStudent->getLastSignIn()->start();
        //    }
        //    else if(!currStudent->getCorrectSignIn() && currStudent->getLastSignIn()->elapsed()>57600000)//57600000 //16 hours in millesonds
        //    {
        //        currStudent->setCorrectSignOut(false);
        //        ui->log->append("You did not sign-out last time, resigning-in");
        //        ui->log->append("Signed in: " + name);
        //        currStudent->getLastSignIn()->restart();
        //    }

        //    else if(currStudent->getLastSignIn()->elapsed()<5400000)//5400000   //1 hour 30 minutes in seconds
        //    {
        //        int elapsed = currStudent->getLastSignIn()->elapsed();
        //        int seconds = (int) (elapsed / 1000) % 60 ;
        //        int minutes = (int) ((elapsed / (1000*60)) % 60);
        //        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        //        ui->log->append("Signed out: " + name + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));
        //        currStudent->getLastSignIn()->restart();
        //    }
        //    else if(currStudent->getLastSignIn()->elapsed()>5400000)
        //    {
        //        currStudent->setCorrectSignOut(true);
        //        int elapsed = currStudent->getLastSignIn()->elapsed();
        //        int seconds = (int) (elapsed / 1000) % 60 ;
        //        int minutes = (int) ((elapsed / (1000*60)) % 60);
        //        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        //        ui->log->append("Signed out: " + name + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));
        //        currStudent->getLastSignIn()->restart();
        //        this->manager->changeStatus(name);
        //    }
    }
    return 1;

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
    return (Student *)NULL;
}
Student *MainWindow::findStudent(QString &name) //looks through array to find the student and returns the Student object
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getName()==name)
        {
            return (this->students.at(i));
        }
    }
    return (Student *)NULL;
}
void MainWindow::newUser()
{
    QString name = QInputDialog::getText(this, tr("What is your name"),tr("Name:"), QLineEdit::Normal,"John Doe");
    QString id = QInputDialog::getText(this, tr("What is your id #"),tr("Id #:"), QLineEdit::Normal,"1234");
    this->manager->addUser(name,id);
    this->students.append(new Student(name,id.toInt()));
}
