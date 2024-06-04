/* um ponto é representado por duas coordenadas */
struct ponto {
	float x;
	float y;
};

/* le um ponto do teclado e retorna */
struct ponto le_ponto ();

/* calcula a distancia entre os pontos a e b */
float distancia_ponto (struct ponto a, struct ponto b);

#define NCOORD 3

/* um triangulo eh representado por 3 pontos */
struct triangulo {
	struct ponto coord[NCOORD];
};

/* le os 3 pontos que formam um triangulo e retorna */
struct triangulo le_triangulo();

/* calcula o perimetro do triang e retona */
float perimetro_triangulo (struct triangulo triang);