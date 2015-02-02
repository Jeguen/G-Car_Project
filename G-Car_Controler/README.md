# Copyright © 2015 Rodolphe Cargnello, rodolphe.cargnello@gmail.com

 ---------------------------------------------------------
| G-Car Controler https://github.com/Jeguen/G-Car_Project |
 ---------------------------------------------------------

This software can retrieve information about the G-Car, and it allows the remote control


 -----------------------------------------
| System requirement for G-Car Controler  |
 -----------------------------------------

The required packages are the packages required by SFML 2.2.
http://www.sfml-dev.org/download/sfml/2.2/index-fr.php

You also need to install Thōth and the required packages and TGUI : 
https://gitorious.org/thoth/thoth/source/8128ca1df0ba9de1d81de57a409be379a7068772:
https://github.com/texus/TGUI

 ---------------------------------
| Compilation of G-Car Controler  |
 ---------------------------------

Use CMake to build G-Car Controler:
---------------------------------------
- mkdir build
- cd build
- cmake ..
- make

Use Code::Blocks to build G-Car Controler (Windows)
----------------------------------------
- In order to compile G-Car Controler, you need to use Mingw32 4.7.2 : 
http://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.7.2/32-bit/threads-posix/sjlj/x32-4.7.2-release-posix-sjlj-rev11.7z/download
- Go to Settings/Compilers/Toolchain executables
- Edit all executables
- Now you can build and run the project

Run the executable:
------------------
./test__main
