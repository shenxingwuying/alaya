#!/bin/bash

find . -name "*.[c|h|S|s]" -o -name "*.cpp" -o -name "*.cc"> cscope.files
cscope -k -b -q
ctags -R $path
