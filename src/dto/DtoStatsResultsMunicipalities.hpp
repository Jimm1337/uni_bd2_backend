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
  DTO_FIELD(Vector< Object< DtoStatsInfoMunicipality > >, info);
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsResultsMunicipalities_hpp