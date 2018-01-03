#pragma check_stack(off)
#include "..\include\string.h"
#include "..\include\stdio.h" 
int main(int argc, char* argv[])
{
	//Blatant cheating to make life easier on myself
	printf("Address of foo = %p\n", foo);
	printf("Address of bar = %p\n", bar);
	printf("strlen of input string is: %i\n", strlen(argv[1]));

	if (argc != 2)
	{
		printf("Please supply a string as an argument!\n");
		return -1;
	}
	foo(argv[1]);
	return 0;
}

void foo(const char* input)
{
    char buf[10];

    printf("My stack looks like:\n%p\n%p\n%p\n%p\n%p\n% p\n\n");

    strcpy(buf, input);
    printf("%s\n", buf);

    printf("Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
}

void bar(void)
{
    printf("Augh! I've been hacked!\n");
}