#include "student.h"

Student::Student(QString name, QString barcodeID, QString studentID)
{
    this->name = name;
    this->barcodeID = barcodeID;
    this->studentID = studentID;

    this->isSignIn = false;    //a new Student is not signed in when he is added
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
QTime *Student::getLastSignIn()
{
    return &lastSignIn;
}
bool Student::isSignedIn() const
{
    return isSignIn;
}

void Student::setSignedIn(bool value)
{
    isSignIn = value;
}


QString Student::getBarcodeID() const
{
    return barcodeID;
}

void Student::setBarcodeID(int value)
{
    barcodeID = value;
}

