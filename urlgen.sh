#!/bin/bash
#credit to chinatsu-chan on github

[[ -z $1 || ! -f $1 ]] && echo "File not found." && exit 1

cat $1 | \
    while read string; do
        echo "<a 
href='https://8chan.co/$string'>https://www.8chan.co/$string</a></br>"
    done
