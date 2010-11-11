// Copyright 2010 Yuji Kaneda
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------

#ifndef _SZARU_TOP_
#define _SZARU_TOP_

#include <stdint.h>
#include <string>
#include <vector>

namespace SZaru{

template<typename Value>
class TopEstimator {
public:
  // factory
  static TopEstimator* Create(uint32_t numTops);
  
  virtual ~TopEstimator() {};

  // Combination of a value & weight.
  struct Elem {
    std::string value;
    Value weight;
  };
  
  // Add a new element to this entry.
  virtual void AddElem(const std::string& elm) = 0;

  // Add a new element  with weight to this entry.
  virtual void AddWeightedElem(const std::string& elem, Value weight) = 0;
  
  // Estimate the number of top entries.
  // estimate = (maxelems << bits-in-hash) / biggest-small-elem
  virtual void Estimate(std::vector<Elem>& topElems) = 0;
  
  // Get the number of elements added to this entry in the table.
  virtual uint64_t TotElems() const = 0;

protected:
  TopEstimator() {}
};

// factory class
class TopEstimatorFactory {
public:
  static TopEstimator<int32_t>* CreateInt32(uint32_t numTops);
  static TopEstimator<int64_t>* CreateInt64(uint32_t numTops);
  static TopEstimator<double>* CreateDouble(uint32_t numTops);
};

template <>
TopEstimator<int32_t>* 
TopEstimator<int32_t>::Create(uint32_t numTops) {
  return TopEstimatorFactory::CreateInt32(numTops);
}

template <>
TopEstimator<int64_t>* 
TopEstimator<int64_t>::Create(uint32_t numTops) {
  return TopEstimatorFactory::CreateInt64(numTops);
}

template <>
TopEstimator<double>* 
TopEstimator<double>::Create(uint32_t numTops) {
  return TopEstimatorFactory::CreateDouble(numTops);
}

}

#endif  //  _SZARU_TOP_
