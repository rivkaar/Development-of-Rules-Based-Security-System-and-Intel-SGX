#include "Secure_Functions_t.h"

#include "sgx_trts.h"
#include <string.h>
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

