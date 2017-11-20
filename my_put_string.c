#include <stdio.h>
#include "my_put_char.h"
#include "my_put_string.h"

void my_put_string(char const* str)
{
	int i = 0;

	if (str == NULL)
	{
		return;
	}

	while (str[i] != '\0')
	{
		my_put_char(str[i]);
		i++;
	}
}
