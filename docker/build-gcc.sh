#!/bin/sh
set -e

export PREFIX="/usr/local/cross"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

mkdir ~/src
cd ~/src

curl https://ftp.gnu.org/gnu/gcc/gcc-12.1.0/gcc-12.1.0.tar.xz --output gcc-12.1.0.tar.xz
tar -xf gcc-12.1.0.tar.xz
rm gcc-12.1.0.tar.xz

cd ~/src
mkdir build-gcc
cd build-gcc
../gcc-12.1.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make -j$((`nproc`+1)) all-gcc
make -j$((`nproc`+1)) all-target-libgcc
make install-gcc
make install-target-libgcc

cd ~/
rm -r ~/src