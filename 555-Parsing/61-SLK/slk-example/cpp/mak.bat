
@echo off

if     "%1" == "clean" goto clean
if     "%1" == "comp" goto comp
if     "%1" == "help" goto usage

slk %1 %2 %3 %4 -C++ calc.ll > Slk.out
:comp
icc calc.cpp SlkParse.cpp SlkTable.cpp SlkString.cpp scanner.cpp SlkLog.cpp SlkError.cpp Slktoken.cpp SlkAction.cpp
goto exit

:clean
	@rm -f *.obj
	@rm -f *.out
	@rm -f *.lst
	@rm -f *.err
	@rm -f *.map
        @rm -f *.def
	@rm -f *.exe
        @rm -f SlkString.*
        @rm -f SlkTable.*
        @rm -f SlkParse.*
        @rm -f SlkKeywords.*
	@rm -f xxx*

goto exit

:usage
echo Usage:  mak [flags] [clean] [help]

:exit
