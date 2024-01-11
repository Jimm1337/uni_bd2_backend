#include "BDTestStats.hpp"
#include "app/BDTest.hpp"
#include "app/BDTestComponent.hpp"
#include "controller/BDController.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void BDTestStats::onRun() {
  /* Register test components */
  BDTestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Add MyController endpoints to the router of the test server */
  runner.addController(std::make_shared< BDController >());

  /* Run test */
  runner.run(
    [this, &runner] {
      /* Get client connection provider for Api Client */
      OATPP_COMPONENT(
        std::shared_ptr< oatpp::network::ClientConnectionProvider >,
        clientConnectionProvider);

      /* Get object mapper component */
      OATPP_COMPONENT(
        std::shared_ptr< oatpp::data::mapping::ObjectMapper >, objectMapper);

      /* Create http request executor for Api Client */
      auto requestExecutor =
        oatpp::web::client::HttpRequestExecutor::createShared(
          clientConnectionProvider);

      /* Create Test API client */
      auto client = BDTest::createShared(requestExecutor, objectMapper);

      /* Call server API */
      testStatsRegions(*client, objectMapper);
      testStatsDistricts(*client, objectMapper);
      testStatsMunicipalities(*client, objectMapper);
    },
    std::chrono::seconds(60) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void BDTestStats::testStatsRegions(
  BDTest&                                               client,
  std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper) {
  auto response = client.getStatsRegions();
  OATPP_ASSERT(response->getStatusCode() == 200);

  auto message =
    response->readBodyToDto< oatpp::Object< DtoStatsResultsRegions > >(
      objectMapper.get());

  OATPP_ASSERT(message);
  OATPP_ASSERT(message->success == true);
  OATPP_ASSERT(message->info->empty() == false);
}

void BDTestStats::testStatsDistricts(
  BDTest&                                               client,
  std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper) {
  auto response = client.getStatsDistricts("Prague");
  OATPP_ASSERT(response->getStatusCode() == 200);

  auto message =
    response->readBodyToDto< oatpp::Object< DtoStatsResultsDistricts > >(
      objectMapper.get());

  OATPP_ASSERT(message);
  OATPP_ASSERT(message->success == true);
  OATPP_ASSERT(message->region == "Prague");
  OATPP_ASSERT(message->info->empty() == false);
}

void BDTestStats::testStatsMunicipalities(
  BDTest&                                               client,
  std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper) {
  auto response = client.getStatsMunicipalities("Prague");
  OATPP_ASSERT(response->getStatusCode() == 200);

  auto message =
    response->readBodyToDto< oatpp::Object< DtoStatsResultsMunicipalities > >(
      objectMapper.get());

  OATPP_ASSERT(message);
  OATPP_ASSERT(message->success == true);
  OATPP_ASSERT(message->region == "Prague");
  OATPP_ASSERT(message->district == "Prague");
  OATPP_ASSERT(message->info->empty() == false);
}
