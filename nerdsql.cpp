#include "nerdsql.h"
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>

using namespace std;

NerdSQL::NerdSQL()
{

}

std::vector<Nerd> NerdSQL::getAllScientists()
{
    vector<Nerd> ComputerScientists;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    query.prepare("SELECT * FROM People");
    query.bindValue("Name", QString::fromStdString("*"));

    query.exec();

    while(query.next()){
        string name = query.value("Name").toString().toStdString();
        string gender = query.value("Gender").toString().toStdString();
        sexType sex;
        if (gender == "male")
            sex = male;
        else
            sex = female;
        int born = query.value("YearBorn").toInt();
        int dead = query.value("YearDeath").toInt();

        Nerd scientist(name, sex, born, dead);

        ComputerScientists.push_back(scientist);
    }

    db.close();

    return ComputerScientists;
}

std::vector<Computer> NerdSQL::getAllComputers()
{
    vector<Computer> Computers;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    query.prepare("SELECT * FROM Computers");
    query.bindValue("Name", QString::fromStdString("*"));

    query.exec();

    while(query.next()){
        string name = query.value("Name").toString().toStdString();
        string yearBuilt = query.value("YearBuilt").toString().toStdString();
        string type = query.value("Type").toString().toStdString();
        bool made = query.value("Made").toBool();


        Computer pc(name, yearBuilt, type, made);

        Computers.push_back(pc);
    }

    db.close();

    return Computers;}

std::vector<Nerd> NerdSQL::searchForScientists(std::string searchTerm)
{
    vector<Nerd> allNerds = getAllScientists();

    return allNerds;
}

bool NerdSQL::addScientist(Nerd nerd)
{
    return true;
}

bool NerdSQL::addComputer(Computer computer)
{
    return true;
}

