#include "nerdsql.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <iostream>

using namespace std;

NerdSQL::NerdSQL()
{
}

void NerdSQL::openDB()
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

    QString Asc;
    if(orderAscending)
        Asc = " ASC";
    else
        Asc = " DESC";

    QString order = "SELECT * FROM People Order By " + QString::fromStdString(orderBy) + Asc;

    query.prepare(order);

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

    QString Asc;
    if(orderAscending)
        Asc = " ASC";
    else
        Asc = " DESC";

    QString order = "SELECT * FROM Computers Order By " + QString::fromStdString(orderBy) + Asc;


    query.prepare(order);
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

std::vector<string> NerdSQL::getAllConnections(std::string sortBy, bool sortAscending)
{
    vector<string> Connections;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    QString Asc;
    if(sortAscending)
        Asc = " ASC";
    else
        Asc = " DESC";

    QString order = "SELECT * FROM Connections Order By " + QString::fromStdString(sortBy) + Asc;


    query.prepare(order);
    query.bindValue("Name", QString::fromStdString("*"));

    query.exec();

    while(query.next()){
        string sName = query.value("SName").toString().toStdString();
        string cName = query.value("CName").toString().toStdString();

        Connections.push_back(sName);
        Connections.push_back(cName);
    }

    db.close();


    return Connections;
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

    QString search = "SELECT * FROM People WHERE Name LIKE '%"+QString::fromStdString(searchTerm)
            +"%' OR YearBorn LIKE '%"+QString::fromStdString(searchTerm)
            +"%' OR YearDeath LIKE '%"+QString::fromStdString(searchTerm)+"%'";

    query.prepare(search);
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

std::vector<Computer> NerdSQL::searchForComputers(std::string searchTerm)
{
    vector<Computer> Computers;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    QString search = "SELECT * FROM Computers WHERE Name LIKE '%"+QString::fromStdString(searchTerm)
                    +"%' OR Type LIKE '%"+QString::fromStdString(searchTerm)+"%'";

    query.prepare(search);
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
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query;

    string name = computer.getName();
    string type = computer.getType();
    string yearBuilt = computer.getYearBuilt();
    bool made = computer.getMade();

    query.prepare("INSERT INTO Computers(Name, Type, YearBuilt, Made) "
                  "VALUES (:Name, :Type, :YearBuilt, :Made)");
    query.bindValue(":Name", QString::fromStdString(name));
    query.bindValue(":Type", QString::fromStdString(type));
    query.bindValue(":YearBuilt", QString::fromStdString(yearBuilt));
    query.bindValue(":Made", made);
    query.exec();
    db.close();

    return true;
}

bool NerdSQL::addConnection(std::string nerdName, std::string pcName)
{
    vector<string> Connections;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "../SQL/Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    QString searchNerd = "SELECT * FROM People WHERE Name='"+QString::fromStdString(nerdName)+"'";
    query.prepare(searchNerd);
    query.bindValue("Name", QString::fromStdString("*"));
    query.exec();

    while(query.next()){
        string name = query.value("Name").toString().toStdString();
        Connections.push_back(name);
    }

    QString searchPC = "SELECT * FROM Computers WHERE Name='"+QString::fromStdString(pcName)+"'";
    query.prepare(searchPC);
    query.bindValue("Name", QString::fromStdString("*"));
    query.exec();

    while(query.next()){
        string name = query.value("Name").toString().toStdString();

        Connections.push_back(name);
    }
/*
    for(unsigned int i(0); i<Connections.size(); i++)
    {
        cout << Connections.at(i) << endl;
    }

    cin.get();
*/
    if(Connections.size()!=2)
        return false;
    else
    {
        query.prepare("INSERT INTO Connections(SName, CName) "
                      "VALUES (:SName, :CName)");
        query.bindValue(":SName", QString::fromStdString(Connections.at(0)));
        query.bindValue(":CName", QString::fromStdString(Connections.at(1)));
        query.exec();
    }

    return true;
}
