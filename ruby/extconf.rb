require "mkmf"
$CFLAGS = "-I../src/emitters -L../build/src"
$LDFLAGS = "-L../build/src"
dir_config('szaru')
if have_library('szaru')
  create_makefile('szaru')
end