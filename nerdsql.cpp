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

std::vector<Nerd> NerdSQL::getAllScientists(std::string orderBy, bool orderAscending)
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
        string yearBorn = query.value("yearBorn").toString().toStdString();
        string yearDeath = query.value("yearDeath").toString().toStdString();

        Nerd scientist(name, gender, yearBorn, yearDeath);

        ComputerScientists.push_back(scientist);
    }

    db.close();

    return ComputerScientists;
}

std::vector<Computer> NerdSQL::getAllComputers(std::string orderBy, bool orderAscending)
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

    return Computers;
}

std::vector<Nerd> NerdSQL::searchForScientists(std::string searchTerm)
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
        string yearBorn = query.value("yearBorn").toString().toStdString();
        string yearDeath = query.value("yearDeath").toString().toStdString();

        Nerd scientist(name, gender, yearBorn, yearDeath);

        ComputerScientists.push_back(scientist);
    }

    db.close();

    return ComputerScientists;
}

bool NerdSQL::addScientist(Nerd nerd)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query;

    string name = nerd.getName();
    string gender = nerd.getSex();
    string yearBorn = nerd.getYearBorn();
    string yearDeath = nerd.getYearDied();

    query.prepare("INSERT INTO People(Name, Gender, YearBorn, YearDeath) "
                  "VALUES (:Name, :Gender, :YearBorn, :YearDeath)");
    query.bindValue(":Name", QString::fromStdString(name));
    query.bindValue(":Gender", QString::fromStdString(gender));
    query.bindValue(":YearBorn", QString::fromStdString(yearBorn));
    query.bindValue(":YearDeath", QString::fromStdString(yearDeath));
    query.exec();
    db.close();

    return true;
}

bool NerdSQL::addComputer(Computer computer)
{
    return true;
}

