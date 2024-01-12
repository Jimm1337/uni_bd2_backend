#ifndef DtoDatabaseSearch_hpp
#define DtoDatabaseSearch_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoDatabaseSearch : public oatpp::DTO {
  DTO_INIT(DtoDatabaseSearch, DTO)

  DTO_FIELD(String, name);

  DTO_FIELD_INFO(name) {
    info->required    = true;
    info->description = "Region name";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoDatabaseSearch_hpp