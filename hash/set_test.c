#include <stdio.h>

#include "set.h"

int main(int argc, char *argv[])
{
	set *s = set_init(10);

	set_add(s, "calvin");
	set_add(s, "hobbes");
	set_add(s, "alfred");
	set_add(s, "hobbes");

	printf("len: %d\n", set_size(s));

	printf("calvin: %d\nhobz: %d\n", set_ismember(s, "calvin"), set_ismember(s, "hobz"));


	set_destroy(s);

	return 0;
}
