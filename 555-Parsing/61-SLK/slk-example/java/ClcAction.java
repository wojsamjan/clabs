
class ClcAction {

ClcAction ( ClcToken   scanner,
            ClcLog     log )
{              
    this.scanner = scanner;
    this.log = log;
    semantic_stack = new Stack();
    answer = 0;
}

private ClcToken  scanner;
private ClcLog    log;
private double    answer;
private Stack     semantic_stack;

public double     get_answer ()          { return  answer; }

public void execute ( int  number )
{
  switch ( number ) {
    case 1:  finish();  break;
    case 2:  push();  break;
    case 3:  add();  break;
    case 4:  multiply();  break;
    case 5:  exponent();  break;
    case 6:  negate();  break;
  }
}

// -----------------------------------------------------------------------
// grammar action code functions
// -----------------------------------------------------------------------

private 
void 
add ()
{
    double   op;

    answer =  semantic_stack.pop();
    op = semantic_stack.pop();
    if ( op == '+' ) {
        answer = semantic_stack.pop() + answer;
    } else {
        answer = semantic_stack.pop() - answer;
    }
    semantic_stack.push ( answer );
}

private 
void 
finish ()
{
    answer = semantic_stack.pop();
}

private 
void 
multiply ()
{
    double   op;

    answer = semantic_stack.pop();
    op = semantic_stack.pop();
    if ( op == '*' ) {
        answer = semantic_stack.pop() * answer;
    } else {
        answer = semantic_stack.pop() / answer;
    }
    semantic_stack.push ( answer );
}

private 
void 
exponent ()
{
    answer = semantic_stack.pop();
    answer = Math.pow ( semantic_stack.pop(), answer );
    semantic_stack.push ( answer );
}

private 
void 
negate ()
{
    answer = semantic_stack.pop();
    semantic_stack.push ( -answer );
}

private 
void
push ()
{
    semantic_stack.push ( scanner.get_attribute() );
}

};
