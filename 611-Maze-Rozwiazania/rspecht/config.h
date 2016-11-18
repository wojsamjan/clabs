#ifndef CONFIG_H_HAS_BEEN_ALREADY_INCLUDED
#define CONFIG_H_HAS_BEEN_ALREADY_INCLUDED


// zmienne globalne - parametry pracy programu

char *cfgInputWallChars, *cfgInputStartChars, *cfgInputExitChars,
     *cfgOutputWallChar, *cfgOutputStartChar, *cfgOutputExitChar,
     *cfgOutputDeadEndChar, *cfgOutputVisitedChar,
     *cfgOutputOnPathChar, *cfgOutputFloorChar;

int cfgUseExtendedFlags, cfgEliminateDeadEnds, cfgOutputDeadEndColPair,
    cfgOutputVisitedColPair, cfgOutputOnPathColPair;

int cfgDelay; 
   
char *inputfilename, *outputfilename;


// zajmuje sie parametrami wywolania programu i ustawia
// powyzsze opcje

void
SetConfig(int argc, char *argv[]);

#endif
