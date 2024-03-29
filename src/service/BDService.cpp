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
  const auto correctPrefix = fixInputString(prefix);

  const auto result = m_database->regionsStartingWith(correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsRegions::createShared();

  const auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();

  for (const auto& row : *intermediateResult) { ret->names->push_back(row->name); }

  ret->success = true;

  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoSearchResultsDistricts > >
BDService::searchDistrict(
  const oatpp::String& region, const oatpp::String& prefix) {
  auto correctRegion = fixInputString(region);
  auto correctPrefix = fixInputString(prefix);

  const auto result = m_database->districtsStartingWith(correctRegion, correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsDistricts::createShared();

  const auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();

  for (const auto& row : *intermediateResult) { ret->names->push_back(row->name); }

  ret->success = true;
  ret->region  = correctRegion;

  return ret;
}

std::variant<
  oatpp::Object< DtoError >,
  oatpp::Object< DtoSearchResultsMunicipalities > >
BDService::searchMunicipality(
  const oatpp::String& district, const oatpp::String& prefix) {
  const auto correctDistrict = fixInputString(district);
  const auto correctPrefix = fixInputString(prefix);

  const auto result =
    m_database->municipalitiesStartingWith(correctDistrict, correctPrefix);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoSearchResultsMunicipalities::createShared();

  const auto intermediateResult =
    result->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseSearch > > >();

  for (const auto& row : *intermediateResult) { ret->names->push_back(row->name); }

  ret->success  = true;
  ret->district = correctDistrict;

  return ret;
}

std::
  variant< oatpp::Object< DtoError >, oatpp::Object< DtoStatsResultsRegions > >
  BDService::statsRegions() {
  const auto result = m_database->statsRegions();

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoStatsResultsRegions::createShared();

  const auto intermediateResult =
    result
      ->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseStatsRegions > > >();

  for (const auto& row : *intermediateResult)
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
  const auto correctRegion = fixInputString(region);

  const auto result = m_database->statsDistricts(correctRegion);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoStatsResultsDistricts::createShared();

  const auto intermediateResult =
    result
      ->fetch< oatpp::Vector< oatpp::Object< DtoDatabaseStatsDistricts > > >();

  for (const auto& row : *intermediateResult)
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
  const auto correctDistrict = fixInputString(district);

  const auto result = m_database->statsMunicipalities(correctDistrict);

  if (!result->isSuccess())
  {
    auto ret     = DtoError::createShared();
    ret->type    = ErrorType::DATABASE;
    ret->message = result->getErrorMessage();
    return ret;
  }

  auto ret = DtoStatsResultsMunicipalities::createShared();

  auto intermediateResult = result->fetch<
    oatpp::Vector< oatpp::Object< DtoDatabaseStatsMunicipalities > > >();
  oatpp::String region = "";

  if (!intermediateResult->empty())
  { region = intermediateResult->front()->region; }

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

oatpp::String BDService::fixInputString(const oatpp::String& input) {
  auto correctInput = input;

  for (auto pos = correctInput->find('%'); pos != std::string::npos;
       pos      = correctInput->find('%'))
  {
    const auto codedChar = correctInput->substr(pos, 6);

    if (codedChar.substr(0, 3) == "%20")
    {
      correctInput->replace(pos, 3, " ");
      continue;
    }
    if (codedChar == "%C3%A1")
    {
      correctInput->replace(pos, 6, "á");
      continue;
    }
    if (codedChar == "%C4%8D")
    {
      correctInput->replace(pos, 6, "č");
      continue;
    }
    if (codedChar == "%C4%8F")
    {
      correctInput->replace(pos, 6, "ď");
      continue;
    }
    if (codedChar == "%C3%A9")
    {
      correctInput->replace(pos, 6, "é");
      continue;
    }
    if (codedChar == "%C4%9B")
    {
      correctInput->replace(pos, 6, "ě");
      continue;
    }
    if (codedChar == "%C3%AD")
    {
      correctInput->replace(pos, 6, "í");
      continue;
    }
    if (codedChar == "%C5%88")
    {
      correctInput->replace(pos, 6, "ň");
      continue;
    }
    if (codedChar == "%C3%B3")
    {
      correctInput->replace(pos, 6, "ó");
      continue;
    }
    if (codedChar == "%C5%99")
    {
      correctInput->replace(pos, 6, "ř");
      continue;
    }
    if (codedChar == "%C5%A1")
    {
      correctInput->replace(pos, 6, "š");
      continue;
    }
    if (codedChar == "%C5%A5")
    {
      correctInput->replace(pos, 6, "ť");
      continue;
    }
    if (codedChar == "%C3%BA")
    {
      correctInput->replace(pos, 6, "ú");
      continue;
    }
    if (codedChar == "%C5%AF")
    {
      correctInput->replace(pos, 6, "ů");
      continue;
    }
    if (codedChar == "%C3%BD")
    {
      correctInput->replace(pos, 6, "ý");
      continue;
    }
    if (codedChar == "%C5%BE")
    {
      correctInput->replace(pos, 6, "ž");
      continue;
    }
    if (codedChar == "%C3%81")
    {
      correctInput->replace(pos, 6, "Á");
      continue;
    }
    if (codedChar == "%C4%8C")
    {
      correctInput->replace(pos, 6, "Č");
      continue;
    }
    if (codedChar == "%C4%8E")
    {
      correctInput->replace(pos, 6, "Ď");
      continue;
    }
    if (codedChar == "%C3%89")
    {
      correctInput->replace(pos, 6, "É");
      continue;
    }
    if (codedChar == "%C4%9A")
    {
      correctInput->replace(pos, 6, "Ě");
      continue;
    }
    if (codedChar == "%C3%8D")
    {
      correctInput->replace(pos, 6, "Í");
      continue;
    }
    if (codedChar == "%C5%87")
    {
      correctInput->replace(pos, 6, "Ň");
      continue;
    }
    if (codedChar == "%C3%93")
    {
      correctInput->replace(pos, 6, "Ó");
      continue;
    }
    if (codedChar == "%C5%98")
    {
      correctInput->replace(pos, 6, "Ř");
      continue;
    }
    if (codedChar == "%C5%A0")
    {
      correctInput->replace(pos, 6, "Š");
      continue;
    }
    if (codedChar == "%C5%A4")
    {
      correctInput->replace(pos, 6, "Ť");
      continue;
    }
    if (codedChar == "%C3%9A")
    {
      correctInput->replace(pos, 6, "Ú");
      continue;
    }
    if (codedChar == "%C5%AE")
    {
      correctInput->replace(pos, 6, "Ů");
      continue;
    }
    if (codedChar == "%C3%9D")
    {
      correctInput->replace(pos, 6, "Ý");
      continue;
    }
    if (codedChar == "%C5%BD")
    {
      correctInput->replace(pos, 6, "Ž");
      continue;
    }
  }

  return correctInput;
}
