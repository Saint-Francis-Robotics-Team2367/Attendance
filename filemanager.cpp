#include "filemanager.h"

FileManager::FileManager()
{

}
QList<Student> FileManager::readIds()
{
    QFile ids("users.ids");
    QList<Student> students;
    if(!ids.exists())
    {
        qDebug() << "File does not exist\nCreating...";
        ids.open(QIODevice::ReadWrite | QIODevice::Text);
        ids.flush();
        ids.close();
    }
    if(!ids.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream in(&ids);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QString id = line.section(' ',0,0);
        qDebug() << id;
        QString name = line.section(' ',1);
        qDebug() << name;
        students.append(Student(name,id.toInt()));
    }
    in.flush();
    ids.close();
    return students;
}
