#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QDebug>
#include <student.h>

class FileManager
{
public:
    FileManager();
    QList<Student> readIds();
private:
};

#endif // FILEMANAGER_H
