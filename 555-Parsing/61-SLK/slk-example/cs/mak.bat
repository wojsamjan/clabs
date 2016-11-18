
@echo off

if     "%1" == "clean" goto clean
if     "%1" == "comp" goto comp
if     "%1" == "help" goto usage

slk %1 %2 %3 %4 %5 -cs -n:Clc calc.ll > slk.out

:comp
rem for %%f in (*.cs) do ccs %%f
cscc *.cs -o calc.exe
goto exit

:clean
	@rm -f *.obj
	@rm -f *.out
	@rm -f *.lst
        @rm -f *.err
	@rm -f *.map
        @rm -f *.def
	@rm -f *.exe
        @rm -f *.class
        @rm -f SlkKeywords.txt
        @rm -f SlkExecute.txt
        @rm -f SlkString.cs
        @rm -f SlkConstants.cs
        @rm -f SlkParser.cs
        @rm -f ClcKeywords.txt
        @rm -f ClcExecute.txt
        @rm -f ClcString.cs
        @rm -f ClcConstants.cs
        @rm -f ClcParser.cs
	@rm -f xxx*

goto exit

:usage
echo Usage:  mak [flags] [clean] [help] [comp]

:exit
