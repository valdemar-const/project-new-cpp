#!/usr/bin/env bash
shopt -s dotglob
7z -m0=lzma2 -mx9 -ms=off u skif-theia.7z * -x!out* -x!node_modules -x!.vscode-test-web -x!dist -x!build -x!3rdparty/_src -x!3rdparty/preload -x!*7z -x!.vs
# 7z -m0=copy -mx0 -ms=off u 3rdparty.7z 3rdparty/preload
