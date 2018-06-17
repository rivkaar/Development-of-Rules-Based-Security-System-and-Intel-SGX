#include "secure_functions_t.h"
#include "sgx_trts.h"
#include <string.h>
#include <wchar.h>
#include <limits>
#include <stdlib.h>   


int tailRecursion(int num, int acc);

int callRecursion(int param)
{
	return tailRecursion(param, 1);
}

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

void enclaveRecursive(int* outRes, size_t size, int param)
{
	//Tail Call optimiztion
	int result = callRecursion(param);
	memcpy(outRes, &result, size);
}

int  tailRecursion(int a1, int acc = 1) {
	if (a1 == 1)
	{
		return acc;
	}
	return tailRecursion(a1 - 1, acc*a1);
}

void enclaveDivideByZero(int num1, int num2, int* res, size_t size)
{
	int result;
	if (num2 != 0)
	{
		result = num1 / num2;
	}
	else
	{
		result = 0;
	}

	memcpy(res, &result, size);

}
