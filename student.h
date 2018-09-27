#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, QString barcodeID, QString studentID, QString status, QString time, QString date);

    QString getStudentID() const;
    void setStudentID(int value);



    QString getName() const;
    void setName(const QString &value);

    QTime getLastTimeSignIn();
    void setLastTimeSignIn();

    enum class Status {SIGNED_IN, CLEANING_UP, SIGNED_OUT};
    Status getStatus() const;
    void setStatus(Status value);

    QString getBarcodeID() const;
    void setBarcodeID(int value);

    QDate getLastDateSignIn() const;
    void setLastDateSignIn();

private:
    QString studentID;
    QString barcodeID;
    QString name;
    QTime lastTimeSignIn;
    QDate lastDateSignIn;
    Status status;

};

#endif // STUDENT_H
