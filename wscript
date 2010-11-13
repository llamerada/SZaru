#! /usr/bin/env python
# encoding: utf-8

VERSION = '0.1.0'
APPNAME = 'SZaru'

top = '.'
out = 'build'

def options(opt):
  opt.load('compiler_cxx')


# check hash_set / hash_map bsed on szl/m4/slt_hash.m4
def check_hash(conf):
  found = False
  conf.start_msg('Checking for the location of hash_map')
  for location in ["tr1/unordered_map", "ext/hash_map", "hash_map"]:
    for namespace in ["std::tr1", "__gnu_cxx", "", "std", "stdext"]:
      for name in ["unordered_map", "hash_map"]:
        if not found and check_hash_snippet(conf, location, namespace, name):
          found = True
          define_config(conf, location, namespace, name)
  conf.end_msg('could not find an STL hash_map', 'YELLOW')

def define_config(conf, location, namespace, name):
  hash_map_header = "<%s>" % location
  hash_namespece = namespace
  hash_map_class = name
  hash_set_header = hash_map_header.replace("map", "set")
  hash_set_class = hash_map_class.replace("map", "set")
  conf.define("HAVE_HASH_MAP", 1) 
  conf.define("HAVE_HASH_SET", 1)
  conf.define("HASH_MAP_H", hash_map_header, quote=False)
  conf.define("HASH_SET_H", hash_set_header, quote=False)
  conf.define("HASH_MAP_CLASS", hash_map_class, quote=False)
  conf.define("HASH_SET_CLASS", hash_set_class, quote=False)
  conf.define("HASH_NAMESPACE", hash_namespece, quote=False)
  conf.end_msg(hash_map_header)


def check_hash_snippet(conf, location, namespace, name):
  fragment = """
  #include <%s>
  const %s::%s<int, int> t;
  int main(){ t.find(1); }
  """ % (location, namespace, name)
  k = []
  kw = {
    'fragment' : fragment,
    'compiler' : 'cxx',
    }
  conf.validate_c(kw)
  # conf.start_msg(kw['msg'])
  ret=None
  try:
    ret = conf.run_c_code(*k,**kw)
  except conf.errors.ConfigurationError ,e:
    pass
  else:
    kw['success']=ret
  conf.post_check(*k,**kw)
  if isinstance(ret,int):
    return ret == 0
  return ret


def configure(conf):
  conf.load('compiler_cxx')
  
  # conf.env.CXXFLAGS += ['-O2', '-Wall', '-g']
  conf.check_cxx(lib = 'crypto', cxxflags = ['-O2', '-Wall', '-g'])
  check_hash(conf)

  
  conf.write_config_header('config.h')

def build(bld):
  bld.recurse('src test')
