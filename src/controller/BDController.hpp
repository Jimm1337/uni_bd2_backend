#ifndef MyController_hpp
#define MyController_hpp

#include <variant>
#include "dto/DtoError.hpp"
#include "dto/DtoSearchResultsDistricts.hpp"
#include "dto/DtoSearchResultsMunicipalities.hpp"
#include "dto/DtoSearchResultsRegions.hpp"
#include "dto/DtoStatsInfoDistrict.hpp"
#include "dto/DtoStatsInfoMunicipality.hpp"
#include "dto/DtoStatsInfoRegion.hpp"
#include "dto/DtoStatsResultsDistricts.hpp"
#include "dto/DtoStatsResultsMunicipalities.hpp"
#include "dto/DtoStatsResultsRegions.hpp"
#include "enum/EnumErrorType.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/BDService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class BDController : public oatpp::web::server::api::ApiController {
  BDService m_userService; // Create user service.

public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  BDController(OATPP_COMPONENT(std::shared_ptr< ObjectMapper >, objectMapper)):
    oatpp::web::server::api::ApiController(objectMapper) {
  }

  static std::shared_ptr< BDController > createShared(OATPP_COMPONENT(
    std::shared_ptr< ObjectMapper >,
    objectMapper) // Inject objectMapper component here as default parameter
  ) {
    return std::make_shared< BDController >(objectMapper);
  }

  // SEARCH API ENDPOINTS ------------------------------------------------------

  ENDPOINT_INFO(searchRegion) {
    info->summary = "Search for regions";
    info->addResponse< Object< DtoSearchResultsRegions > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT(
    "GET", "/search/region", searchRegion, QUERY(String, prefix, "prefix")) {
    auto result = m_userService.searchRegion(prefix);
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoSearchResultsRegions =
        std::get< oatpp::Object< DtoSearchResultsRegions > >(result);
      return createDtoResponse(Status::CODE_200, dtoSearchResultsRegions);
    }
  }
  ADD_CORS(searchRegion, "*", "GET")

  ENDPOINT_INFO(searchDistrict) {
    info->summary = "Search for districts";
    info->addResponse< Object< DtoSearchResultsDistricts > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT(
    "GET",
    "/search/district/{region}",
    searchDistrict,
    PATH(String, region),
    QUERY(String, prefix, "prefix")) {
    auto result = m_userService.searchDistrict(region, prefix);
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoSearchResultsDistricts =
        std::get< oatpp::Object< DtoSearchResultsDistricts > >(result);
      return createDtoResponse(Status::CODE_200, dtoSearchResultsDistricts);
    }
  }
  ADD_CORS(searchDistrict, "*", "GET")

  ENDPOINT_INFO(searchMunicipality) {
    info->summary = "Search for municipalities";
    info->addResponse< Object< DtoSearchResultsMunicipalities > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT(
    "GET",
    "/search/municipality/{district}",
    searchMunicipality,
    PATH(String, district),
    QUERY(String, prefix, "prefix")) {
    auto result = m_userService.searchMunicipality(district, prefix);
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoSearchResultsMunicipalities =
        std::get< oatpp::Object< DtoSearchResultsMunicipalities > >(result);
      return createDtoResponse(
        Status::CODE_200, dtoSearchResultsMunicipalities);
    }
  }
  ADD_CORS(searchMunicipality, "*", "GET")

  // STATS API ENDPOINTS -------------------------------------------------------

  ENDPOINT_INFO(statsRegions) {
    info->summary = "Get regions statistics";
    info->addResponse< Object< DtoStatsResultsRegions > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "/stats/regions", statsRegions) {
    auto result = m_userService.statsRegions();
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoStatsResultsRegions =
        std::get< oatpp::Object< DtoStatsResultsRegions > >(result);
      return createDtoResponse(Status::CODE_200, dtoStatsResultsRegions);
    }
  }
  ADD_CORS(statsRegions, "*", "GET")

  ENDPOINT_INFO(statsDistricts) {
    info->summary = "Get districts statistics";
    info->addResponse< Object< DtoStatsResultsDistricts > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT(
    "GET", "/stats/districts/{region}", statsDistricts, PATH(String, region)) {
    auto result = m_userService.statsDistricts(region);
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoStatsResultsDistricts =
        std::get< oatpp::Object< DtoStatsResultsDistricts > >(result);
      return createDtoResponse(Status::CODE_200, dtoStatsResultsDistricts);
    }
  }
  ADD_CORS(statsDistricts, "*", "GET")

  ENDPOINT_INFO(statsMunicipalities) {
    info->summary = "Get municipalities statistics";
    info->addResponse< Object< DtoStatsResultsMunicipalities > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
  }
  ENDPOINT(
    "GET",
    "/stats/municipalities/{district}",
    statsMunicipalities,
    PATH(String, district)) {
    auto result = m_userService.statsMunicipalities(district);
    if (std::holds_alternative< oatpp::Object< DtoError > >(result))
    {
      auto dtoError = std::get< oatpp::Object< DtoError > >(result);
      return createDtoResponse(Status::CODE_500, dtoError);
    } else {
      auto dtoStatsResultsMunicipalities =
        std::get< oatpp::Object< DtoStatsResultsMunicipalities > >(result);
      return createDtoResponse(Status::CODE_200, dtoStatsResultsMunicipalities);
    }
  }
  ADD_CORS(statsMunicipalities, "*", "GET")
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
