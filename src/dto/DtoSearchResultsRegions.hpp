#ifndef DtoSearchResultsRegions_hpp
#define DtoSearchResultsRegions_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoSearchResultsRegions : public oatpp::DTO {
  DTO_INIT(DtoSearchResultsRegions, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Vector< String >, names) = {};

  DTO_FIELD_INFO(success) {
    info->required    = true;
    info->description = "Database query success";
  }

  DTO_FIELD_INFO(names) {
    info->required    = false;
    info->description = "Region names";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoSearchResultsRegions_hpp