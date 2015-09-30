#include "filemanager.h"

FileManager::FileManager()
{
    ids = new QFile("users.ids");
}
QList<Student*> FileManager::readIds()
{
    
    QList<Student*> students;
    if(!ids->exists())
    {
        qDebug() << "File does not exist\nCreating...";
        ids->open(QIODevice::ReadWrite | QIODevice::Text);
        ids->flush();
        ids->close();
    }
    if(!ids->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream in(ids);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QString studentID = line.section(';',0,0);
        qDebug() << studentID;
        QString barcodeID = line.section(';',1,1);
        qDebug() << barcodeID;
        QString name = line.section(';',2);
        qDebug() << name;
        students.append(new Student(name,barcodeID.toInt(), studentID.toInt()));
    }
    in.flush();
    ids->close();
    return students;
}

void FileManager::addUser(QString name, QString id, QString barcodeNum)
{
    QFile ids("users.ids");
    QStringList rawText;
    if(!ids.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream in(&ids);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        rawText.append(line);
    }
    in.flush();
    ids.close();
    rawText.append(id +";" + barcodeNum + ";"+name);
    if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    qDebug() << "Can't open file";
    }

    QTextStream out(&ids);
    for(int i = 0;i<rawText.size();i++)
    {
    out << rawText.at(i) +"\n";
    }
    out.flush();
    ids.close();
}

