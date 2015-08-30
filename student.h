#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, int id);

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    QTime *getLastSignIn();

    bool getCorrectSignIn() const;
    void setCorrectSignOut(bool value);

private:
    int id;
    QString name;
    QTime lastSignIn;
    bool correctSignIn;

};

#endif // STUDENT_H
