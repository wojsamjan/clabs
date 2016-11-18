
@echo off

if     "%1" == "clean" goto clean
if     "%1" == "usage" goto usage

%1slk %2 %3 %4 %5 calc.ll > slk.out
icc calc.c slkparse.c slktable.c slkstring.c 
goto exit

:clean
	@rm -f *.obj
	@rm -f *.out
	@rm -f *.lst
	@rm -f *.err
	@rm -f *.map
        @rm -f *.def
	@rm -f *.exe
        @rm -f slk*.*
	@rm -f xxx*

goto exit

:usage
echo Usage:  mak [slk path] [flags] [clean]

:exit
