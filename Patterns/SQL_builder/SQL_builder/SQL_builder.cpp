#include <string>
#include <vector>
#include <map>
#include <cassert>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() = default;

    // Добавление одного столбца
    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        if (!column.empty()) {
            columns_.push_back(column);
        }
        return *this;
    }

    // Добавление нескольких столбцов
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            if (!column.empty()) {
                columns_.push_back(column);
            }
        }
        return *this;
    }

    // Добавление таблицы
    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept {
        if (!table.empty()) {
            table_ = table;
        }
        return *this;
    }

    // Добавление одного условия WHERE
    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept {
        if (!column.empty() && !value.empty()) {
            where_conditions_[column] = value;
        }
        return *this;
    }

    // Добавление нескольких условий WHERE
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [key, value] : kv) {
            if (!key.empty() && !value.empty()) {
                where_conditions_[key] = value;
            }
        }
        return *this;
    }

    // Построение запроса
    std::string BuildQuery() const {
        std::string query = "SELECT ";

        // Добавление столбцов
        if (columns_.empty()) {
            query += "*";
        }
        else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                if (i != 0) {
                    query += ", ";
                }
                query += columns_[i];
            }
        }

        // Добавление таблицы
        query += " FROM " + table_;

        // Добавление условий WHERE
        if (!where_conditions_.empty()) {
            query += " WHERE ";
            bool first = true;
            for (const auto& [column, value] : where_conditions_) {
                if (!first) {
                    query += " AND ";
                }
                query += column + "=" + value;
                first = false;
            }
        }

        query += ";";
        return query;
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::map<std::string, std::string> where_conditions_;
};

int main() {
    // Тестирование нового функционала
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumns({ "name", "phone", "email" });
        query_builder.AddFrom("users");
        query_builder.AddWhere({ {"id", "100"}, {"status", "active"} });

        assert(query_builder.BuildQuery() ==
            "SELECT name, phone, email FROM users WHERE id=100 AND status=active;");
    }

    // Тестирование комбинации старых и новых методов
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumn("login");
        query_builder.AddColumns({ "password", "last_login" });
        query_builder.AddFrom("accounts");
        query_builder.AddWhere("active", "1");
        query_builder.AddWhere({ {"banned", "0"}, {"deleted", "0"} });

        assert(query_builder.BuildQuery() ==
            "SELECT login, password, last_login FROM accounts WHERE active=1 AND banned=0 AND deleted=0;");
    }

    return 0;
}