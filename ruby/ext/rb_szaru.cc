#include "ruby.h"
#include "szaru.h"
// local include files
#include "converter.h"

extern "C" {
  void Init_szaru(void);
}

template<typename Value>
class RubyQuantileEstimator {
private:
  static void
  Free(SZaru::QuantileEstimator<Value> **ptr)
  {
    if (*ptr) {
      delete *ptr;
    }
  }
  
  static VALUE
  Alloc(VALUE klass)
  {
    SZaru::QuantileEstimator<Value> **ptr = ALLOC(SZaru::QuantileEstimator<Value>*);
    *ptr = NULL;
    return Data_Wrap_Struct(klass, 0, Free, ptr);
  }
  
  static VALUE
  Initialize(VALUE self, VALUE maxElems)
  {
    SZaru::QuantileEstimator<Value> **ptr;
    Data_Get_Struct(self, SZaru::QuantileEstimator<Value>*, ptr);
    *ptr = SZaru::QuantileEstimator<Value>::Create(NUM2LONG(maxElems));
    return Qnil;
  }
  
  static VALUE
  AddElem(VALUE self, VALUE elem)
  {
    SZaru::QuantileEstimator<Value> **te;
    Check_Type(elem, T_FIXNUM);
    Data_Get_Struct(self, SZaru::QuantileEstimator<Value>*, te);
    (*te)->AddElem(Converter<Value>::FromRuby(elem));
    return Qnil;
  }
  
  static VALUE
  Estimate(VALUE self)
  {
    SZaru::QuantileEstimator<Value> **te;
    Data_Get_Struct(self, SZaru::QuantileEstimator<Value>*, te);
    std::vector<Value> quantiles;
    (*te)->Estimate(quantiles);
    VALUE ary = rb_ary_new2(quantiles.size());
    for (int i = 0; i < quantiles.size(); i++) {
      rb_ary_push(ary, Converter<Value>::ToRuby(quantiles[i]));
    }
    return ary;
  }

public:

  static VALUE 
  Define(VALUE superModule, const char *name)
  {
    VALUE cQuantileEstimator = rb_define_class_under(superModule, name, rb_cObject);
    rb_define_alloc_func(cQuantileEstimator, Alloc);
    rb_define_private_method(cQuantileEstimator, "initialize", 
			     RUBY_METHOD_FUNC(Initialize), 1);
    rb_define_method(cQuantileEstimator, "add_elem", 
		     RUBY_METHOD_FUNC(AddElem), 1);
    rb_define_method(cQuantileEstimator, "estimate", 
		     RUBY_METHOD_FUNC(Estimate), 0);
    return cQuantileEstimator;
  }
};


template< typename Value >
class RubyTopEstimator {
private:

  static void
  Free(SZaru::TopEstimator<Value> **ptr)
  {
    if (*ptr) {
      delete *ptr;
    }
  }
  
  static VALUE
  Alloc(VALUE klass)
  {
    SZaru::TopEstimator<Value> **ptr = ALLOC(SZaru::TopEstimator<Value>*);
    *ptr = NULL;
    return Data_Wrap_Struct(klass, 0, Free, ptr);
  }

  static VALUE
  Initialize(VALUE self, VALUE maxElems)
  {
    SZaru::TopEstimator<Value> **ptr;
    Check_Type(maxElems, T_FIXNUM);
    Data_Get_Struct(self, SZaru::TopEstimator<Value>*, ptr);
    *ptr = SZaru::TopEstimator<Value>::Create(NUM2LONG(maxElems));
    return Qnil;
  }
  
  static VALUE
  AddElem(VALUE self, VALUE elem)
  {
    SZaru::TopEstimator<Value> **te;
    Check_Type(elem, T_STRING);
    Data_Get_Struct(self, SZaru::TopEstimator<Value>*, te);
    (*te)->AddElem(std::string(RSTRING_PTR(elem), RSTRING_LEN(elem)));
    return Qnil;
  }
  
