#ifndef DtoSearchResultsDistricts_hpp
#define DtoSearchResultsDistricts_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoSearchResultsDistricts : public oatpp::DTO {

  DTO_INIT(DtoSearchResultsDistricts, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String , region);
  DTO_FIELD(Vector<String>, names);

};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoSearchResultsDistricts_hpp