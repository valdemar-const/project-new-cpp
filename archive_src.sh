#!/usr/bin/env bash
shopt -s dotglob
# Main sources
7z -m0=lzma2 -mx9 -ms=off u sources.7z * -x!out* -x!build* -x!3rdparty* -x!*7z -x!.vs
# Additional thirdparty
7z -m0=copy -mx0 -ms=off u 3rdparty.7z 3rdparty
