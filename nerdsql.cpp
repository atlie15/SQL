#include "nerdsql.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>

using namespace std;

NerdSQL::NerdSQL()
{

}

std::vector<Nerd> NerdSQL::getAllNerds()
{
    vector<Nerd> ComputerScientists;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "Scientists.sqlite";
    db.setDatabaseName(dbName);

    db.open();

    QSqlQuery query(db);

    query.prepare("SELECT * FROM People");
    query.bindValue("Name", QString::fromStdString("*"));

    query.exec();

    while(query.next()){

        string name = query.value("Name").toString().toStdString();
        string sex = query.value("Gender").toString().toStdString();
        string born = query.value("YearBorn").toString().toStdString();
        string dead = query.value("YearDeath").toString().toStdString();

        Nerd dude(name, sex, born, dead);

        ComputerScientists.push_back(dude);
    }

    db.close();

    return ComputerScientists;
}
