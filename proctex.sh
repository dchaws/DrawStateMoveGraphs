#!/bin/bash

# $1 is the file name

latex $1 && dvipdf ${1/tex/dvi} && open ${1/tex/pdf}
