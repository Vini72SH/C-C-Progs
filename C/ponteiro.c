#include <stdio.h>

int main (){
	int *p;
	int a = 123;
	int b = 7680;

	printf("&a vale %p\n", &a);
	printf("&b vale %p\n", &b);
	printf("&p vale %p\n", &p);

	p = &a;
	printf("p vale %p\n", p);
	printf("*p vale %d\n", *p);

	p = &b;
	printf("p vale %p\n", p);
	printf("*p vale %d\n", *p);

	*p = 500;
	printf("b vale %d\n", b);

	return 0;
}