#include "student.h"

Student::Student(QString name, int id)
{
    this->name = name;
    this->id = id;
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




