#ifndef DtoStatsResultsRegions_hpp
#define DtoStatsResultsRegions_hpp

#include "DtoStatsInfoRegion.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoStatsResultsRegions : public oatpp::DTO {
  DTO_INIT(DtoStatsResultsRegions, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(UnorderedFields< Object< DtoStatsInfoRegion > >, info);

  DTO_FIELD_INFO(success) {
    info->required    = true;
    info->description = "Database query success";
  }

  DTO_FIELD_INFO(info) {
    info->required    = false;
    info->description = "Regions info";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoStatsResultsRegions_hpp