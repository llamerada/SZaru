#! /bin/sh
rm -rf doc
rdoc szaru-doc.rb
rm -rf ../../szaru-doc/ruby
cp -rp doc ../../szaru-doc/ruby