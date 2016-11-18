/*************************************************************************

    scanner.h

*************************************************************************/

#ifndef _SCANNER_H
#define _SCANNER_H

class Scanner
{

public:

    Scanner ( char    *input,
              SlkLog  &log );

    virtual short   get ( void );

    double      get_Attribute ( void )       { return  Last_attribute; }

protected:

    SlkLog     *log;

private:

    double  Attribute;
    double  Last_attribute;
    char    Expression [ 512 ],
           *Scan_text;
};

#endif

