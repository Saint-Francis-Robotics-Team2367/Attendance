#include "filemanager.h"

FileManager::FileManager()  {
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

    if(!ids->open(QIODevice::ReadOnly | QIODevice::Text))   {
        qDebug() << "Can't open file";
    }

    QTextStream in(ids);

    while(!in.atEnd())  {
        QString line = in.readLine();

        QString studentID = line.section(';',0,0);
        QString barcodeID = line.section(';',1,1);
        QString name = line.section(';',2,2);
        QString status = line.section(';',3,3);
        QString time = line.section(';',4,4);
        QString date = line.section(';',5,5);
        QString cleanUp = line.section(';',6);

        students.append(new Student(name,barcodeID, studentID,status,time,date, cleanUp));
    }

    in.flush();
    ids->close();

    return students;
}

void FileManager::addUser(QString name, QString id, QString barcodeNum) {
    QFile ids("users.ids");

    QStringList rawText;

    if(!ids.open(QIODevice::ReadOnly | QIODevice::Text))    {
        qDebug() << "Can't open file";
    }

    QTextStream in(&ids);

    while(!in.atEnd())  {
        QString line = in.readLine();

        rawText.append(line);
    }

    in.flush();
    ids.close();

    rawText.append(id +";" + barcodeNum + ";"+ name + ";" + "Sign Out;" + QTime::currentTime().toString() + ";" + QDate::currentDate().toString() + ";"  + QTime::currentTime().toString());     //in the add user put their id, then barcode, then name and then status

    if(!ids.open(QIODevice::WriteOnly | QIODevice::Text))   {
        qDebug() << "Can't open file";
    }

    QTextStream out(&ids);

    for(int i = 0;i<rawText.size();i++) {
        out << rawText.at(i) +"\n";
    }

    out.flush();
    ids.close();
}

