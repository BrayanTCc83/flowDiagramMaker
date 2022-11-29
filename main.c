#include <Windows.h>
#include <stdio.h>

#define MAX_MSG_CHARS 40

typedef struct {
	char message[MAX_MSG_CHARS];
} Except;

typedef const Except Exception;

Exception Error = {
	"This is an exception error."
};

Exception ExcesiveArgs = {
	"The max number of args is 2"
};

typedef enum { false=0, true=1 } bool;

Except e;
bool isExcept = false;
bool awaitExcept = false;

#define throw(except) if(awaitExcept) { e=except; isExcept = true; };

void catch() {
	if(!awaitExcept) {
		fprintf( stderr, "The Try Statement is required before Catch" );
		exit(0x6);
	};

	if( isExcept ) { 
		printf("ERROR: %s\n", e.message ); 
		isExcept=false; 
	}; 
};

void tries() { awaitExcept = true; };

#define try tries();

void example(int a) {
	if(a > 3)
		throw(ExcesiveArgs);
}

int main(int argc, char *argv[]) {
	try {
		example(argc);
	} catch(); {
		printf("Hello error");
	}

	return 0;
}
