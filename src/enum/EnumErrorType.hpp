#ifndef DtoEnumErrorType_hpp
#define DtoEnumErrorType_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(
  ErrorType,
  v_int8,
  VALUE(UNKNOWN, 0, "Unknown error"),
  VALUE(IMPLEMENTATION, 1, "Implementation error"),
  VALUE(DATABASE, 2, "Database error"));

#include OATPP_CODEGEN_END(DTO)

#endif // DtoEnumErrorType_hpp