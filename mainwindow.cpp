#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent,Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
    connect(ui->actionAdd_User,SIGNAL(triggered()),this,SLOT(addNewUser()));
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
    Student *currStudent = findStudent(name); //gets the student object
    
    name = currStudent->getName();  //really redundant fix soon please
    QString time = (QTime::currentTime().toString());
    QString date = QDate::currentDate().toString();
    
    if (!currStudent->isSignedIn())
    {   //if the user is not signed in
        
        currStudent->setSignedIn(true);   //sign him in
        ui->log->append("Signed in: " + name);
        currStudent->getLastSignIn()->start();  //and start the timer for how long he is there
        
        QFile file("data.csv");
        
        QFileInfo fileInfo("data.csv");
        //ui->log->append(fileInfo.absoluteFilePath());
        
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << name << "," << time <<"," << "Sign In," << date << "\r\n"; // this writes first line with two columns
            file.close();
        } else {
            ui->log->append("This shit don't work");
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
    }
    return 1;
    
}

QString MainWindow::findName(int id)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getStudentID() == id || this->students.at(i)->getBarcodeID() == id)
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
            return this->students.at(i)->getStudentID();
        }
    }
    return -1;
}

Student *MainWindow::findStudent(int id)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getStudentID() == id || this->students.at(i)->getBarcodeID() == id)
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
void MainWindow::addNewUser()
{
    QString name = QInputDialog::getText(this, tr("What is your name"),tr("Enter name:"), QLineEdit::Normal,"John Doe");
    QString id = QInputDialog::getText(this, tr("ID #"),tr("Enter school ID #:"), QLineEdit::Normal,"1234");
    QString barcode = QInputDialog::getText(this, tr("Barcode"),tr("Scan your barcode:"), QLineEdit::Normal,"");
    this->manager->addUser(name,id,barcode);
    this->students.append(new Student(name,barcode.toInt(),id.toInt()));
}
