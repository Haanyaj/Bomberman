# Indie Studio

## Prerequisites

This project requires [Irrlicht 1.8.4](http://irrlicht.sourceforge.net/?page_id=10), [irrKlang 1.6](https://www.ambiera.com/irrklang/downloads.html), OpenGL, X11 and CMake.

Make sure you have open GL installed on your computer.

### Ubuntu

``` text
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

### Fedora

You should already have it.

## Irrlicht installation

Extract the files you downloaded.
Then do

``` text
cd irrlicht-1.8.4/source/Irrlicht
make NDEBUG=1
cd ../../
sudo cp include /usr/include/irr -r
sudo cp lib/Linux/libIrrlicht.a /usr/lib
```

Irrlicht should now be installed on your computer.

## irrKlang installation

Extract the files you downloaded.
Then do

``` text
cd irrKlang-64bit-1.6.0
sudo cp include /usr/include/irrKlang -r
sudo cp bin/linux-gcc-64/libIrrKlang.so /usr/lib/libIrrKlang.a
```

IrrKlang should now be installed on your computer.

## Bomberman

This project uses CMake to compile the source code on Linux and Windows.

Run the following command to generate files according to your OS.

``` text
cmake .
```

### Linux

After cmake finished generated the Makefile, simply execute

``` text
make
```

### Windows

After cmake finished generated the Visual Studio Solution, simply double click on the .sln file.
In Visual Studio, right click the project and click build.
When it is finished, double click bomberman.exe in the explorer.
