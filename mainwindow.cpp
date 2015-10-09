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
    Student *currStudent = findStudentFromId(ui->numberEntry->text()); //gets the student object
    ui->numberEntry->setText("");
    if(currStudent==NULL)
    {
        ui->textBrowserErrors->append("Invalid ID: Please try again");
        return 0;

    }
    QString time = (QTime::currentTime().toString());
    QString date = QDate::currentDate().toString();
    
    if (!currStudent->getStatus())
    {   //if the user is not signed in
        
        currStudent->setStatus(true);   //sign him in
        ui->log->append("Signed in: " + currStudent->getName());
        currStudent->getLastSignIn()->start();  //and start the timer for how long he is there




        QFile file("data.csv");
        
        //QFileInfo fileInfo("data.csv");
        //ui->log->append(fileInfo.absoluteFilePath());
        
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << currStudent->getName() << "," << time <<"," << "Sign In," << date << "\r\n"; // this writes first line with two columns
            file.close();
        } else {
            ui->log->append("FREAKING A");
        }
        
    }
    else if (currStudent->getStatus()) {   //if the user is signed in
        
        currStudent->setStatus(false);  //sign him out
        int elapsed = currStudent->getLastSignIn()->elapsed();  //magically get the numbers for how long he has been there
        int seconds = (int) (elapsed / 1000) % 60 ;
        int minutes = (int) ((elapsed / (1000*60)) % 60);
        int hours   = (int) ((elapsed / (1000*60*60)) % 24);
        ui->log->append("Signed out: " + currStudent->getName() + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));  //display it to him
        currStudent->getLastSignIn()->restart();    //and restart the timer?
        
        
        QFile file("data.csv");
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << currStudent->getName() << "," << time <<"," << "Sign Out," << date << "\r\n"; // this writes first line with two columns
            file.close();
        }
    }

    QFile ids("users.ids");
    QStringList rawText;
    if(!ids.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream in(&ids);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if (currStudent->getName() == line.section(';',2,2))    {
            if (currStudent->getStatus() == true)   {
                rawText.append(line.section(';',0,2) + ";Sign In");
            }   else    {
                rawText.append(line.section(';',0,2) + ";Sign Out");
            }
        }   else    {
            rawText.append(line);
        }
    }
    in.flush();
    ids.close();
    if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    qDebug() << "Can't open file";
    }

    QTextStream out(&ids);
    for(int i = 0;i<rawText.size();i++)
    {
    out << rawText.at(i) +"\n";
    }
    out.flush();
    ids.close();

    return 1;
    
}

QString MainWindow::findName(QString id)
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
QString MainWindow::findId(QString &name)
{
    for(int i = 0;i<this->students.size();i++)
    {
        if(this->students.at(i)->getName()==name)
        {
            return this->students.at(i)->getStudentID();
        }
    }
    return NULL;
}

Student *MainWindow::findStudentFromId(QString id)
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
Student *MainWindow::findStudentFromName(QString &name) //looks through array to find the student and returns the Student object
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
    if (name.isEmpty() || id.isEmpty() || barcode.isEmpty()) {
        ui->textBrowserErrors->append("Cancel was probably pressed at some point. Please try signing in again");
    } else if (name == "John Doe" || id == "1234") {
        ui->textBrowserErrors->append("An actual name and/or id wasn't entered. \"OK\" was pressed with the default value not changed");
    }   else if (checkExistingUser(name))   {
        ui->textBrowserErrors->append("You are already part of the system. If you entered your ID or Barcode incorrectly, please talk to Daniel Grau or Sameer Vijay");
    } else {
        this->manager->addUser(name,id,barcode);
        this->students.append(new Student(name,barcode,id,"Sign Out"));
    }
}

bool MainWindow::checkExistingUser(QString name)    {
    bool cont = false;
    for (int i = 0; i < this->students.size(); i++) {
        if (name == this->students.at(i)->getName()) cont = true;
    }
    return cont;
}