  static VALUE
  Estimate(VALUE self)
  {
    SZaru::TopEstimator<Value> **te;
    Data_Get_Struct(self, SZaru::TopEstimator<Value>*, te);
    std::vector<typename SZaru::TopEstimator<Value>::Elem> topElems;
    (*te)->Estimate(topElems);
    VALUE ary = rb_ary_new2(topElems.size());
    for (int i = 0; i < topElems.size(); i++) {
      rb_ary_push(ary, rb_ary_new3(2, 
				   rb_str_new(topElems[i].value.c_str(), topElems[i].value.size()), 
				   Converter<Value>::ToRuby(topElems[i].weight)));
    }
    return ary;
    // return LONG2NUM(top);
  }

public:
  static VALUE 
  Define(VALUE superModule, const char *name)
  {
    VALUE cTopEstimator = rb_define_class_under(superModule, name, rb_cObject);
    rb_define_alloc_func(cTopEstimator, Alloc);
    rb_define_private_method(cTopEstimator, "initialize", 
			     RUBY_METHOD_FUNC(Initialize), 1);
    rb_define_method(cTopEstimator, "add_elem", 
		     RUBY_METHOD_FUNC(AddElem), 1);
    rb_define_method(cTopEstimator, "estimate", 
		     RUBY_METHOD_FUNC(Estimate), 0);
    return cTopEstimator;
  }

};


class RubyUniqueEstimator {
private:
  static void
  Free(SZaru::UniqueEstimator **ptr)
  {
    if (*ptr) {
      delete *ptr;
    }
  }
  
  static VALUE
  Alloc(VALUE klass)
  {
    SZaru::UniqueEstimator **ptr = ALLOC(SZaru::UniqueEstimator*);
    *ptr = NULL;
    return Data_Wrap_Struct(klass, 0, Free, ptr);
  }
  
  static VALUE
  Initialize(VALUE self, VALUE maxElems)
  {
    SZaru::UniqueEstimator **ptr;
    Data_Get_Struct(self, SZaru::UniqueEstimator*, ptr);
    *ptr = SZaru::UniqueEstimator::Create(NUM2LONG(maxElems));
    return Qnil;
  }
  
  static VALUE
  AddElem(VALUE self, VALUE elem)
  {
    SZaru::UniqueEstimator **ue;
    Check_Type(elem, T_STRING);
    Data_Get_Struct(self, SZaru::UniqueEstimator*, ue);
    (*ue)->AddElemInCIF(RSTRING_PTR(elem), RSTRING_LEN(elem));
    return Qnil;
  }
  
  static VALUE
  Estimate(VALUE self)
  {
    SZaru::UniqueEstimator **ue;
    Data_Get_Struct(self, SZaru::UniqueEstimator*, ue);
    uint64_t unique = (*ue)->Estimate();
    return LONG2NUM(unique);
  }

public:
  static VALUE
  Define(VALUE superModule, const char *name) {
    VALUE cUniqueEstimator = rb_define_class_under(superModule, name, rb_cObject);
    rb_define_alloc_func(cUniqueEstimator, Alloc);
    rb_define_private_method(cUniqueEstimator, "initialize", 
			     RUBY_METHOD_FUNC(Initialize), 1);
    rb_define_method(cUniqueEstimator, "add_elem", 
		     RUBY_METHOD_FUNC(AddElem), 1);
    rb_define_method(cUniqueEstimator, "estimate", 
		     RUBY_METHOD_FUNC(Estimate), 0);  
    return cUniqueEstimator;
  }
};

void
Init_szaru(void){
  VALUE mSZaru = rb_define_module("SZaru");
  // UniqueEstimator
  RubyUniqueEstimator::Define(mSZaru, "UniqueEstimator");

  // TopEstimator
  VALUE mTopEstimator = rb_define_module_under(mSZaru, "TopEstimator");
  RubyTopEstimator<double>::Define(mTopEstimator, "Double");
  RubyTopEstimator<int32_t>::Define(mTopEstimator, "Int32");
  RubyTopEstimator<int64_t>::Define(mTopEstimator, "Int64");
  
  // QuantileEstimator
  VALUE mQuantileEstimator = rb_define_module_under(mSZaru, "QuantileEstimator");
  RubyQuantileEstimator<double>::Define(mQuantileEstimator, "Double");
  RubyQuantileEstimator<int32_t>::Define(mQuantileEstimator, "Int32");
  RubyQuantileEstimator<int64_t>::Define(mQuantileEstimator, "Int64");
  
}
