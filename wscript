VERSION = '0.1.0'
APPNAME = 'simple_szl_emitters'

top = '.'
out = 'build'

def options(ctx):
  ctx.tool_options('compiler_cxx')
  # ctx.tool_options('unittestt')

def configure(ctx):
  ctx.check_tool('compiler_cxx')
  # ctx.check_tool('unittestt')	
  # ctx.check_cfg(package = 'eigen3')
  ctx.env.CXXFLAGS += ['-O2', '-Wall', '-g']

# import Scripting
# Scripting.dist_exts += ['.sh']

# def dist_hook():
#    import os
#    os.remove('googlecode_upload.py')

def build(bld):
  # bld.recurse('src test sample')
  bld.recurse('src test')
