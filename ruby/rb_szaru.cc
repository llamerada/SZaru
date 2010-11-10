#include "ruby.h"
#include "unique.h"
#include "topheap.h"
#include "szlsketch.h"
#include "top.h"
#include "quantile.h"

extern "C" {
  void Init_szaru(void);
}

// Int64QuantileEstimator start
static void
rb_Int64QuantileEstimator_Free(SZaru::QuantileEstimator<int64_t> **ptr)
{
  if (*ptr) {
    delete *ptr;
  }
}

static VALUE
rb_Int64QuantileEstimator_Alloc(VALUE klass)
{
  SZaru::QuantileEstimator<int64_t> **ptr = ALLOC(SZaru::QuantileEstimator<int64_t>*);
  *ptr = NULL;
  return Data_Wrap_Struct(klass, 0, rb_Int64QuantileEstimator_Free, ptr);
}

static VALUE
rb_Int64QuantileEstimator_Initialize(VALUE self, VALUE maxElems)
{
  SZaru::QuantileEstimator<int64_t> **ptr;
  Data_Get_Struct(self, SZaru::QuantileEstimator<int64_t>*, ptr);
  *ptr = SZaru::QuantileEstimatorFactory::CreateInt64(NUM2LONG(maxElems));
  return Qnil;
}

static VALUE
rb_Int64QuantileEstimator_AddElem(VALUE self, VALUE elem)
{
  SZaru::QuantileEstimator<int64_t> **te;
  Check_Type(elem, T_FIXNUM);
  Data_Get_Struct(self, SZaru::QuantileEstimator<int64_t>*, te);
  (*te)->AddElem(FIX2INT(elem));
  return Qnil;
}

static VALUE
rb_Int64QuantileEstimator_Estimate(VALUE self)
{
  SZaru::QuantileEstimator<int64_t> **te;
  Data_Get_Struct(self, SZaru::QuantileEstimator<int64_t>*, te);
  std::vector<int64_t> quantiles;
  (*te)->Estimate(quantiles);
  VALUE ary = rb_ary_new2(quantiles.size());
  for (int i = 0; i < quantiles.size(); i++) {
    rb_ary_push(ary, LONG2FIX(quantiles[i]));
  }
  return ary;
}
// Int64QuantileEstimatorg end

// TopEstimator start
static void
rb_TopEstimator_Free(SZaru::TopEstimator **ptr)
{
  if (*ptr) {
    delete *ptr;
  }
}

static VALUE
rb_TopEstimator_Alloc(VALUE klass)
{
  SZaru::TopEstimator **ptr = ALLOC(SZaru::TopEstimator*);
  *ptr = NULL;
  return Data_Wrap_Struct(klass, 0, rb_TopEstimator_Free, ptr);
}

static VALUE
rb_TopEstimator_Initialize(VALUE self, VALUE maxElems)
{
  SZaru::TopEstimator **ptr;
  Data_Get_Struct(self, SZaru::TopEstimator*, ptr);
  *ptr = SZaru::TopEstimator::Create(NUM2LONG(maxElems));
  return Qnil;
}

static VALUE
rb_TopEstimator_AddElem(VALUE self, VALUE elem)
{
  SZaru::TopEstimator **te;
  Check_Type(elem, T_STRING);
  Data_Get_Struct(self, SZaru::TopEstimator*, te);
  (*te)->AddElem(std::string(RSTRING_PTR(elem), RSTRING_LEN(elem)));
  return Qnil;
}

static VALUE
rb_TopEstimator_Estimate(VALUE self)
{
  SZaru::TopEstimator **te;
  Data_Get_Struct(self, SZaru::TopEstimator*, te);
  std::vector<SZaru::TopEstimator::Elem> topElems;
  (*te)->Estimate(topElems);
  VALUE ary = rb_ary_new2(topElems.size());
  for (int i = 0; i < topElems.size(); i++) {
    rb_ary_push(ary, rb_ary_new3(2, 
				 rb_str_new(topElems[i].value.c_str(), topElems[i].value.size()), 
				 rb_float_new(topElems[i].weight)));
  }
  return ary;
  // return LONG2NUM(top);
}
// TopEstimator end

