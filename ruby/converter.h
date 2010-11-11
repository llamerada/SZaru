// specialization of Conveter only for int32_t, int64_t, double


template< typename Value >
class Converter {
public:
  static inline VALUE ToRuby(Value value);
  static inline Value FromRuby(VALUE value);
};

template<> inline 
VALUE Converter<int32_t>::ToRuby(int32_t value){ 
  return INT2FIX(value);
}

template<> inline 
VALUE Converter<int64_t>::ToRuby(int64_t value){ 
  return LONG2FIX(value);
}

template<> inline 
VALUE Converter<double>::ToRuby(double value){ 
  return rb_float_new(value);
}

template<> inline 
int32_t Converter<int32_t>::FromRuby(VALUE value){ 
  return FIX2INT(value);
}

template<> inline 
int64_t Converter<int64_t>::FromRuby(VALUE value){ 
  return FIX2LONG(value);
}

template<> inline 
double Converter<double>::FromRuby(VALUE value){ 
  return RFLOAT(value)->value;
}

