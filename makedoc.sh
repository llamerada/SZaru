#! /bin/sh
rm -rf doc
doxygen Doxyfile
rm -rf ../szaru-doc/c++
cp -rp doc ../szaru-doc/c++