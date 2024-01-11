#ifndef BDTestStats_hpp
#define BDTestStats_hpp

#include "oatpp-test/UnitTest.hpp"

class BDTestStats : public oatpp::test::UnitTest {
public:
  BDTestStats(): UnitTest("TEST [ Stats ]") {
  }

  void onRun() override;
};

#endif // BDTestStats_hpp
