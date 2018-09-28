#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, QString barcodeID, QString studentID, QString status, QString time, QString date, QString cleanUp);

    QString getStudentID() const;
    void setStudentID(int value);



    QString getName() const;
    void setName(const QString &value);

    QTime getLastTimeSignIn() const;
    void setLastTimeSignIn();

    enum class Status {SIGNED_IN, CLEANING_UP, SIGNED_OUT};
    Status getStatus() const;
    void setStatus(Status value);

    QString getBarcodeID() const;
    void setBarcodeID(int value);

    QDate getLastDateSignIn() const;
    void setLastDateSignIn();

    QTime getLastTimeCleanUp() const;
    void setLastTimeCleanUp();

private:
    QString studentID;
    QString barcodeID;
    QString name;
    QTime lastTimeSignIn;
    QDate lastDateSignIn;
    QTime lastTimeCleanUp;
    Status status;

};

#endif // STUDENT_H
