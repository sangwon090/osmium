#!/bin/sh
set -e

export PREFIX="/usr/local/cross"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

mkdir ~/src
cd ~/src

curl https://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.xz --output binutils-2.39.tar.xz
tar -xf binutils-2.39.tar.xz
rm binutils-2.39.tar.xz

cd ~/src
mkdir build-binutils
cd build-binutils
../binutils-2.39/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make -j$((`nproc`+1))
make install

cd ~/
rm -r ~/src