// Sketch start
static void
rb_Sketch_Free(SZaru::SzlSketch **ptr)
{
  if (*ptr) {
    delete *ptr;
  }
}

static VALUE
rb_Sketch_Alloc(VALUE klass)
{
  SZaru::SzlSketch **ptr = ALLOC(SZaru::SzlSketch*);
  *ptr = NULL;
  return Data_Wrap_Struct(klass, 0, rb_Sketch_Free, ptr);
}

static VALUE
rb_Sketch_Initialize(VALUE self, VALUE totalSize)
{
  SZaru::SzlSketch **ptr;
  Data_Get_Struct(self, SZaru::SzlSketch*, ptr);
  int nTabs, tabSize;
  SZaru::SzlSketch::Dims(NUM2INT(totalSize), &nTabs, &tabSize);
  *ptr = new SZaru::SzlSketch(nTabs, tabSize);
  return Qnil;
}

// Sketch end

// TopHeap start
static void
rb_TopHeap_Free(SZaru::SzlSketch **ptr)
{
  if (*ptr) {
    delete *ptr;
  }
}

static VALUE
rb_TopHeap_Alloc(VALUE klass)
{
  SZaru::TopHeap **ptr = ALLOC(SZaru::TopHeap*);
  *ptr = NULL;
  return Data_Wrap_Struct(klass, 0, rb_TopHeap_Free, ptr);
}

static VALUE
rb_TopHeap_Initialize(VALUE self, VALUE maxElems)
{
  SZaru::TopHeap **ptr;
  Data_Get_Struct(self, SZaru::TopHeap*, ptr);
  *ptr = SZaru::TopHeap::Create(NUM2LONG(maxElems));
  return Qnil;
}

static VALUE
rb_TopHeap_AddNewElem(VALUE self, VALUE elem, VALUE value)
{
  SZaru::TopHeap **th;
  Check_Type(elem, T_STRING);
  Check_Type(value, T_FLOAT);;
  Data_Get_Struct(self, SZaru::TopHeap*, th);
  (*th)->AddNewElem(std::string(RSTRING_PTR(elem)), RFLOAT(value)->value);
  return Qnil;
}

static VALUE
rb_TopHeap_Smallest(VALUE self)
{
  SZaru::TopHeap **th;
  Data_Get_Struct(self, SZaru::TopHeap*, th);
  SZaru::TopHeap::Elem* elem = (*th)->Smallest();
  return rb_ary_new3(2, rb_str_new(elem->value.c_str(), elem->value.size()), rb_float_new(elem->weight));
}



// TopHeap end

// UniqueEstimator
static void
rb_UniqueEstimator_Free(SZaru::UniqueEstimator **ptr)
{
  if (*ptr) {
    delete *ptr;
  }
}

static VALUE
rb_UniqueEstimator_Alloc(VALUE klass)
{
  SZaru::UniqueEstimator **ptr = ALLOC(SZaru::UniqueEstimator*);
  *ptr = NULL;
  return Data_Wrap_Struct(klass, 0, rb_UniqueEstimator_Free, ptr);
}

static VALUE
rb_UniqueEstimator_Initialize(VALUE self, VALUE maxElems)
{
  SZaru::UniqueEstimator **ptr;
  Data_Get_Struct(self, SZaru::UniqueEstimator*, ptr);
  *ptr = SZaru::UniqueEstimator::Create(NUM2LONG(maxElems));
  return Qnil;
}

static VALUE
rb_UniqueEstimator_AddElem(VALUE self, VALUE elem)
{
  SZaru::UniqueEstimator **ue;
  Check_Type(elem, T_STRING);
  Data_Get_Struct(self, SZaru::UniqueEstimator*, ue);
  (*ue)->AddElemInCIF(RSTRING_PTR(elem), RSTRING_LEN(elem));
  return Qnil;
}

