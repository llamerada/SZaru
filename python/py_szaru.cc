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

// Python Binding of SZaru

#include <Python.h>
#include <szaru.h>
#include <cstring>
#include "converter.h"

extern "C" {
  void initszaru(void);
}

namespace {

PyTypeObject CreatePyTypeObject() {
  PyTypeObject type = { PyVarObject_HEAD_INIT(NULL, 0) };
  size_t zoff = offsetof(PyTypeObject, tp_name);
  std::memset((char*)&type + zoff, 0, sizeof(type) - zoff);
  return type;
}


class PythonUniqueEstimator {
public:
  typedef struct {
    PyObject HEAD;
    SZaru::UniqueEstimator *unqEst;
  } PyData;

  static PyObject*
  New(PyTypeObject* pytype, PyObject* pyargs, PyObject* pykwds) {
    PyData *data = (PyData*)pytype->tp_alloc(pytype, 0);
    if (!data) { return  NULL; }
    data->unqEst = NULL;
    return (PyObject*)data;
  }

  static void 
  Dealloc(PyData *data) {
    delete data->unqEst;
    Py_TYPE(data)->tp_free((PyObject*)data);
  }

  static int
  Init(PyData* self, PyObject* args, PyObject* kwds) {
    uint32_t maxElems;
    if (!PyArg_ParseTuple(args, "i", &maxElems))
      return -1;
    self->unqEst = SZaru::UniqueEstimator::Create(maxElems);
    return 0;
  }
    
    
  static PyObject*
  AddElem(PyData *self, PyObject *args)
  {
    const char* elem;
    size_t len;
    if (!PyArg_ParseTuple(args, "s#", &elem, &len))
      return NULL;
    self->unqEst->AddElemInCIF(elem, len);
    Py_RETURN_NONE;
  }

  static PyObject*
  Estimate(PyData *self)
  {
    int64_t nUnique = self->unqEst->Estimate();
    return Py_BuildValue("i", nUnique);
  }

  static bool Define(PyObject *superModule, const char* name) {
    // is it necessary using static ?
    static PyTypeObject tUnqEst = CreatePyTypeObject();   
    tUnqEst.tp_name = "szaru.UniqueEstimator";
    tUnqEst.tp_basicsize = sizeof(PyData);
    tUnqEst.tp_itemsize = 0;
    tUnqEst.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    tUnqEst.tp_doc = "Statistical estimators for the total number of unique data items.";
    tUnqEst.tp_new = New;
    tUnqEst.tp_dealloc = (destructor)Dealloc;
    tUnqEst.tp_init = (initproc)Init;
    static PyMethodDef methods[] = {
      { 
	"add_elem", (PyCFunction)AddElem, METH_VARARGS, 
	"Add a new element to this entry."
      },
      { 
	"estimate", (PyCFunction)Estimate, METH_NOARGS, 
	"Return the estimated number of unique entries."
      },
      { NULL, NULL, 0, NULL }
    };
    tUnqEst.tp_methods = methods;
    if (PyType_Ready(&tUnqEst) != 0) return false;
    Py_INCREF(&tUnqEst);
    if (PyModule_AddObject(superModule, name, reinterpret_cast<PyObject*>(&tUnqEst)) != 0) return false;
    return true;
  }
  
};

template<typename Value>
class PythonTopEstimator {
public:
  typedef struct {
    PyObject HEAD;
    SZaru::TopEstimator<Value> *topEst;
  } PyData;

  static PyObject*
  New(PyTypeObject* pytype, PyObject* pyargs, PyObject* pykwds) {
    PyData *data = (PyData*)pytype->tp_alloc(pytype, 0);
    if (!data) { return  NULL; }
    data->topEst = NULL;
    return (PyObject*)data;
  }

  static void 
  Dealloc(PyData *data) {
    delete data->topEst;
    Py_TYPE(data)->tp_free((PyObject*)data);
  }

  static int
  Init(PyData* self, PyObject* args, PyObject* kwds) {
    uint32_t maxElems;
    if (!PyArg_ParseTuple(args, "i", &maxElems))
      return -1;
    self->topEst = SZaru::TopEstimator<Value>::Create(maxElems);
    return 0;
  }
    
    
  static PyObject*
  AddElem(PyData *self, PyObject *args)
  {
    const char* elem;
    if (!PyArg_ParseTuple(args, "s", &elem))
      return NULL;
    self->topEst->AddElem(std::string(elem));
    Py_RETURN_NONE;
  }

  static PyObject*
  AddWeightedElem(PyData *self, PyObject *args)
  {
    const char* elem;
    PyObject *weight;
    if (!PyArg_ParseTuple(args, "sO", &elem, &weight))
      return NULL;
    self->topEst->AddWeightedElem(std::string(elem), 
				  Converter<Value>::FromPy(weight));
    Py_RETURN_NONE;
  }

  static PyObject*
  Estimate(PyData *self)
  {
    std::vector<typename SZaru::TopEstimator<Value>::Elem> topElems;
    self->topEst->Estimate(topElems);
    PyObject *lst = PyList_New(topElems.size());
    if (!lst) return NULL;
    for (size_t i = 0; i < topElems.size(); i++) {
      PyObject *elmLst = PyList_New(2);
      if (!elmLst) {
	Py_DECREF(lst);
	return NULL;
      }
      PyList_SET_ITEM(elmLst, 0, Py_BuildValue("s#", 
					       topElems[i].value.c_str(),
					       topElems[i].value.size()));
      PyList_SET_ITEM(elmLst, 1, Converter<Value>::ToPy(topElems[i].weight));
      
      PyList_SET_ITEM(lst, i, elmLst);
    }
    return lst;
  }

