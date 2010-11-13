#! /bin/sh
rm -rf doc
doxygen Doxyfile
rm -rf ../szaru-doc/cpp
cp -rp doc/html ../szaru-doc/cpp