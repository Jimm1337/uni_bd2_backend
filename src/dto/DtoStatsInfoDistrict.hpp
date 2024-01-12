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

  DTO_FIELD(Int32, area);
  DTO_FIELD(Int32, totalpopulation);
  DTO_FIELD(Float64, populationdensity);

  DTO_FIELD_INFO(area) {
    info->required    = true;
    info->description = "District area";
  }

  DTO_FIELD_INFO(totalpopulation) {
    info->required    = true;
    info->description = "District total population";
  }

  DTO_FIELD_INFO(populationdensity) {
    info->required    = true;
    info->description = "District population density";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsInfoDistrict_hpp