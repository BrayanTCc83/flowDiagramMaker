#ifndef FDM_PSEUDO_INSTRUCTIONS
#define FDM_PSEUDO_INSTRUCTIONS

// Instructions inputs references.
// Indicates what is the next instruction to be receibed.
typedef enum {
    // DELIMITER ALGORITHM INSTRUCTIONS
    FUNCTION,               // Define the start of a function with their identifier
    START,                  // Indicates the start of the algorithm.
    END,                    // Indicates the end of the algorithm.
    // DEFINITION INSTRUCTIONS
    DEFINE_VAR,             // Define a variable of any type
    DEFINE_ARR,             // Define an array variable of any type
    DEFINE_TYPED_VAR,       // Define a variable with type of asigned value (need to be inicialized)
    DEFINE_TYPED_ARR,       // Define an array variable with type of asigned value (need to be inicialized)
    // INPUT AND OUTPUT INSTRUCTIONS
    STANDART_INPUT,         // Indicates a console input value
    STANDART_OUTPUT,        // Indicates a console ouput print
    // FLOW CHANGE INSTRUCTIONS
    SIMPLE_CONDITION_ASSERT,// Indicates a simple condition, is the equivalent C, C++ if.
    SIMPLE_CONDITION_FAILED,// Indicates when a simple condition isn't resolved
    MULTIPLE_CONDITION,     // Indicates a multiple evaluation condition, is the equivalent C, C++, switch
    EVAL_CASE,              // Indicates an evaluation of a case.
    DEFAULT_CASE,           // Indicates when a multiple condition has not coincidences.
    UNDEFINED_LOOP_WHILE,   // Indicates a C, C++ while
    UNDEFINED_LOOP_UNTIL,   // Indicates a simil as while, but condition negated, while be true do that, until be true stop it
    DEFINED_LOOP_VAR,       // Indicates a C, C++ for, controled by a variable like i
    DEFINED_LOOP_ARR,       // Indicates a C, C++ for, controled by an array like x[n]
    // CONNECTORS INSTRUCTIONS
    INSIDE_DIAGRAM,         // Indicates a conector to the same diagram, pointer x -> x, like a recursive function
    OUTSIDE_DIAGRAM,        // Indicates a conector to another diagram, pointer x -> y, like a call of another function
} INSTRUCTION;

typedef enum {
    // ARITMETHICAL
    ASIGNATION,             // Common asignation:     A <- x
    ADITION,                // Common adition:        C <- A + B
    SUBSTRACTION,           // Common substraction:   C <- A - B
    MULTIPLICATION,         // Common multiplication: C <- A * B
    DIVISION,               // Common division:       C <- A / B
    MODULE,                 // Division residous:     C <- A % B
    // RELATIONAL
    LESS_THAN,              // Comparing if A < B
    GREATER_THAN,           // Comparing if A > B
    EQUALS_TO,              // Comparing if A == B
    DIFFERENT_TO,           // Comparing if A != B
    LESS_OR_EQUALS,         // Comparing if A <= B
    GREATER_OR_EQUALS,      // Comparing if A >= B
    // LOGICAL
    AND,                    // Relating two boolean values A && B
    OR,                     // Relating two boolean values A || B
    XOR,                    // Relating two boolean values A ^^ B
    NOT,                    // Inverint a boolean value !A
    // STRING CONCAT
    CONCAT,                 // Union of two strings  C <- A B
} OPERATOR;

typedef enum {
    DEFINE_CLASS,           // Indicates the definition of a simil as structs and unions with methods relateds (C), classes (C++, Java, Python), or prototipes (Javascript).
    DEFINE_STATIC,          // Indicates that a property or method is of their class exclusively.
    DEFINE_METHOD,          // Indicates the creation of a method, making a relation between a function and a class.
    DEFINE_CONSTRUCTOR,     // Indicates the creation of a special method that give a instance of a class with their values initialized.
} POO;

#endif