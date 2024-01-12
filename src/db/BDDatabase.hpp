#ifndef BDDatabase_hpp
#define BDDatabase_hpp

#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class BDDatabase : public oatpp::orm::DbClient {
public:
  BDDatabase(const std::shared_ptr< oatpp::orm::Executor >& executor):
    oatpp::orm::DbClient(executor) {
    // TODO: uncomment to enable migrations

    //    oatpp::orm::SchemaMigration migration(executor);
    //    migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
    //    Add more migrations here.
    //    migration.migrate(); // <-- run migrations. This guy will throw
    //
    //    auto version = executor->getSchemaVersion();
    //    OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);
  }

  // SEARCH API ----------------------------------------------------------------

  QUERY(
    regionsStartingWith,
    "SELECT name_ AS name "
    "FROM regionsStartingWith(:prefix);",
    PARAM(oatpp::String, prefix))

  QUERY(
    districtsStartingWith,
    "SELECT name_ AS name "
    "FROM districtsinregion(:region) "
    "WHERE name_ LIKE :prefix || '%';",
    PARAM(oatpp::String, region),
    PARAM(oatpp::String, prefix))

  QUERY(
    municipalitiesStartingWith,
    "SELECT name_ AS name "
    "FROM municipalitiesindistrict(:district) "
    "WHERE name_ LIKE :prefix || '%';",
    PARAM(oatpp::String, district),
    PARAM(oatpp::String, prefix))

  // STATS API -----------------------------------------------------------------

  QUERY(statsRegions, "SELECT * FROM stats_regions;")

  QUERY(
    statsDistricts,
    "SELECT name_ AS name, area, totalpopulation, populationdensity, region "
    "FROM districtsinregion(:region);",
    PARAM(oatpp::String, region))

  QUERY(
    statsMunicipalities,
    "SELECT name_ AS name, postalcode, district, region "
    "FROM municipalitiesindistrict(:district);",
    PARAM(oatpp::String, district))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif // BDDatabase_hpp