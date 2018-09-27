#include "student.h"

Student::Student(QString name, QString barcodeID, QString studentID, QString status, QString time, QString date)
{
    this->name = name;
    this->barcodeID = barcodeID;
    this->studentID = studentID;

    if (status == "Sign In") this->status = Student::Status::SIGNED_IN;
    if(status == "Clean Up") this->status = Student::Status::CLEANING_UP;
    else this->status = Student::Status::SIGNED_OUT;

    this->lastTimeSignIn = QTime::fromString(time);
    this->lastDateSignIn = QDate::fromString(date);
}

QString Student::getStudentID() const
{
    return studentID;
}

void Student::setStudentID(int value)
{
    studentID = value;
}

QString Student::getName() const
{
    return name;
}

void Student::setName(const QString &value)
{
    name = value;
}
QTime Student::getLastTimeSignIn()
{
    return lastTimeSignIn;
}

void Student::setLastTimeSignIn()   {
    lastTimeSignIn.start();
}

Student::Status Student::getStatus() const
{
    return status;
}

void Student::setStatus(Student::Status value)
{
    status = value;
}


QString Student::getBarcodeID() const
{
    return barcodeID;
}

void Student::setBarcodeID(int value)
{
    barcodeID = value;
}
QDate Student::getLastDateSignIn() const
{
    return lastDateSignIn;
}

void Student::setLastDateSignIn()
{
    lastDateSignIn = QDate::currentDate();
}


