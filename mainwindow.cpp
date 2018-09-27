#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <qtimer.h>
#include <qdatetime.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent,Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->numberEntry,SIGNAL(returnPressed()),this,SLOT(gotText()));
    connect(ui->actionAdd_User,SIGNAL(triggered()),this,SLOT(addNewUser()));
    //QTimer *timer = new QTimer(this);   //make a timer which will call a method
    //connect(timer, SIGNAL(timeout()), this, SLOT(signAllOut()));    //connecting the timer with the method
    //timer->start(1000); //setting the timer to call the method every 1000 milliseconds or 1 second
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

    if(currStudent==NULL)   {
        QSound::play("error.wav");
        ui->log->append("Invalid ID: Please try again");
        return 0;
    }

    QString time = QTime::currentTime().toString();
    //QString date = QDate::currentDate().toString();

    if (!(currStudent->getStatus() == Student::Status::SIGNED_IN))
    {   //if the user is not signed in
        
        currStudent->setLastDateSignIn();

        currStudent->setStatus(Student::Status::SIGNED_IN);   //sign him in

        ui->log->append("Signed in: " + currStudent->getName());

        currStudent->setLastTimeSignIn();  //and start the timer for how long he is there

        QFile file("data.csv");
        
        //QFileInfo fileInfo("data.csv");
        //ui->log->append(fileInfo.absoluteFilePath());
        
        if (file.open(QFile::WriteOnly|QFile::Append))
        {
            QTextStream stream(&file);
            stream << currStudent->getName() << "," << time <<"," << "Sign In," << currStudent->getLastDateSignIn().toString() << "\r\n"; // this writes first line with two columns
            file.close();
        }

        else {
            ui->log->append("Error in opening data.csv!");
        }
        
    }

    else if (currStudent->getStatus() == Student::Status::SIGNED_IN) {   //if the user is signed in

        currStudent->setStatus(Student::Status::SIGNED_OUT);  //sign him out

        //int elapsed = currStudent->getLastTimeSignIn().elapsed();  //magically get the numbers for how long he has been there
        int elapsed = currStudent->getLastTimeSignIn().secsTo(QTime::currentTime()) + (24 * 60 * 60 * currStudent->getLastDateSignIn().daysTo(QDate::currentDate()));

        int seconds = elapsed % 60 ;
        int minutes = (int) ((elapsed / 60) % 60);
        int hours   = (int) ((elapsed / (60 * 60) ) % 24);
        if(currStudent->getLastDateSignIn().daysTo(QDate::currentDate())>=1)
         {
            ui->log->append("Signed out: " + currStudent->getName() + " || Duration: 0:00:00");  //display it to him

            ui->log->append("Next Time Remember to Sign Out");

            QTime realTime = currStudent->getLastTimeSignIn();

            QFile file("data.csv");

            if (file.open(QFile::WriteOnly|QFile::Append))  {
                QTextStream stream(&file);

                if (realTime.hour() == 23)  {   //if they signed in at 23:00 or later, then set the time to an hour on the next day
                    stream << currStudent->getName() << "," + realTime.addSecs(60*60).toString() + "," << "Sign Out," << currStudent->getLastDateSignIn().addDays(1).toString() << "\r\n"; // this writes first line with two columns
                }

                else    {   //otherwise just increment an hour on the same day
                    stream << currStudent->getName() << "," + realTime.addSecs(60*60).toString() + "," << "Sign Out," << currStudent->getLastDateSignIn().toString() << "\r\n"; // this writes first line with two columns
                }
                file.close();
            }
            ui->numberEntry->setText(currStudent->getStudentID());

            gotText();  //call the function again to sign them in automatically

        }

        else  {
            QString hoursString, minutesString, secondsString;

            if (QString::number(hours).length() == 1)   {
                hoursString = "0" + QString::number(hours);
            } else {
                hoursString = QString::number(hours);
            }

            if (QString::number(minutes).length() == 1)   {
                minutesString = "0" + QString::number(minutes);
            } else {
                minutesString = QString::number(minutes);
            }

            if (QString::number(seconds).length() == 1)   {
                secondsString = "0" + QString::number(seconds);
            } else {
                secondsString = QString::number(seconds);
            }
            ui->log->append("Signed out: " + currStudent->getName() + " || Duration: " +  hoursString + ":" + minutesString + ":" +  secondsString);  //display it to him

            currStudent->setLastTimeSignIn();    //and restart the timer

            currStudent->setLastDateSignIn();   //reset the date

            QFile file("data.csv");

            if (file.open(QFile::WriteOnly|QFile::Append))
            {
                QTextStream stream(&file);
                stream << currStudent->getName() << "," << time <<"," << "Sign Out," << currStudent->getLastDateSignIn().toString() << "\r\n"; // this writes first line with two columns
                file.close();
            }

        }

    }

    QFile ids("users.ids");
    QStringList rawText;
    if(!ids.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream in(&ids);
    while(!in.atEnd())  {
        QString line = in.readLine();

        if (currStudent->getName() == line.section(';',2,2))    {

            if (currStudent->getStatus() == Student::Status::SIGNED_IN)   {
                rawText.append(line.section(';',0,2) + ";Sign In;" + currStudent->getLastTimeSignIn().toString() + ";" + currStudent->getLastDateSignIn().toString());
            }   else    {
                rawText.append(line.section(';',0,2) + ";Sign Out;" + currStudent->getLastTimeSignIn().toString() + ";" + currStudent->getLastDateSignIn().toString());
            }

        }

        else    {
            rawText.append(line);
        }

    }

    in.flush();
    ids.close();

    if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))   {
        qDebug() << "Can't open file";
    }

    QTextStream out(&ids);

    for(int i = 0;i<rawText.size();i++) {
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
    QString barcode = QInputDialog::getText(this, tr("Barcode"),tr("Scan your barcode or press enter if no barcode:"), QLineEdit::Normal,"");

    if (name.isEmpty() || id.isEmpty() || barcode.isEmpty()) {
        ui->log->append("Cancel was probably pressed at some point. Please try signing in again");
        QSound::play("error.wav");
    }

    else if (name == "John Doe" || id == "1234")    {
        ui->log->append("An actual name and/or id wasn't entered. \"OK\" was pressed with the default value not changed");
        QSound::play("error.wav");
    }

    else if (checkExistingUser(name))   {
        QSound::play("error.wav");
        QMessageBox msgBox;
        msgBox.setText("You are already part of the system. If you entered your ID or Barcode incorrectly, please talk to a board member or moderator");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        ui->log->append("You are already part of the system. If you entered your ID or Barcode incorrectly, please talk to a board member or moderator");
    }

    else    {
        this->manager->addUser(name,id,barcode);
        this->students.append(new Student(name, barcode, id, "Sign Out", QTime::currentTime().toString(), QDate::currentDate().toString()));
    }

}

bool MainWindow::checkExistingUser(QString name)    {
    bool cont = false;
    for (int i = 0; i < this->students.size(); i++) {
        if (name == this->students.at(i)->getName()) cont = true;
    }
    return cont;
}
