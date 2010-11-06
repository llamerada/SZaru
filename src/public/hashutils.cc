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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include <string>
#include <utility>

#include "public/porting.h"
#include "public/logging.h"
#include "public/hashutils.h"

//============================================================================
// MD5 hash

void MD5Digest(const void* data, size_t length,
               uint8 (*digest)[MD5_DIGEST_LENGTH]) {
  MD5_CTX md;
  MD5_Init(&md);
  MD5_Update(&md, data, length);
  MD5_Final(*digest, &md);
}
