#!/bin/bash

cd $1
for file in *.xlsx; do
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    ssconvert --export-type=Gnumeric_html:latex $filename.xlsx $filename.tex
    # Also need to change longtable to tabular
    sed -i 's/\\begin{longtable}/\\begin{tabular}/g' $filename.tex
    sed -i 's/\\end{longtable}/\\end{tabular}/g' $filename.tex
done
