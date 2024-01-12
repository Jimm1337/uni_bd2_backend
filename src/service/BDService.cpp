#include "BDService.hpp"
#include "dto/DtoDatabaseSearch.hpp"
#include "dto/DtoDatabaseStatsDistricts.hpp"
#include "dto/DtoDatabaseStatsMunicipalities.hpp"
#include "dto/DtoDatabaseStatsRegions.hpp"
#include "dto/DtoError.hpp"
#include "enum/EnumErrorType.hpp"
#include "fmt/core.h"

std::
  variant< oatpp::Object< DtoError >, oatpp::Object< DtoSearchResultsRegions > >
  BDService::searchRegion(const oatpp::String& prefix) {
  auto correctPrefix = oatpp::String{ prefix };
  auto pos           = correctPrefix->find("%20");
  if (pos != std::string::npos) { correctPrefix->replace(pos, 3, " "); }

  auto result = m_database->regionsStartingWith(correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsRegions::createShared();
  auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();
  for (auto& row : *intermediateResult) { ret->names->push_back(row->name); }
  ret->success = true;
  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoSearchResultsDistricts > >
BDService::searchDistrict(
  const oatpp::String& region, const oatpp::String& prefix) {
  auto correctRegion = oatpp::String{ region };
  auto pos           = correctRegion->find("%20");
  if (pos != std::string::npos) { correctRegion->replace(pos, 3, " "); }
  auto correctPrefix = oatpp::String{ prefix };
  pos                = correctPrefix->find("%20");
  if (pos != std::string::npos) { correctPrefix->replace(pos, 3, " "); }

  auto result = m_database->districtsStartingWith(correctRegion, correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsDistricts::createShared();
  auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();
  for (auto& row : *intermediateResult) { ret->names->push_back(row->name); }
  ret->success = true;
  ret->region  = correctRegion;
  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoSearchResultsMunicipalities > >
BDService::searchMunicipality(
  const oatpp::String& district, const oatpp::String& prefix) {
  auto correctDistrict = oatpp::String{ district };
  auto pos             = correctDistrict->find("%20");
  if (pos != std::string::npos) { correctDistrict->replace(pos, 3, " "); }
  auto correctPrefix = oatpp::String{ prefix };
  pos                = correctPrefix->find("%20");
  if (pos != std::string::npos) { correctPrefix->replace(pos, 3, " "); }

  auto result =
    m_database->municipalitiesStartingWith(correctDistrict, correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsMunicipalities::createShared();
  auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();
  for (auto& row : *intermediateResult) { ret->names->push_back(row->name); }
  ret->success  = true;
  ret->district = correctDistrict;
  return ret;
}

std::
  variant< oatpp::Object< DtoError >, oatpp::Object< DtoStatsResultsRegions > >
  BDService::statsRegions() {
  auto result = m_database->statsRegions();

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto intermediateResult =
    result
      ->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseStatsRegions > > >();

  auto ret = DtoStatsResultsRegions::createShared();
  for (auto& row : *intermediateResult)
  {
    auto info               = DtoStatsInfoRegion::createShared();
    info->area              = row->area;
    info->capital           = row->capital;
    info->populationdensity = row->populationdensity;
    info->totalpopulation   = row->totalpopulation;
    ret->info->insert(std::make_pair(row->name, info));
  }
  ret->success = true;

  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoStatsResultsDistricts > >
BDService::statsDistricts(const oatpp::String& region) {
  auto correctRegion = oatpp::String{ region };
  auto pos           = correctRegion->find("%20");
  if (pos != std::string::npos) { correctRegion->replace(pos, 3, " "); }

  auto result = m_database->statsDistricts(correctRegion);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto intermediateResult =
    result
      ->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseStatsDistricts > > >();

  auto ret = DtoStatsResultsDistricts::createShared();
  for (auto& row : *intermediateResult)
  {
    auto info               = DtoStatsInfoDistrict::createShared();
    info->area              = row->area;
    info->populationdensity = row->populationdensity;
    info->totalpopulation   = row->totalpopulation;
    ret->info->insert(std::make_pair(row->name, info));
  }
  ret->success = true;
  ret->region  = correctRegion;

  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoStatsResultsMunicipalities > >
BDService::statsMunicipalities(const oatpp::String& district) {
  auto correctDistrict = oatpp::String{ district };
  auto pos             = correctDistrict->find("%20");
  if (pos != std::string::npos) { correctDistrict->replace(pos, 3, " "); }

  auto result = m_database->statsMunicipalities(correctDistrict);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto intermediateResult = result->fetch<
    oatpp::Vector< oatpp::Object< DtoDatabaseStatsMunicipalities > > >();
  oatpp::String region = "";

  if (!intermediateResult->empty())
  { region = intermediateResult->front()->region; }

  auto ret = DtoStatsResultsMunicipalities::createShared();
  for (auto& row : *intermediateResult)
  {
    auto info        = DtoStatsInfoMunicipality::createShared();
    info->postalcode = row->postalcode;
    ret->info->insert(std::make_pair(row->name, info));
  }
  ret->success  = true;
  ret->district = correctDistrict;
  ret->region   = region;

  return ret;
}