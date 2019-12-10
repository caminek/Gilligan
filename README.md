# Gilligan

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Travis (.org)](https://travis-ci.org/caminek/Gilligan.svg?branch=master)
![AppVeyor](https://ci.appveyor.com/api/projects/status/github/caminek/Gilligan?branch=master&svg=true)

Tested on:
- Ubuntu 16.04 LTS (Xenial Xerus) with gcc 5.4.0 and Qt 5.6 and higher
- Ubuntu 18.04 LTS (Bionic Beaver) with gcc 7.4.0 and Qt 5.11 and higher
- OS X with Apple LLVM version 9.1.0 (clang-902.0.39.2) and Qt 5.13
- Windows 7, 8, and 10 with MinGW 4.8.2 and higher, and Qt 5.3 and higher

## About

Gilligan is a Qt/C++ app that serves as both a password generator and a password validator for the  [The Adventures of Gilligan's Island](https://en.wikipedia.org/wiki/The_Adventures_of_Gilligan's_Island).

## Requirements

### Ubuntu and OS X

Qt 5.6 or greater can be installed via [Brew](http://osxdaily.com/2018/03/07/how-install-homebrew-mac-os/) on OS X, and on Ubuntu by adding the appropriate [PPA](https://launchpad.net/~beineri). 

### Windows
Qt 5.3 or greater can be downloaded from [qt.io](https://doc.qt.io/qt-5/windows.html)

MinGW 4.8.2 or creater (32-bit or 64-bit) can be downloaded from [SourceForge](https://sourceforge.net/projects/mingw-w64/)

#### Optional 

cmake 3.1

## Build

### Building on Ubuntu and OS X

#### Using qmake

```bash
cd /path/to/Gilligan

mkdir build
cd build

qmake ../Gilligan.pro CONFIG+=release
make
```

#### Using cmake

```bash
cd /path/to/Gilligan

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Building on Windows

#### Using qmake

```
cd c:\path\to\Gilligan

mkdir build
cd build

qmake ..\Gilligan.pro CONFIG+=release CONFIG+=c++11 DESTDIR=%cd%
mingw32-make
mingw32-make install
```

## TODO
- Look into how to get version of Qt < 5.13 from Brew
- Look into getting cmake, windows, and appveyor to play nicely
