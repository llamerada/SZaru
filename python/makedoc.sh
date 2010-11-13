#! /bin/sh
rm -rf doc
cp szaru-doc.py szaru.py
epydoc -v -o doc szaru.py
rm -rf szaru.py*