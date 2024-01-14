#ifndef CRUD_USERSERVICE_HPP
#define CRUD_USERSERVICE_HPP

#include <variant>
#include "db/BDDatabase.hpp"
#include "dto/DtoError.hpp"
#include "dto/DtoSearchResultsDistricts.hpp"
#include "dto/DtoSearchResultsMunicipalities.hpp"
#include "dto/DtoSearchResultsRegions.hpp"
#include "dto/DtoStatsResultsDistricts.hpp"
#include "dto/DtoStatsResultsMunicipalities.hpp"
#include "dto/DtoStatsResultsRegions.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class BDService {
private:
  using Status = oatpp::web::protocol::http::Status;

  OATPP_COMPONENT(
    std::shared_ptr< BDDatabase >, m_database); // Inject database component

public:
  // SEARCH API ENDPOINTS ------------------------------------------------------

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoSearchResultsRegions > >
  searchRegion(const oatpp::String& prefix);

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoSearchResultsDistricts > >
  searchDistrict(const oatpp::String& region, const oatpp::String& prefix);

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoSearchResultsMunicipalities > >
  searchMunicipality(
    const oatpp::String& district, const oatpp::String& prefix);

  // STATS API ENDPOINTS -------------------------------------------------------

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoStatsResultsRegions > >
  statsRegions();

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoStatsResultsDistricts > >
  statsDistricts(const oatpp::String& region);

  std::variant<
    oatpp::Object< DtoError >,
    oatpp::Object< DtoStatsResultsMunicipalities > >
  statsMunicipalities(const oatpp::String& district);

private:
  static oatpp::String fixInputString(const oatpp::String& input);
};

#endif // CRUD_USERSERVICE_HPP