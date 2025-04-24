#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

int main()
{
    std::string connectionString =
        "host=localhost"
        " port=5432"
        " dbname=lesson03"
        " user=lesson03user"
        " password=lesson03user";
    auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
    Wt::Dbo::Session session;
    session.setConnection(std::move(postgres));
}