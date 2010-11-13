#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "szaru.h"
using namespace SZaru;
using namespace std;

void testSimple(){
  UniqueEstimator *uniqueEstimator = 
    UniqueEstimator::Create(10);
  const string test("test");
  char buf[255];
  for (int i = 0; i < 20000; i++) {
    sprintf(buf, "test %d", i);
    uniqueEstimator->AddElem(string(buf));
  }
  for (int i = 0; i < 200; i++) {
    sprintf(buf, "test %d", i);
    uniqueEstimator->AddElem(string(buf));
  }
  printf("%lld\n", uniqueEstimator->Estimate());
  delete uniqueEstimator;
}

void testTop()
{
  TopEstimator<int32_t> *topEst = TopEstimator<int32_t>::Create(3);
  topEst->AddWeightedElem("abc", 1);
  topEst->AddWeightedElem("def", 2);
  topEst->AddWeightedElem("ghi", 3);
  topEst->AddWeightedElem("def", 4);
  topEst->AddWeightedElem("jkl", 5);
  vector< TopEstimator<int32_t>::Elem > topElems;
  topEst->Estimate(topElems);
  cout << topElems[0].value << ", " << topElems[0].weight << endl;
  cout << topElems[1].value << ", " << topElems[1].weight << endl;
  cout << topElems[2].value << ", " << topElems[2].weight << endl;
  delete topEst;
}

int main()
{
  testSimple();
  testTop();
}
