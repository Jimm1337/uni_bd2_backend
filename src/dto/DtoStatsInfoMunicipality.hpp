#ifndef DtoStatsInfoMunicipality_hpp
#define DtoStatsInfoMunicipality_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoStatsInfoMunicipality : public oatpp::DTO {
  DTO_INIT(DtoStatsInfoMunicipality, DTO)

  DTO_FIELD(String, postalcode);

  DTO_FIELD_INFO(postalcode) {
    info->required    = true;
    info->description = "Municipality postal code";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsInfoMunicipality_hpp