require "mkmf"
dir_config('szaru')
if have_library('szaru')
  create_makefile('szaru')
end
