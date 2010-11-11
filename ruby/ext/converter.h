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

// specialization of Conveter only for int32_t, int64_t, double
template< typename Value >
class Converter {
public:
  static inline VALUE ToRuby(Value value);
  static inline Value FromRuby(VALUE value);
  static inline void CheckType(VALUE value);
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

template<> inline 
void Converter<int32_t>::CheckType(VALUE value){ 
  Check_Type(value, T_FIXNUM);
}

template<> inline 
void Converter<int64_t>::CheckType(VALUE value){ 
  Check_Type(value, T_FIXNUM);
}

template<> inline 
void Converter<double>::CheckType(VALUE value){ 
  Check_Type(value, T_FLOAT);
}

