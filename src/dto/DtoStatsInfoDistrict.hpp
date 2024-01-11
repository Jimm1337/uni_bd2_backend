#ifndef DtoStatsInfoDistrict_hpp
#define DtoStatsInfoDistrict_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoStatsInfoDistrict : public oatpp::DTO {
  DTO_INIT(DtoStatsInfoDistrict, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, area);
  DTO_FIELD(String, totalpopulation);
  DTO_FIELD(String, populationdensity);
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsInfoDistrict_hpp