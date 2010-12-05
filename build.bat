@echo off

set VISE_ROOT=%CD%

set PATH=%VISE_ROOT%\lib;<put here the Python directory>;<Put here the scons directory>\Scripts;%PATH%

set PYTHONPATH=<Put here the scons directory>\Scripts;<Put here the scons directory>\Lib\site-packages\scons-0.96.92
@echo on

scons %1 %2 %3 %4 %5 %6 %7 %8 %9
