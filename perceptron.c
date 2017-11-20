#include <stdio.h>



void mensaje(float w1, float w2, int x1, int x2, int delta, int y, float sumatoria){
	printf(" -------------------\n");
	printf("x1: %d\n",x1);
	printf("x2: %d\n",x2);
	printf("w1: %g\n",w1);
	printf("w2: %g\n",w2);
	printf("suma: %g\n",sumatoria);
	printf("salida: %d\n",y);
	printf("salida esperada: %d\n",delta);
}

int salida(float sumatoria){
	if(sumatoria >= 0){
		return 1;
	}
	return 0;
}



float actualizacionPesos(float w, float alfa, int delta, int y, int x){
	return w + alfa*(delta - y)*x;
}


float funcionActivacion(float w1, float w2, int x1, int x2, float u){
	return (w1*x1 - u) + (w2*x2 - u); 	
}


int termino(int comprobacion[], int n){
	for (int i = 0; i < n; i++){
		if (comprobacion[i] == 0){
			return 0;
		}
	}
	return 1;
}






/*
Variables usadas

* w = peso de la entrada
* x = valor de la entrada
* alfa = coeficiente de aprendizaje
* u = umbral
* y = salida
* delta = salida esperada
*/

void main(){

	// 2^n, donde n es el numero de entrada, en este caso es 2 (x1 y x2)
	const int n = 4;

	/*
	// Vectores que representan la tabla de verdad para el operador AND 
	int x1[] = {0,0,1,1};
	int x2[] = {0,1,0,1};
	int output[] = {0,0,0,1};
	*/

	/*
	// Vectores que representan la tabla de verdad para el operador OR 
	int x1[] = {0,0,1,1};
	int x2[] = {0,1,0,1};
	int output[] = {0,1,1,1};
	*/

	// Vectores que representan la tabla de verdad para el operador XOR 
	int x1[] = {0,0,1,1};
	int x2[] = {0,1,0,1};
	int output[] = {0,1,1,0};



	/* Pesos iniciales */
	float w1 = 0.5;
	float w2 = 0.2;

	// vector de comprobacion
	int comprobacion[] = {0,0,0,0};

	/* inicializacion umbral y coeficiente de aprendizaje respectivamente */
	float u = 0.24;
	float alfa = 0.25;


	/* Entrenar perceptron */

	int condTermino = termino(comprobacion,n);
	while (!condTermino){
		// recorro la lista de entradas
		for (int i = 0; i < n; i++){
			int e1 = x1[i];
			int e2 = x2[i];
			float sumatoria = funcionActivacion(w1,w2,e1,e2,u);
			int y = salida(sumatoria);
			int delta = output[i];

			// aca compruebo si la salida que obtuves es igual a la que esperaba
			if (y == delta){
				comprobacion[i] = 1;
				mensaje(w1,w2,e1,e2,delta,y,sumatoria);
			}
			// a entrenar !!!
			else{
				while(y != delta){
					mensaje(w1,w2,e1,e2,delta,y,sumatoria);
					printf("---- entrenar x1: %d y x2: %d ----\n",e1,e2);
					w1 = actualizacionPesos(w1,alfa,delta,y,e1);
					w2 = actualizacionPesos(w2,alfa,delta,y,e2);
					sumatoria = funcionActivacion(w1,w2,e1,e2,u);
					y = salida(sumatoria);
					if (y == delta){
						comprobacion[i] = 1;
						printf("nuevo valores\n");
						mensaje(w1,w2,e1,e2,delta,y,sumatoria);
					}					
				}
			}
			
		}

		condTermino = termino(comprobacion,n);
	}


}

/*
void mensaje(float w1, float w2, int x1, int x2, int delta, int y){
	printf(" -------------------");
	printf("x1: %d\n",x1);
	printf("x2: %d\n",x2);
	printf("w1: %g\n",w1);
	printf("w2: %g\n",w2);
	printf("salida: %d\n",y);
	printf("salida esperada: %d\n",delta);
	printf(" -------------------");
}

int salida(float sumatoria){
	if(sumatoria >= 0){
		return 1;
	}
	return 0;
}



float actualizacionPesos(float w, float alfa, int delta, int y, int x){
	return w + alfa*(delta - y)*x;
}


float funcionActivacion(float w1, float w2, int x1, int x2, float u){
	return (w1*x1 - u) + (w2*x2 - u); 	
}


int termino(int comprobacion[], int n){
	for (int i = 0; i < n; i++){
		if (comprobacion[i] == 0){
			return 0;
		}
	}
	return 1;
}

*/