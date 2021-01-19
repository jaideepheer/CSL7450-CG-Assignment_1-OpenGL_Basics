#!/bin/bash
cd "$(dirname "$0")"
# native
rm -rf ./builddir
meson setup builddir -Dprefix=$PWD/bin/native
pushd ./builddir
ninja install
popd
# win64
rm -rf ./builddir
meson setup builddir --cross-file cross-compile/x64-windows.ini -Dprefix=$PWD/bin/win
pushd ./builddir
ninja install
popd