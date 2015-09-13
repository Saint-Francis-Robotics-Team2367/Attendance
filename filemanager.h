#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QDebug>
#include <student.h>
#include <QDir>
class FileManager
{
public:
    FileManager();
    QList<Student*> readIds();
    void changeStatus(QString name);
private:
    QFile *ids;
};

#endif // FILEMANAGER_H
