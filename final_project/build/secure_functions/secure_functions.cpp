#include "secure_functions_t.h"
#include "sgx_trts.h"
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <limits>


void enclaveStrcpy(char* dest, const char* src)
{
	int len;
	if (strlen(src) > sizeof(dest) - 1)
	{
		len = sizeof(dest) - 1;
	}
	else
	{
		len = strlen(src);
	}
	strncpy(dest, src, len + 1);
}

void enclaveRecursive(int* outRes, size_t size)
{
	int* retval = new int;
	//Tail Call
	int result = int_ocall_wrapper((int*)retval);
	if (result != SGX_SUCCESS)
	{
		abort();
	}
	//copying result to pointer that could be accessed  from outside the enclave 
	memcpy(outRes, (int*)retval, size);
}