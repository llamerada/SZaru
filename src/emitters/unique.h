// Copyright 2010 Google Inc.
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

#ifndef _SZARU_UNIQUE_
#define _SZARU_UNIQUE_

#include <stdint.h>

namespace SZaru{

class UniqueEstimator {
protected:
  UniqueEstimator() {}
  
public:
  virtual ~UniqueEstimator();
  
  // Add a new element to this entry.
  virtual void AddElem(const std::string& elm);
  virtual int64_t Estimate() const;

  // ToDo: move to super class
  // Get the number of elements added to this entry in the table.
  virtual uint64_t TotElems() const;

  static UniqueEstimator* Create(int maxElems);
};

}

#endif  //  _SZARU_UNIQUE_
