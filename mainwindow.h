#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <filemanager.h>
#include <student.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QSound>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
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
    void addNewUser();
    int gotText();
    bool checkExistingUser(QString name);
};

#endif // MAINWINDOW_H
