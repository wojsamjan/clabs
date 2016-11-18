
@echo off

if     "%1" == "clean" goto clean
if     "%1" == "comp" goto comp
if     "%1" == "help" goto usage

slk %2 %3 %4 %5 -j -n:Clc calc.ll > slk.out

:comp
jikes Calc.java  
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
        @rm -f SlkString.java
        @rm -f SlkConstants.java
        @rm -f SlkParser.java
        @rm -f ClcKeywords.txt
        @rm -f ClcExecute.txt
        @rm -f ClcString.java
        @rm -f ClcConstants.java
        @rm -f ClcParser.java
	@rm -f xxx*

goto exit

:usage
echo Usage:  mak [flags] [clean] [help]

:exit
