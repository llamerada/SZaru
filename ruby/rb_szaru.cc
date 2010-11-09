#include "ruby.h"
#include "unique.h"
#include "topheap.h"

extern "C" {
  void Init_szaru(void);
}

// TopHeap start
static void
rb_TopHeap_Free(SZaru::TopHeap **ptr)
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
  (*ue)->AddElem(RSTRING_PTR(elem), RSTRING_LEN(elem));
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

  // TopHeap
  VALUE cTopHeap = rb_define_class_under(mSZaru, "TopHeap", rb_cObject);
  rb_define_alloc_func(cTopHeap, rb_TopHeap_Alloc);
  rb_define_private_method(cTopHeap, "initialize", 
			   RUBY_METHOD_FUNC(rb_TopHeap_Initialize), 1);
  rb_define_method(cTopHeap, "add_new_elem", 
		   RUBY_METHOD_FUNC(rb_TopHeap_AddNewElem), 2);
  rb_define_method(cTopHeap, "smallest", 
		   RUBY_METHOD_FUNC(rb_TopHeap_Smallest), 0);
}
