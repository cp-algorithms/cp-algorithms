#!/bin/bash

# Check for .md links
MATCHES=$(grep -E "\[.*\]\(.*\.md(#.*)?\)" ../src/*/*.md ../src/index.md)
if [ ! -z "$MATCHES" ];
then
    echo "Links containing .md found:"
    echo "$MATCHES"
    exit 1
fi
