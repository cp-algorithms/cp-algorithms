#!/bin/sh
sed -e 's#&imgroot&#../../img#g' disjoint_set_union.md | pandoc -s --mathjax="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/MathJax.js?config=TeX-MML-AM_CHTML" -o preview.html && firefox preview.html

