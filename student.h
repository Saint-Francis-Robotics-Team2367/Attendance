#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
class Student
{
public:
    Student(QString name, int id);

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

private:
    int id;
    QString name;
};

#endif // STUDENT_H
