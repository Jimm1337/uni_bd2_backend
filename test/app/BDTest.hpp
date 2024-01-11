#ifndef BDTest_hpp
#define BDTest_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/client/ApiClient.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class BDTest : public oatpp::web::client::ApiClient {
  API_CLIENT_INIT(BDTest)

  // Stats API
  API_CALL("GET", "/stats/regions", getStatsRegions)
  API_CALL(
    "GET", "/stats/districts/{region}", getStatsDistricts, PATH(String, region))
  API_CALL(
    "GET",
    "/stats/municipalities/{district}",
    getStatsMunicipalities,
    PATH(String, district))

  // Search API
  API_CALL(
    "GET", "/search/region", getSearchRegion, QUERY(String, prefix, "prefix"))
  API_CALL(
    "GET",
    "/search/district/{region}",
    getSearchDistrict,
    PATH(String, region),
    QUERY(String, prefix, "prefix"))
  API_CALL(
    "GET",
    "/search/municipality/{district}",
    getSearchMunicipality,
    PATH(String, district),
    QUERY(String, prefix, "prefix"))
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // BDTest_hpp
