#ifndef DtoDatabaseStatsDistricts_hpp
#define DtoDatabaseStatsDistricts_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoDatabaseStatsDistricts : public oatpp::DTO {
  DTO_INIT(DtoDatabaseStatsDistricts, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Int32, area);
  DTO_FIELD(Int32, totalpopulation);
  DTO_FIELD(Float64, populationdensity);
  DTO_FIELD(String, region);

  DTO_FIELD_INFO(name) {
    info->required    = true;
    info->description = "Region name";
  }

  DTO_FIELD_INFO(area) {
    info->required    = true;
    info->description = "Region area";
  }

  DTO_FIELD_INFO(totalpopulation) {
    info->required    = true;
    info->description = "Region total population";
  }

  DTO_FIELD_INFO(populationdensity) {
    info->required    = true;
    info->description = "Region population density";
  }

  DTO_FIELD_INFO(region) {
    info->required    = true;
    info->description = "Region";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoDatabaseStatsDistricts_hpp