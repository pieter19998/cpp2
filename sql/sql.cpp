#include "sql.h"

Sql::Sql() : dbName_("handelsschepen.db") {}

std::unique_ptr<Ship> Sql::GetShip(int shipId) const {
    const std::string query{
            "select * from schepen where id = " + std::to_string(shipId)
    };

    const std::string query2{
            "SELECT bijzonderheden.bijzonderheid "
            "FROM schepen_bijzonderheden "
            "INNER JOIN bijzonderheden ON schepen_bijzonderheden.bijzonderheid_id = bijzonderheden.id "
            "WHERE schepen_bijzonderheden.schip_id = " + std::to_string(shipId)
    };

    sqlite3 *db{nullptr};
    int status{sqlite3_open(dbName_.c_str(), &db)};
    std::unique_ptr<sqlite3, int (*)(sqlite3 *)> dbh{db, sqlite3_close};
    if (status != SQLITE_OK) {
        std::cout << "failure";
        sqlite3_close(db);
        std::exit(EXIT_FAILURE);
    }
    int id, price, cargo, cannons, health;
    std::string type, particularity;

    sqlite3_stmt *stmt{nullptr};
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
        type = (reinterpret_cast<char const *>(sqlite3_column_text(stmt, 1)));
        price = sqlite3_column_int(stmt, 2);
        cargo = sqlite3_column_int(stmt, 3);
        cannons = sqlite3_column_int(stmt, 4);
        health = sqlite3_column_int(stmt, 5);
    }

    sqlite3_prepare_v2(db, query2.c_str(), -1, &stmt, nullptr);
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        particularity = (reinterpret_cast<char const *>(sqlite3_column_text(stmt, 0)));
    }
    sqlite3_finalize(stmt);
    return std::make_unique<Ship>(type, id, price, cargo, cannons, health, StringToParticularity(particularity));
}

Particularities Sql::StringToParticularity(const std::string &particularity) const {
    if (particularity == "log") return LOG;
    if (particularity == "light") return LIGHT;
    if (particularity == "small") return SMALL;
    return NONE;
}

//distance between ports
int Sql::GetDistance(int from, int to) const {
    const std::string query{
            "SELECT afstand from afstanden WHERE haven1_id = " + std::to_string(from) + " and haven2_id =" +
            std::to_string(to)
    };
    sqlite3 *db{nullptr};
    sqlite3_open(dbName_.c_str(), &db);
    std::unique_ptr<sqlite3, int (*)(sqlite3 *)> dbh{db, sqlite3_close};
    int distance{0};
    sqlite3_stmt *stmt{nullptr};
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        distance = sqlite3_column_int(stmt, 0);
    }
    return distance;
}

//distance between ports
std::vector<std::unique_ptr<Wares>> Sql::GetWares(int portId) const {
    const std::string query{
            "select * from havens_goederen "
            "INNER JOIN goederen ON havens_goederen.goed_id = goederen.id "
            "WHERE havens_goederen.haven_id = " + std::to_string(portId)
    };
    sqlite3 *db{nullptr};
    int status{sqlite3_open(dbName_.c_str(), &db)};
    std::unique_ptr<sqlite3, int (*)(sqlite3 *)> dbh{db, sqlite3_close};
    if (status != SQLITE_OK) {
        std::cout << "failure";
        sqlite3_close(db);
        std::exit(EXIT_FAILURE);
    }
    int wareId;
    std::string ware;

    auto vector{std::vector<std::unique_ptr<Wares>>()};
    sqlite3_stmt *stmt{nullptr};
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        wareId = sqlite3_column_int(stmt, 1);
        ware = (reinterpret_cast<char const *>(sqlite3_column_text(stmt, 7)));
        //calculate price
        int price{Dice::get().generateNumber(sqlite3_column_int(stmt, 4), sqlite3_column_int(stmt, 5))};
        //calculate amount
        int amount{Dice::get().generateNumber(sqlite3_column_int(stmt, 2), sqlite3_column_int(stmt, 3))};
        vector.emplace_back(std::make_unique<Wares>(ware, wareId, amount, price));
    }
    return std::move(vector);
}

std::unique_ptr<Port> Sql::GetPort(int id) const {
    const std::string query{
            "select * from havens WHERE id = " + std::to_string(id)
    };
    sqlite3 *db{nullptr};
    int status{sqlite3_open(dbName_.c_str(), &db)};
    std::unique_ptr<sqlite3, int (*)(sqlite3 *)> dbh{db, sqlite3_close};
    if (status != SQLITE_OK) {
        std::cout << "failure";
        sqlite3_close(db);
        std::exit(EXIT_FAILURE);
    }
    std::string name;
    sqlite3_stmt *stmt{nullptr};
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    while ((sqlite3_step(stmt)) == SQLITE_ROW) {
        name = (reinterpret_cast<char const *>(sqlite3_column_text(stmt, 1)));
    }

    //get wares in port
    auto wares{GetWares(id)};

    //get 3 ships for ship shop
    std::vector<std::unique_ptr<Ship>> ships;
    ships.emplace_back(GetShip(Dice::get().generateNumber(0, 13)));
    ships.emplace_back(GetShip(Dice::get().generateNumber(0, 13)));
    ships.emplace_back(GetShip(Dice::get().generateNumber(0, 13)));

    //get Cannons in port
    int l{Dice::get().generateNumber(0, 5)};
    int m{Dice::get().generateNumber(0, 3)};
    int h{Dice::get().generateNumber(0, 2)};
    auto cannon{std::make_unique<Cannon>(l, m, h)};
    return std::make_unique<Port>(id, name, wares, cannon, ships);
}
