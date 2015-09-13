#ifndef STUDENT_H
#define STUDENT_H
#include <QObject>
#include <QTime>
class Student
{
public:
    Student(QString name, int barcodeID, int studentID);

    int getStudentID() const;
    void setStudentID(int value);



    QString getName() const;
    void setName(const QString &value);

    QTime *getLastSignIn();

    bool isSignedIn() const;
    void setSignedIn(bool value);

    int getBarcodeID() const;
    void setBarcodeID(int value);

private:
    int studentID;
    int barcodeID;
    QString name;
    QTime lastSignIn;
    bool isSignIn;

};

#endif // STUDENT_H
