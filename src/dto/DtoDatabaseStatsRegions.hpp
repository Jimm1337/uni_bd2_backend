#ifndef DtoDatabaseStatsRegions_hpp
#define DtoDatabaseStatsRegions_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoDatabaseStatsRegions : public oatpp::DTO {
  DTO_INIT(DtoDatabaseStatsRegions, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, capital);
  DTO_FIELD(Int32, totalpopulation);
  DTO_FIELD(Int32, area);
  DTO_FIELD(Float64, populationdensity);

  DTO_FIELD_INFO(name) {
    info->required    = true;
    info->description = "Region name";
  }

  DTO_FIELD_INFO(capital) {
    info->required    = true;
    info->description = "Region capital";
  }

  DTO_FIELD_INFO(totalpopulation) {
    info->required    = true;
    info->description = "Region total population";
  }

  DTO_FIELD_INFO(area) {
    info->required    = true;
    info->description = "Region area";
  }

  DTO_FIELD_INFO(populationdensity) {
    info->required    = true;
    info->description = "Region population density";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoDatabaseStatsRegions_hpp