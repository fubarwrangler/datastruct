#include <stdio.h>

#include "set.h"

int main(int argc, char *argv[])
{
	set *s = set_init(10);
	set *t = set_init(3);
	set *r;
	set_iter i;
	char *p;

	set_add(s, "calvin");
	set_add(s, "hobbes");
	set_add(s, "alfred");
	set_add(s, "hobbes");

	set_add(t, "batman");
	set_add(t, "robin");
	set_add(t, "calvin");
	set_add(t, "kevin bacon");
	set_add(t, "alfred");



	/*printf("len: %d\n", set_size(s));

	printf("calvin: %d\nhobz: %d\n", set_ismember(s, "calvin"), set_ismember(s, "hobz"));*/

	r = set_and(s, t);

	set_iter_init(r, &i);
	while((p = set_iterate(r, &i)) != NULL)	{
		printf("member: %s\n", p);
	}


	set_destroy(s);
	set_destroy(t);


	return 0;
}