static VALUE
rb_UniqueEstimator_Estimate(VALUE self)
{
  SZaru::UniqueEstimator **ue;
  Data_Get_Struct(self, SZaru::UniqueEstimator*, ue);
  uint64_t unique = (*ue)->Estimate();
  return LONG2NUM(unique);
}

void
Init_szaru(void){
  VALUE mSZaru = rb_define_module("SZaru");
  // UniqueEstimator
  VALUE cUniqueEstimator = rb_define_class_under(mSZaru, "UniqueEstimator", rb_cObject);
  rb_define_alloc_func(cUniqueEstimator, rb_UniqueEstimator_Alloc);
  rb_define_private_method(cUniqueEstimator, "initialize", 
			   RUBY_METHOD_FUNC(rb_UniqueEstimator_Initialize), 1);
  rb_define_method(cUniqueEstimator, "add_elem", 
		   RUBY_METHOD_FUNC(rb_UniqueEstimator_AddElem), 1);
  rb_define_method(cUniqueEstimator, "estimate", 
		   RUBY_METHOD_FUNC(rb_UniqueEstimator_Estimate), 0);

  // TopEstimator
  VALUE cTopEstimator = rb_define_class_under(mSZaru, "TopEstimator", rb_cObject);
  rb_define_alloc_func(cTopEstimator, rb_TopEstimator_Alloc);
  rb_define_private_method(cTopEstimator, "initialize", 
			   RUBY_METHOD_FUNC(rb_TopEstimator_Initialize), 1);
  rb_define_method(cTopEstimator, "add_elem", 
		   RUBY_METHOD_FUNC(rb_TopEstimator_AddElem), 1);
  rb_define_method(cTopEstimator, "estimate", 
		   RUBY_METHOD_FUNC(rb_TopEstimator_Estimate), 0);

  // Int64QuantileEstimator
  VALUE cInt64QuantileEstimator = rb_define_class_under(mSZaru, "Int64QuantileEstimator", rb_cObject);
  rb_define_alloc_func(cInt64QuantileEstimator, rb_Int64QuantileEstimator_Alloc);
  rb_define_private_method(cInt64QuantileEstimator, "initialize", 
			   RUBY_METHOD_FUNC(rb_Int64QuantileEstimator_Initialize), 1);
  rb_define_method(cInt64QuantileEstimator, "add_elem", 
		   RUBY_METHOD_FUNC(rb_Int64QuantileEstimator_AddElem), 1);
  rb_define_method(cInt64QuantileEstimator, "estimate", 
		   RUBY_METHOD_FUNC(rb_Int64QuantileEstimator_Estimate), 0);

  // TopHeap
  VALUE cTopHeap = rb_define_class_under(mSZaru, "TopHeap", rb_cObject);
  rb_define_alloc_func(cTopHeap, rb_TopHeap_Alloc);
  rb_define_private_method(cTopHeap, "initialize", 
			   RUBY_METHOD_FUNC(rb_TopHeap_Initialize), 1);
  rb_define_method(cTopHeap, "add_new_elem", 
		   RUBY_METHOD_FUNC(rb_TopHeap_AddNewElem), 2);
  rb_define_method(cTopHeap, "smallest", 
		   RUBY_METHOD_FUNC(rb_TopHeap_Smallest), 0);

  // Sketch
  VALUE cSketch = rb_define_class_under(mSZaru, "Sketch", rb_cObject);
  rb_define_alloc_func(cSketch, rb_Sketch_Alloc);
  rb_define_private_method(cSketch, "initialize", 
			   RUBY_METHOD_FUNC(rb_Sketch_Initialize), 1);
  // rb_define_method(cSketch, "add_new_elem", 
  // RUBY_METHOD_FUNC(rb_Sketch_AddNewElem), 2);
  // rb_define_method(cSketch, "smallest", 
  //		   RUBY_METHOD_FUNC(rb_Sketch_Smallest), 0);
}
