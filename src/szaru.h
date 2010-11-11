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

#ifndef _SZARU_
#define _SZARU_

#include <stdint.h>
#include <string>
#include <vector>

namespace SZaru{
  
class UniqueEstimator {
public:
  // factory
  static UniqueEstimator* Create(int maxElems);
  
  virtual ~UniqueEstimator() {};
  
  // Add a new element to this entry.
  virtual void AddElem(const std::string& elm) = 0;

  // Add a new element to this entry.
  virtual void AddElemInCIF(const char *data, size_t size_t) = 0;

  // Estimate the number of unique entries.
  // estimate = (maxelems << bits-in-hash) / biggest-small-elem
  virtual int64_t Estimate() const = 0;

  // Get the number of elements added to this entry in the table.
  virtual uint64_t TotElems() const = 0;

protected:
  UniqueEstimator() {}
};

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

template <>
TopEstimator<int32_t>* 
TopEstimator<int32_t>::Create(uint32_t numTops);

template <>
TopEstimator<int64_t>* 
TopEstimator<int64_t>::Create(uint32_t numTops);

template <>
TopEstimator<double>* 
TopEstimator<double>::Create(uint32_t numTops);

// Note; only double, int32_t, int64_t 
template <typename Key>
class QuantileEstimator {
public:
  // factory
  static QuantileEstimator* Create(uint32_t numQuantiles);

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

template <>
QuantileEstimator<int32_t>* 
QuantileEstimator<int32_t>::Create(uint32_t numQuantiles);

template <>
QuantileEstimator<int64_t>* 
QuantileEstimator<int64_t>::Create(uint32_t numQuantiles);

template <>
QuantileEstimator<double>* 
QuantileEstimator<double>::Create(uint32_t numQuantiles);

}

#endif  //  _SZARU_
