#ifndef MyController_hpp
#define MyController_hpp

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

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class BDController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  BDController(OATPP_COMPONENT(std::shared_ptr< ObjectMapper >, objectMapper)):
    oatpp::web::server::api::ApiController(objectMapper) {
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
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
    // TODO: implement

    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::IMPLEMENTATION;
    dtoError->message = "Not implemented yet.";
    return createDtoResponse(Status::CODE_500, dtoError);
  }
  ADD_CORS(statsMunicipalities, "*", "GET")
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
