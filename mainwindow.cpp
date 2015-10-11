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
//    QTimer *timer = new QTimer(this);   //make a timer which will call a method
//    connect(timer, SIGNAL(timeout()), this, SLOT(signAllOut()));    //connecting the timer with the method
//    timer->start(1000); //setting the timer to call the method every 1000 milliseconds or 1 second
    manager = new FileManager();
    this->students = manager->readIds();
    this->setWindowTitle("SFRT Attendance");
    this->setWindowIcon(QIcon("icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::callOther()    {
//    QTimer *autoTimer = new QTimer(this);
//    autoTimer->setInterval(5*1000);
//    autoTimer->setSingleShot(false);
//    connect(autoTimer, SIGNAL(timeout()), this, SLOT(signAllOut()));
//    autoTimer->start();
//}

/*signAllOut
 *
 * If the user forgets to sign out
 * then they will automatically be signed out
 * this method is called every second so as to
 * check for when the time limit is reached,
 * and when it reaches that limit, everyone is signed out.
 *
 * This time limit is something for which it would be unreasonable
 * for someone to stay until i.e. 3 A.M. for Saturdays and 7 P.M.
 * for Weekdays.
 */

//void MainWindow::signAllOut()   {
//    if (QDate::currentDate().dayOfWeek() == 7)    { //3 A.M. on Sunday, the day after Saturday meetings
//        if (QTime::currentTime() == QTime(3,0,0))   {
//            QFile ids("users.ids"); //open the users file because the status is saved there
//            QString text;   //make a string which will be used to rewrite the file

//            if (ids.open(QFile::ReadOnly|QFile::Text))   {  //only reading from the file right now
//                qDebug() << "Error when reading file";
//            }

//            QTextStream in(&ids);
//            while(!in.atEnd())  {   //keep reading the file until we get to the end
//                QString line = in.readLine();
//                if (line.section(';',3) == "Sign In")    {  //if the user is signed in
//                    text += line.section(';',0,2) + ";Sign Out\n";  //sign them out and append that to the text which will replace the file
//                    foreach (Student* stud, this->students)    {   //also go through all the students and if the name matches, change their status too
//                        if (stud->getName() == line.section(';',2,2))   {
//                            stud->setStatus(false);
//                        }
//                    }
//                } else  {   //otherwise just carry on and append
//                    text += line + "\n";
//                }
//            }

//            in.flush();
//            ids.close();    //closing so no glitches occur


//            if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))   {  //now writing to the file
//                qDebug() << "No File";
//            }


//            QTextStream out(&ids);
//            out << text;    //output the text which we collected and changed above

//            out.flush();
//            ids.close();
//        }
//    } else if (QDate::currentDate().dayOfWeek() != 6)   {   //7 P.M.on all Weekdays

//        /*NOTE
//         *
//         * Since doyOfWeek == 7 is coded for above,
//         * one does not need to include that as it
//         * will only move to this statement if the
//         * previous condition is not satisfied. On
//         * that note, saturdays do not have a forced
//         * sign out as it is on the sunday 3 A.M.;
//         * hence, for every day but saturday this
//         * condition will hold.
//         */

//        if (QTime::currentTime() == QTime(19,0,0))   {
//            QFile ids("users.ids"); //open the users file because the status is saved there
//            QString text;   //make a string which will be used to rewrite the file

//            if (ids.open(QFile::ReadOnly|QFile::Text))   {  //only reading from the file right now
//                qDebug() << "Error when reading file";
//            }

//            QTextStream in(&ids);
//            while(!in.atEnd())  {   //keep reading the file until we get to the end
//                QString line = in.readLine();
//                if (line.section(';',3) == "Sign In")    {  //if the user is signed in
//                    text += line.section(';',0,2) + ";Sign Out\n";  //sign them out and append that to the text which will replace the file
//                    foreach (Student* stud, this->students)    {   //also go through all the students and if the name matches, change their status too
//                        if (stud->getName() == line.section(';',2,2))   {
//                            stud->setStatus(false);
//                        }
//                    }
//                } else  {   //otherwise just carry on and append
//                    text += line + "\n";
//                }
//            }

//            in.flush();
//            ids.close();    //closing so no glitches occur


//            if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))   {  //now writing to the file
//                qDebug() << "No File";
//            }


//            QTextStream out(&ids);
//            out << text;    //output the text which we collected and changed above

//            out.flush();
//            ids.close();
//        }
//    }
//}

int MainWindow::gotText()
{
    Student *currStudent = findStudentFromId(ui->numberEntry->text()); //gets the student object
    ui->numberEntry->setText("");
    if(currStudent==NULL)
    {
        QSound::play("error.wav");
        ui->log->append("Invalid ID: Please try again");
        return 0;

    }
    QString time = (QTime::currentTime().toString());
    QString date = QDate::currentDate().toString();
    if(currStudent->getName()=="Daniel Grau")
        QSound::play("Yeah.wav");
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
        if (hours > 16) {
            ui->log->append("Signed out: " + currStudent->getName() + " || Duration: " +  QString::number(hours)+ ":" + QString::number(minutes) + ":" +  QString::number(seconds));  //display it to him
            currStudent->getLastSignIn()->restart();    //and restart the timer?
        
        
            QFile file("data.csv");
            if (file.open(QFile::WriteOnly|QFile::Append))
            {
                QTextStream stream(&file);
                stream << currStudent->getName() << ",1:00:00," << "Sign Out," << date << "\r\n"; // this writes first line with two columns
                file.close();
            }
            ui->numberEntry->setText(currStudent->getStudentID());
            gotText();
        }  else  {
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
        ui->log->append("Cancel was probably pressed at some point. Please try signing in again");
        QSound::play("error.wav");
    }
    else if (name == "John Doe" || id == "1234")
    {
        ui->log->append("An actual name and/or id wasn't entered. \"OK\" was pressed with the default value not changed");
        QSound::play("error.wav");
    }
    else if (checkExistingUser(name))
    {
        QSound::play("error.wav");
        QMessageBox msgBox;
        msgBox.setText("You are already part of the system. If you entered your ID or Barcode incorrectly, please talk to Daniel Grau or Sameer Vijay");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        ui->log->append("You are already part of the system. If you entered your ID or Barcode incorrectly, please talk to Daniel Grau or Sameer Vijay");
    }
    else
    {
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
