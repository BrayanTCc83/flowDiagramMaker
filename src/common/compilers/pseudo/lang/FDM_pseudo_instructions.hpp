#ifndef FDM_PSEUDO_INSTRUCTIONS
#define FDM_PSEUDO_INSTRUCTIONS

/**
 * Instructions inputs references.
 * Indicates what is the next instruction to get.
*/
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
    SIMPLE_CONDITION_END,   // Indicates when a simple condition ends
    MULTIPLE_CONDITION,     // Indicates a multiple evaluation condition, is the equivalent C, C++, switch
    EVAL_CASE,              // Indicates an evaluation of a case.
    DEFAULT_CASE,           // Indicates when a multiple condition has not coincidences.
    MULTIPLE_CONDITION_END, // Indicates when a multiple condition ends
    UNDEFINED_WHILE,        // Indicates a C, C++ while
    UNDEFINED_WHILE_END,    // Indicates a while ends
    UNDEFINED_UNTIL,        // Indicates a simil as while, but condition negated, while be true do that, until be true stop it
    UNDEFINED_UNTIL_END,    // Indicates a while ends
    DEFINED_FOR_VAR,        // Indicates a C, C++ for, controled by a variable like i
    DEFINED_FOR_VAR_END,    // Indicates a C, C++ for end
    DEFINED_FOR_ARR,        // Indicates a C, C++ for, controled by an array like x[n]
    DEFINED_FOR_ARR_END,    // Indicates a C, C++ for end
    // CONNECTORS INSTRUCTIONS
    INSIDE_DIAGRAM,         // Indicates a conector to the same diagram, pointer x -> x, like a recursive function
    OUTSIDE_DIAGRAM,        // Indicates a conector to another diagram, pointer x -> y, like a call of another function
    // POO
    DEFINE_CLASS,           // Indicates the definition of a simil as structs and unions with methods relateds (C), classes (C++, Java, Python), or prototipes (Javascript).
    DEFINE_CLASS_END,       // Indicates the end of class block
    DEFINE_STATIC,          // Indicates that a property or method is of their class exclusively.
    DEFINE_CONSTRUCTOR,     // Indicates the creation of a special method that give a instance of a class with their values initialized.
    INSTANCE,               // Indicates the instance of a class as a new object, it search in the constructors to search the equivalent.
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
    
    INSTRUCTIONS_COUNT      // The number of poo instructions
} INSTRUCTIONS;

#endif