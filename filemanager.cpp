#include "filemanager.h"

FileManager::FileManager()
{

}
QList<Student*> FileManager::readIds()
{
    QFile ids("users.ids");
    QList<Student*> students;
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
        QString studentID = line.section(' ',0,0);
        qDebug() << studentID;
        QString barcodeID = line.section(' ',1,1);
        qDebug() << barcodeID;
        QString name = line.section(' ',2);
        qDebug() << name;
        students.append(new Student(name,barcodeID.toInt(), studentID.toInt()));
    }
    in.flush();
    ids.close();
    return students;
}
void FileManager::changeStatus(QString name)
{
    QList<QString> rawFile;
    QFile log("attendance.log");
    if(!log.exists())
    {
        qDebug() << "File does not exist\nCreating...";
        log.open(QIODevice::ReadWrite | QIODevice::Text);
        log.flush();
        log.close();
    }
    if(!log.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream logData(&log);
    while(!logData.atEnd())
    {
        rawFile.append(logData.readLine());

    }
    logData.flush();
    log.close();
    bool foundName = false;
    int days;
    for(int i = 0;i<rawFile.size();i++)
    {
        QStringList lineParts = rawFile.at(i).split(";",QString::SkipEmptyParts);
        if(name==lineParts.at(0))
        {
            foundName = true;
            days = lineParts.at(1).toInt()+1;
            QString newName = name +";"+QString::number(days);
            rawFile.replace(i,newName);
        }
    }
    if(!foundName)
    {
        rawFile.append(name + ";1");
    }
    if(!log.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
    }
    QTextStream out(&log);
    for(int i = 0;i<rawFile.size();i++)
    {
        out << rawFile.at(i) +"\n";
    }
    out.flush();
    log.close();
}

void FileManager::addUser(QString name, QString id)
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
    rawText.append(id +" " +name);
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
