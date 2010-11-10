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
  
class TopEstimator {
public:
  // factory
  static TopEstimator* Create(int maxElems);
  
  virtual ~TopEstimator() {};

  // Combination of a value & weight.
  struct Elem {
    std::string value;
    double weight;
  };
  
  // Add a new element to this entry.
  virtual void AddElem(const std::string& elm) = 0;

  // Add a new element  with weight to this entry.
  virtual void AddWeightedElem(const std::string& elem, double weight) = 0;

  // Estimate the number of top entries.
  // estimate = (maxelems << bits-in-hash) / biggest-small-elem
  virtual void Estimate(std::vector<Elem>& topElems) = 0;
  
  // Get the number of elements added to this entry in the table.
  virtual uint64_t TotElems() const = 0;

protected:
  TopEstimator() {}
};

}

#endif  //  _SZARU_TOP_
