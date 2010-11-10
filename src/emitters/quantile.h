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

#ifndef _SZARU_QUANTILE_
#define _SZARU_QUANTILE_

#include <stdint.h>

namespace SZaru{

template <typename Key>
class QuantileEstimator {
public:
  virtual ~QuantileEstimator() {};
  
  // Add a new element to this entry.
  virtual void AddElem(const Key& elm) = 0;

  // Estimate the quantile entries.
  virtual void Estimate(std::vector<Key>& output) = 0;

  // Get the number of elements added to this entry in the table.
  virtual uint64_t TotElems() const = 0;

protected:
  QuantileEstimator() {}
};

// factory class
class QuantileEstimatorFactory {
public:
  static QuantileEstimator<int32_t>* CreateInt32(uint32_t numQuantiles);
  static QuantileEstimator<int64_t>* CreateInt64(uint32_t numQuantiles);
  static QuantileEstimator<double>* CreateDouble(uint32_t numQuantiles);
};

}

#endif  //  _SZARU_QUANTILE_
