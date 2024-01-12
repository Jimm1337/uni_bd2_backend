#ifndef DtoStatsResultsDistricts_hpp
#define DtoStatsResultsDistricts_hpp

#include "DtoStatsInfoDistrict.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoStatsResultsDistricts : public oatpp::DTO {
  DTO_INIT(DtoStatsResultsDistricts, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String, region);
  DTO_FIELD(UnorderedFields< Object< DtoStatsInfoDistrict > >, info) = {};

  DTO_FIELD_INFO(success) {
    info->required    = true;
    info->description = "Database query success";
  }

  DTO_FIELD_INFO(region) {
    info->required    = false;
    info->description = "Region name";
  }

  DTO_FIELD_INFO(info) {
    info->required = false;
    info->description =
      "Districts in region info - key is district name, value is district info";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsResultsDistricts_hpp