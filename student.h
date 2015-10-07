#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, QString barcodeID, QString studentID);

    QString getStudentID() const;
    void setStudentID(int value);



    QString getName() const;
    void setName(const QString &value);

    QTime *getLastSignIn();

    bool isSignedIn() const;
    void setSignedIn(bool value);

    QString getBarcodeID() const;
    void setBarcodeID(int value);

private:
    QString studentID;
    QString barcodeID;
    QString name;
    QTime lastSignIn;
    bool isSignIn;

};

#endif // STUDENT_H
