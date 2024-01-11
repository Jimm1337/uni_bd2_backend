#ifndef BDTestSearch_hpp
#define BDTestSearch_hpp

#include "app/BDTest.hpp"
#include "oatpp-test/UnitTest.hpp"

class BDTestSearch : public oatpp::test::UnitTest {
public:
  BDTestSearch(): UnitTest("TEST [ Search ]") {
  }

  void onRun() override;

private:
  void testSearchRegion(
    BDTest& client, std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
  void testSearchDistrict(
    BDTest& client, std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
  void testSearchMunicipality(
    BDTest& client, std::shared_ptr< oatpp::data::mapping::ObjectMapper > objectMapper);
};

#endif // BDTestSearch_hpp
