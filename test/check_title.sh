#!/bin/bash

# Check for <!--?title TITEL>
MISSING=$(grep -L "<\!--?title" ../src/*/*.md)
if [ ! -z "$MISSING" ];
then
    echo "Title missing in:"
    echo "$MISSING"
    exit 1
fi
