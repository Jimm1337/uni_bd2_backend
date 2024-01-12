#ifndef DtoDatabaseStatsMunicipalities_hpp
#define DtoDatabaseStatsMunicipalities_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoDatabaseStatsMunicipalities : public oatpp::DTO {
  DTO_INIT(DtoDatabaseStatsMunicipalities, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, postalcode);
  DTO_FIELD(String, district);
  DTO_FIELD(String, region);

  DTO_FIELD_INFO(name) {
    info->required    = true;
    info->description = "Region name";
  }

  DTO_FIELD_INFO(postalcode) {
    info->required    = true;
    info->description = "Municipality postal code";
  }

  DTO_FIELD_INFO(district) {
    info->required    = true;
    info->description = "District";
  }

  DTO_FIELD_INFO(region) {
    info->required    = true;
    info->description = "Region";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoDatabaseStatsMunicipalities_hpp