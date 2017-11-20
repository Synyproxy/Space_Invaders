#include <stdio.h>
#include "my_put_char.h"

void my_put_char(char x)
{
	fwrite(&x, 1, 1, stdout);
}