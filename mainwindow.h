#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <filemanager.h>
#include <student.h>

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
    QList<Student> students;
    QString findName(int id);
    int findId(QString &name);
    FileManager *manager;
public slots:
    void gotText();
};

#endif // MAINWINDOW_H
