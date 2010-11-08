VERSION = '0.1.0'
APPNAME = 'SZaru'

top = '.'
out = 'build'

def options(opt):
  opt.load('compiler_cxx')

def configure(opt):
  opt.load('compiler_cxx')
  opt.env.CXXFLAGS += ['-O2', '-Wall', '-g']

def build(bld):
  bld.recurse('src test')
