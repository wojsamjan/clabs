expression:
    additive_expression  _action_Finish

additive_expression:
    multiplicitive_expression { add_op _action_Push multiplicitive_expression \
                                _action_Add }

add_op:
    +
    - 

multiplicitive_expression:
    exponential_expression { mul_op _action_Push exponential_expression \
                             _action_Multiply }

mul_op:
    *
    /

exponential_expression:
    primary_expression [ ^  exponential_expression  _action_Exponent ]

primary_expression:
    (   additive_expression   )
    -  primary_expression   _action_Negate 
    NUMBER _action_Push
