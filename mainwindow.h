#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <filemanager.h>
#include <student.h>
#include <QInputDialog>

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
    QString findName(int id);
    int findId(QString &name);
    FileManager *manager;
    Student *findStudent(int id);
    Student *findStudent(QString &name);
public slots:
    void addNewUser();
    int gotText();
};

#endif // MAINWINDOW_H
