[![Build Status](https://travis-ci.org/Optimaton/playmusic.svg?branch=master)](https://travis-ci.org/Optimaton/playmusic)

## playmusic
A simple command line utility written in C++ to play music from console. <br>
`keywords` : `C++17`,`SDL`,`Mixer`,`GCC 7+`

> Note: Please make sure you have a compiler that supports C++ 17

**Steps to build:**
1. Install a version of compiler of `gcc` that supports `C++17`.
2. We are working with ubuntu here. so the steps here will cater to ubuntu users with Advance Packaging Tool (apt) available to them but the steps can be generalized to any linux distro. `ex: use yum with centos`
`apt-get install libsdl2.0-dev libsdl-mixer2.0-dev`
3. just run `./configure.sh`
4.  TADA ! you should find the binary in bin folder if every thing works

**Usage:** <br>
`playmusic <path-to-file | path-to-directory>` <br>
`playmusic [ --shuffle | --repeat ]  <path-to-file | path-to-directory>` <br>
`playmusic [--help]` <br>

**example usage:** `playmusic 'sample music/'`

**Features** <br>
`1. Works only on offline files` <br>
`2. Can shuffle the music in the directory` <br>
`3. Can repeat the music` <br>

