// test_after.c 
#pragma check_stack(off)
//#include "stdafx.h"
#include "sgx_urts.h"
#include "secure_functions_u.h"
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ENCLAVE_FILE _T("secure_functions.signed.dll")
using namespace std;
/* OCall functions */
void ocall_print_string(const char *str)
{
	/* Proxy/Bridge will check the length and null-terminate
	* the input string to prevent buffer overflow.
	*/
	printf("%s", str);
}
sgx_status_t createEnclave(sgx_enclave_id_t *eid) {
	sgx_status_t		ret = SGX_SUCCESS;
	sgx_launch_token_t	token = { 0 };
	int					updated = 0;
	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, eid, NULL);
	return ret;
}
sgx_enclave_id_t eid;


/*
StackOverrun.c
This program shows an example of how a stack-based
buffer overrun can be used to execute arbitrary code.  Its
objective is to find an input string that executes the function bar.
*/

#pragma check_stack(off)

#include <string.h>
#include <stdio.h> 

void foo(const char* input)
{
	char buf[10];

	printf("My stack looks like:\n%p\n%p\n%p\n%p\n%p\n% p\n\n");

	//strcpy(buf, input);
	enclaveStrcpy(eid, buf, input);

	printf("%s\n", buf);

	printf("Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
}

void bar(void)
{
	printf("Augh! I've been hacked!\n");
}

int main(int argc, char* argv[])
{
	sgx_status_t res = SGX_SUCCESS;
	// Create the Enclave with above launch token.
	res = createEnclave(&eid);
	if (res != SGX_SUCCESS)
	{
		printf("App: error %#x, failed to create enclave.", res);
		return -1;
	}

	//Blatant cheating to make life easier on myself
	printf("Address of foo = %p\n", foo);
	printf("Address of bar = %p\n", bar);
	printf("strlen of input string is: %i\n",argv[1]);

	if (argc != 2)
	{
		printf("Please supply a string as an argument!\n");
		return -1;
	}
	foo(argv[1]);
	return 0;

	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
	{
		return -1;
	}
}