#ifndef BDTestStats_hpp
#define BDTestStats_hpp

#include "app/BDTest.hpp"
#include "oatpp-test/UnitTest.hpp"

class BDTestStats : public oatpp::test::UnitTest {
public:
  BDTestStats(): UnitTest("TEST [ Stats ]") {
  }

  void onRun() override;

private:
  void testStatsRegions(
    BDTest&                                               client,
    std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
  void testStatsDistricts(
    BDTest&                                               client,
    std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
  void testStatsMunicipalities(
    BDTest&                                               client,
    std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
};

#endif // BDTestStats_hpp
