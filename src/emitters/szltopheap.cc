// Copyright 2010 Google Inc.
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

#include <assert.h>
#include <string>
#include <vector>
#include <utility>

#include "public/porting.h"
#include "public/hash_map.h"
#include "public/logging.h"
#include "public/hashutils.h"

// #include "public/szltype.h"
// #include "public/szlvalue.h"
// #include "public/szlencoder.h"
// #include "public/szldecoder.h"
// #include "public/szltabentry.h"

#include "emitters/szltopheap.h"

namespace SZaru {

TopHeap *
TopHeap::Create(int maxElems) {
  return new SzlTopHeap(maxElems);
}

// Helper classes for making hashes work.
struct SzlTopHeapEq {
  bool operator()(const string* s1, const string* s2) const {
    return *s1 == *s2;
  }
};

struct SzlTopHeapHash {
  size_t operator()(const string* s) const {
    return Hash32StringWithSeed(s->data(), s->size(), 0);
  }
};

SzlTopHeap::SzlTopHeap(uint32_t  maxElems)
  : heap_(new vector<Elem*>),
    hash_(new TopHash(5)),    // Pre-allocate room for a few buckets.
                              // By default, hash_map allocates 100 entries,
                              // way too many.
    maxElems_(maxElems) {
}

SzlTopHeap::~SzlTopHeap() {
  Clear();
  delete hash_;
  delete heap_;
}

void SzlTopHeap::Clear() {
  for (size_t i = 0; i < heap_->size(); i++) {
    delete (*heap_)[i];
  }
  heap_->clear();
  hash_->clear();
}

SzlTopHeap::Elem* SzlTopHeap::Find(const string& s) {
  TopHash::iterator it = hash_->find(&s);
  if (it == hash_->end())
    return NULL;
  return it->second;
}

void SzlTopHeap::AddNewElem(const string& value, const double w) {
  // CHECK(heap_->size() < maxElems_);
  Elem* e = new Elem;
  e->value = value;
  e->weight = w;
  e->heap = heap_->size();
  heap_->push_back(e);
  FixHeapUp(heap_->size() - 1);
  int bucks = hash_->bucket_count();
  hash_->insert(pair<const string*, Elem*>(&e->value, e));
  bucks = hash_->bucket_count() - bucks;
  bucks = MaxInt(0, bucks);
 }

void SzlTopHeap::ReplaceSmallest(const string& value, const double w) {
  // CHECK(heap_->size() > 0);
  Elem* smallest = (*heap_)[0];
  hash_->erase(&smallest->value);
  smallest->value = value;
  smallest->weight = w;
  hash_->insert(pair<const string*, Elem*>(&smallest->value, smallest));
  FixHeapDown(0, heap_->size());
}

// Add to the weight of e.
void SzlTopHeap::AddToWeight(const double w, Elem* e) {
  assert(e != NULL);
  e->weight += w;
  FixHeap(e->heap);
}

// Sort, destroying heap.
void SzlTopHeap::Sort() {
  int ne = heap_->size();
  if (!ne)
    return;

  while (--ne > 0) {
    Elem* e = (*heap_)[0];
    (*heap_)[0] = (*heap_)[ne];
    (*heap_)[ne] = e;
    FixHeapDown(0, ne);
  }
}

// Restore to a heap after sorting; simply reverse the sort.
void SzlTopHeap::ReHeap() {
  int ne = heap_->size();
  int nswap = ne >> 1;
  for (int i = 0; i < nswap; i++) {
    Elem* e = (*heap_)[i];
    Elem* e2 = (*heap_)[ne - 1 - i];
    (*heap_)[i] = e2;
    e2->heap = i;
    (*heap_)[ne - 1 - i] = e;
    e->heap = ne - 1 - i;
  }
  if (ne & 1)
    (*heap_)[nswap]->heap = nswap;
  assert(IsHeap());
}

// Move an element up the heap to its proper position.
void SzlTopHeap::FixHeapUp(int h) {
  assert(h >= 0 && h <  heap_->size());
  Elem* e = (*heap_)[h];
  const double w = e->weight;

  while (h != 0) {
    int parent = (h - 1) >> 1;
    Elem* pe = (*heap_)[parent];
    assert(pe != NULL);
    // original: "if (!less_->Cmp(w, pe->weight))"
    if (w >= pe->weight)
       break;
    (*heap_)[h] = pe;
    pe->heap = h;
    h = parent;
  }

  (*heap_)[h] = e;
  e->heap = h;
}

// Move an element down the heap to its proper position.
void SzlTopHeap::FixHeapDown(int h, int nheap) {
  assert(h >= 0 && h < nheap);
  Elem* e = (*heap_)[h];
  const double w = e->weight;

  for (;;) {
    int kid = (h << 1) + 1;
    if (kid >= nheap)
      break;
    Elem* ke = (*heap_)[kid];
    double kw = ke->weight;
    if (kid + 1 < nheap) {
      Elem* ke1 = (*heap_)[kid + 1];
      double kw1 = ke1->weight;
      //if (less_->Cmp(*kw1, *kw)) {
      if (kw1 < kw) {
        ke = ke1;
        kw = kw1;
        ++kid;
      }
    }
    // if (less_->Cmp(w, *kw))
    if (w < kw)
      break;
    (*heap_)[h] = ke;
    ke->heap = h;
    h = kid;
  }

  (*heap_)[h] = e;
  e->heap = h;
}

// Element h in the heap needs to be moved to the
// proper position, which may be either up or down.
// It is the only element whose weight has changed
// since the heap was last consistent.
void SzlTopHeap::FixHeap(int h) {
  assert(h >= 0 && h < heap_->size());

  // Fix up the heap if smaller than parent
  // original: if (h != 0 && less_->Cmp((*heap_)[h]->weight, (*heap_)[(h - 1) >> 1]->weight))
  if (h != 0 && ((*heap_)[h]->weight < (*heap_)[(h - 1) >> 1]->weight))
    FixHeapUp(h);
  else
    FixHeapDown(h, heap_->size());
}

// Check that the heap really is a heap.
bool SzlTopHeap::IsHeap() {
  for (int i = 1; i < heap_->size(); ++i) {
    int parent = (i - 1) >> 1;
    if ((*heap_)[i] == NULL
	|| (*heap_)[parent] == NULL
	// || original: less_->Cmp((*heap_)[i]->weight, (*heap_)[parent]->weight)
	|| (*heap_)[i]->weight < (*heap_)[parent]->weight
	|| (*heap_)[i]->heap != i)
      return false;
  }
  return true;
}

}
