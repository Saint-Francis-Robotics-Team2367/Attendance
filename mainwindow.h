#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <filemanager.h>
#include <student.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QSound>
#include <qtimer.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);    /*{
        QTimer *timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(signAllOut()));
        timer->start(1000); //time specified in ms
    }*/

    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QList<Student*> students;
    QString findName(QString id);
    QString findId(QString &name);
    FileManager *manager;
    Student *findStudentFromId(QString id);
    Student *findStudentFromName(QString &name);
public slots:
//    void callOther();
//    void signAllOut();
    void addNewUser();
    int gotText();
    bool checkExistingUser(QString name);
};

#endif // MAINWINDOW_H
