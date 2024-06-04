#include <stdio.h>

int main (){
	int total, vbrancos, vnulos, vvalidos;
	float pvbrancos, pvnulos, pvvalidos;
	printf("Digite o total de eleitores e a quantia dos votos em branco, nulos e válidos: ");
	scanf ("%d %d %d %d", &total, &vbrancos, &vnulos, &vvalidos);
	pvbrancos = (vbrancos * 100.0) / total;
	pvnulos = (vnulos * 100.0) / total;
	pvvalidos = (vvalidos * 100.0) / total;
	printf ("O percentual de votos dessa eleição foi:\n");
	printf ("Votos válidos: %.2f%%\n", pvvalidos);
	printf ("Votos brancos: %.2f%%\n", pvbrancos);
	printf ("Votos nulos: %.2f%%\n", pvnulos);
}