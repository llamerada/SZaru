VERSION = '0.1.0'
APPNAME = 'simple_szl_emitters'

top = '.'
out = 'build'

def options(ctx):
  ctx.tool_options('compiler_cxx')

def configure(ctx):
  ctx.check_tool('compiler_cxx')
  ctx.env.CXXFLAGS += ['-O2', '-Wall', '-g']

def build(bld):
  bld.recurse('src test')
