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
  static inline PyObject* ToPy(Value value);
  static inline Value FromPy(PyObject* value);
  static inline const std::string Name();
};

template<> inline 
PyObject* Converter<int32_t>::ToPy(int32_t value){ 
  return Py_BuildValue("i", value);
}

template<> inline 
PyObject* Converter<int64_t>::ToPy(int64_t value){ 
  return Py_BuildValue("i", value);
}

template<> inline 
PyObject* Converter<double>::ToPy(double value){ 
  return PyFloat_FromDouble(value);
}

template<> inline 
int32_t Converter<int32_t>::FromPy(PyObject* value){ 
  return PyInt_AsLong(value);
}

template<> inline 
int64_t Converter<int64_t>::FromPy(PyObject* value){ 
  return PyInt_AsLong(value);
}

template<> inline 
double Converter<double>::FromPy(PyObject* value){ 
  return PyFloat_AS_DOUBLE(value);
}

template<> inline 
const std::string Converter<int32_t>::Name(){ 
  return std::string("Int32");
}

template<> inline 
const std::string Converter<int64_t>::Name(){ 
  return std::string("Int64");
}

template<> inline 
const std::string Converter<double>::Name(){ 
  return std::string("Double");
}



