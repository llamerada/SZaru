#include <stdint.h>
#include <stdio.h>
#include <string>

#include "szaru.h"

void testSimple(){
  SZaru::UniqueEstimator *uniqueEstimator = 
    SZaru::UniqueEstimator::Create(10);
  const std::string test("test");
  char buf[255];
  for (int i = 0; i < 20000; i++) {
    sprintf(buf, "test %d", i);
    uniqueEstimator->AddElem(std::string(buf));
  }
  for (int i = 0; i < 200; i++) {
    sprintf(buf, "test %d", i);
    uniqueEstimator->AddElem(std::string(buf));
  }
  printf("%lld\n", uniqueEstimator->Estimate());
  delete uniqueEstimator;
}

int main()
{
  testSimple();
}
