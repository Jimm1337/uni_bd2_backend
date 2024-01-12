#ifndef DtoSearchResultsMunicipalities_hpp
#define DtoSearchResultsMunicipalities_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoSearchResultsMunicipalities : public oatpp::DTO {
  DTO_INIT(DtoSearchResultsMunicipalities, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String, district);
  DTO_FIELD(Vector< String >, names) = {};

  DTO_FIELD_INFO(success) {
    info->required    = true;
    info->description = "Database query success";
  }

  DTO_FIELD_INFO(district) {
    info->required    = false;
    info->description = "District name";
  }

  DTO_FIELD_INFO(names) {
    info->required    = false;
    info->description = "Municipality names";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoSearchResultsMunicipalities_hpp