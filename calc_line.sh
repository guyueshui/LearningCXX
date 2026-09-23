#!/bin/sh

find  -type f -regextype posix-extended -regex  ".*\.(c|cpp|h|hpp)" -exec wc -l {} + |\
	tail -1 |\
       	awk '{print "src code line: " $1}'
