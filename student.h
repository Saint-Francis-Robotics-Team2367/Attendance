#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, QString barcodeID, QString studentID, QString status);

    QString getStudentID() const;
    void setStudentID(int value);



    QString getName() const;
    void setName(const QString &value);

    QTime *getLastSignIn();

    bool getStatus() const;
    void setStatus(bool value);

    QString getBarcodeID() const;
    void setBarcodeID(int value);

private:
    QString studentID;
    QString barcodeID;
    QString name;
    QTime lastSignIn;
    bool status;

};

#endif // STUDENT_H
