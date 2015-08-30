#include "student.h"

Student::Student(QString name, int id)
{
    this->name = name;
    this->id = id;

    this->isSignIn = false;    //a new Student is not signed in when he is added
}
int Student::getId() const
{
    return id;
}

void Student::setId(int value)
{
    id = value;
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
