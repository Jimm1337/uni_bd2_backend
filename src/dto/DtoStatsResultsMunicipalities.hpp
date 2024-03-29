#ifndef DtoStatsResultsMunicipalities_hpp
#define DtoStatsResultsMunicipalities_hpp

#include "DtoStatsInfoMunicipality.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoStatsResultsMunicipalities : public oatpp::DTO {
  DTO_INIT(DtoStatsResultsMunicipalities, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String, region);
  DTO_FIELD(String, district);
  DTO_FIELD(UnorderedFields< Object< DtoStatsInfoMunicipality > >, info) = {};

  DTO_FIELD_INFO(success) {
    info->required    = true;
    info->description = "Database query success";
  }

  DTO_FIELD_INFO(region) {
    info->required    = false;
    info->description = "Region name";
  }

  DTO_FIELD_INFO(district) {
    info->required    = false;
    info->description = "District name";
  }

  DTO_FIELD_INFO(info) {
    info->required    = false;
    info->description = "Municipalities in district info - key is municipality "
                        "name, value is municipality info";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsResultsMunicipalities_hpp