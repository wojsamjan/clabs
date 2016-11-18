
class Stack {

private double[]    stack;
private int         top;

internal
Stack () {
    stack = new double[512];
    top = 511;
    stack [ top ] = 0;
}

public double   
pop ()     
{ 
    return ( stack[top++] );
} 

public void     
push ( double value )
{ 
    stack [--top] = value;
} 

};
