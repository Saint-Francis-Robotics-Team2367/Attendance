#include "student.h"

Student::Student(QString name, int barcodeID, int studentID)
{
    this->name = name;
    this->barcodeID = barcodeID;
    this->studentID = studentID;

    this->isSignIn = false;    //a new Student is not signed in when he is added
}
int Student::getStudentID() const
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


int Student::getBarcodeID() const
{
    return barcodeID;
}

void Student::setBarcodeID(int value)
{
    barcodeID = value;
}

