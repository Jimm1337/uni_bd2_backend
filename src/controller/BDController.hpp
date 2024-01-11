#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DtoSearchResultsRegions.hpp"
#include "dto/DtoSearchResultsDistricts.hpp"
#include "dto/DtoSearchResultsMunicipalities.hpp"
#include "dto/DtoStatsResultsRegions.hpp"
#include "dto/DtoStatsResultsDistricts.hpp"
#include "dto/DtoStatsResultsMunicipalities.hpp"
#include "dto/DtoStatsInfoRegion.hpp"
#include "dto/DtoStatsInfoDistrict.hpp"
#include "dto/DtoStatsInfoMunicipality.hpp"
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
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  BDController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}

//  ENDPOINT("GET", "/", root) {
//    auto dto = MyDto::createShared();
//    dto->statusCode = 200;
//    dto->message = "Hello World!";
//    return createDtoResponse(Status::CODE_200, dto);
//  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
