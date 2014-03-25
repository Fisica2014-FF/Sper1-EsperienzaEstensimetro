#!/bin/bash
# Trasforma un file così:
#
# a = 12
# b = 32
# in un file fdat così:
# #%a:12
# #%b:32
perl -pe "s/  \h* (\w+) \h* = \h* (\-? \d+ \. \d+)   /#%\1:\2/gx"
#                 ^^^^^           ^^^^^^^^^^^^^^^^  
#                   a       =        -12.34   diventa #%a:-12.34
exit 0