  static bool Define(PyObject *superModule, const char* name) {
    // is it necessary using static ?
    static PyTypeObject tTopEst = CreatePyTypeObject();   
    const char* tp_name = (std::string("szaru.TopEstimator") + Converter<Value>::Name()).c_str();
    tTopEst.tp_name = strdup(tp_name); // alloc memory
    tTopEst.tp_itemsize = 0;
    tTopEst.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    tTopEst.tp_doc = "Statistical samplings that record the 'top N' data items.";
    tTopEst.tp_new = New;
    tTopEst.tp_dealloc = (destructor)Dealloc;
    tTopEst.tp_init = (initproc)Init;
    static PyMethodDef methods[] = {
      { 
	"add_elem", (PyCFunction)AddElem, METH_VARARGS, 
	"Add a new element to this entry."
      },
      { 
	"add_weighted_elem", (PyCFunction)AddWeightedElem, METH_VARARGS, 
	"Add a new element with weight to this entry."
      },
      { 
	"estimate", (PyCFunction)Estimate, METH_NOARGS, 
	"Return the estimated top entries."
      },
      { NULL, NULL, 0, NULL }
    };
    tTopEst.tp_methods = methods;
    if (PyType_Ready(&tTopEst) != 0) return false;
    Py_INCREF(&tTopEst);
    if (PyModule_AddObject(superModule, name, reinterpret_cast<PyObject*>(&tTopEst)) != 0) return false;
    return true;
  }
  
};

template<typename Key>
class PythonQuantileEstimator {
public:
  typedef struct {
    PyObject HEAD;
    SZaru::QuantileEstimator<Key> *qtlEst;
  } PyData;

  static PyObject*
  New(PyTypeObject* pytype, PyObject* pyargs, PyObject* pykwds) {
    PyData *data = (PyData*)pytype->tp_alloc(pytype, 0);
    if (!data) { return  NULL; }
    data->qtlEst = NULL;
    return (PyObject*)data;
  }

  static void 
  Dealloc(PyData *data) {
    delete data->qtlEst;
    Py_TYPE(data)->tp_free((PyObject*)data);
  }

  static int
  Init(PyData* self, PyObject* args, PyObject* kwds) {
    uint32_t maxElems;
    if (!PyArg_ParseTuple(args, "i", &maxElems))
      return -1;
    self->qtlEst = SZaru::QuantileEstimator<Key>::Create(maxElems);
    return 0;
  }
    
    
  static PyObject*
  AddElem(PyData *self, PyObject *args)
  {
    PyObject *elem;
    if (!PyArg_ParseTuple(args, "O", &elem))
      return NULL;
    self->qtlEst->AddElem(Converter<Key>::FromPy(elem));
    Py_RETURN_NONE;
  }

  static PyObject*
  Estimate(PyData *self)
  {
    std::vector<Key> quantiles;
    self->qtlEst->Estimate(quantiles);
    PyObject *lst = PyList_New(quantiles.size());
    if (!lst) return NULL;
    for (size_t i = 0; i < quantiles.size(); i++) {
      PyList_SET_ITEM(lst, i, Converter<Key>::ToPy(quantiles[i]));
    }
    return lst;
  }

  static bool Define(PyObject *superModule, const char* name) {
    // is it necessary using static ?
    static PyTypeObject tQuantileEst = CreatePyTypeObject();
    const char* tp_name = (std::string("szaru.QuantileEstimator") + Converter<Key>::Name()).c_str();
    tQuantileEst.tp_name = strdup(tp_name); // alloc memory
    tQuantileEst.tp_basicsize = sizeof(PyData);
    tQuantileEst.tp_itemsize = 0;
    tQuantileEst.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    tQuantileEst.tp_doc = "Statistical samplings that record the 'Quantile N' data items.";
    tQuantileEst.tp_new = New;
    tQuantileEst.tp_dealloc = (destructor)Dealloc;
    tQuantileEst.tp_init = (initproc)Init;
    static PyMethodDef methods[] = {
      { 
	"add_elem", (PyCFunction)AddElem, METH_VARARGS, 
	"Add a new element to this entry."
      },
      { 
	"estimate", (PyCFunction)Estimate, METH_NOARGS, 
	"Return the estimated Quantile entries."
      },
      { NULL, NULL, 0, NULL }
    };
    tQuantileEst.tp_methods = methods;
    if (PyType_Ready(&tQuantileEst) != 0) return false;
    Py_INCREF(&tQuantileEst);
    if (PyModule_AddObject(superModule, name, reinterpret_cast<PyObject*>(&tQuantileEst)) != 0) return false;
    return true;
  }
  
};


}

/**
 * Entry point of the library.
 */
PyMODINIT_FUNC initszaru(void)
{
  static PyMethodDef method_def[] = {
    {NULL, NULL, 0, NULL}
  };
  PyObject *mSZaru = Py_InitModule("szaru", method_def);
  PyModule_AddStringConstant(mSZaru, "VERSION", SZaru::VERSION);

  PythonUniqueEstimator::Define(mSZaru, "UniqueEstimator");

  PythonTopEstimator<int32_t>::Define(mSZaru, "TopEstimatorInt32");
  PythonTopEstimator<int64_t>::Define(mSZaru, "TopEstimatorInt64");
  PythonTopEstimator<double>::Define(mSZaru, "TopEstimatorDouble");

  PythonQuantileEstimator<int32_t>::Define(mSZaru, "QuantileEstimatorInt32");
  PythonQuantileEstimator<int64_t>::Define(mSZaru, "QuantileEstimatorInt64");
  PythonQuantileEstimator<double>::Define(mSZaru, "QuantileEstimatorDouble");
}
