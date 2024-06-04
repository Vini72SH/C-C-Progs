#include <stdio.h>

int fat_d (int n, int k){
	if (n == k){
		return n;
	}

	return n * (fat_d (n-1, k));
}

int main (){
	int n, k;

	scanf ("%d %d", &n, &k);
	printf ("%d\n", fat_d (n, k));

	return 0;
}