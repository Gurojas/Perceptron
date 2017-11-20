#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int salida(float sumatoria){
    if(sumatoria > 0){
        return 1;
    }
    return 0;
}



float actualizacionPesos(float w, float alfa, int delta, int y, int x){
    return w + alfa*(delta - y)*x;
}


float funcionActivacion(float w1, float w2, int x1, int x2, float u){
    return (w1*x1 + w2*x2) - u;
}

int error(int delta, int y){
    return delta - y;
}

void imprimirSalida(int output[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d\n",output[i]);
    }
}


int main(int argc, char *argv[]){


    // 2^n, donde n es el numero de entrada, en este caso es 2 (x1 y x2)
    const int n = 4;

    
    /* Pesos iniciales */

    srand(time(NULL));
    float r = (rand()%10)*0.1;

    float w1 = r;
    r = (rand()%10)*0.1;
    float w2 = r;

    // vector de comprobacion
    int comprobacion[] = {0,0,0,0};

    /* inicializacion umbral y coeficiente de aprendizaje respectivamente */
    float u = 0.6;
    float alfa = 0.1;

    int x1[] = {0,0,1,1};
    int x2[] = {0,1,0,1};
    int output[4];


    if (strcmp("AND",argv[1]) == 0){
        printf("Compuerta AND\n");
        output[0] = 0;
        output[1] = 0;
        output[2] = 0;
        output[3] = 1;
    }
    if (strcmp("OR",argv[1]) == 0){
        printf("Compuerta OR\n");
        output[0] = 0;
        output[1] = 1;
        output[2] = 1;
        output[3] = 1;
        
    }


    /* Entrenar perceptron */
    
    while (1){
            int contError = 0;
        int i;
            for (i = 0; i < n; i++){
                int e1 = x1[i];
                int e2 = x2[i];
                float sumatoria = funcionActivacion(w1,w2,e1,e2,u);
                int y = salida(sumatoria);
                int delta = output[i];
                float err = error(delta,y);
                comprobacion[i] = y;
                if (err != 0){
                    contError++;
                    w1 = actualizacionPesos(w1,alfa,delta,y,e1);
                    w2 = actualizacionPesos(w2,alfa,delta,y,e2);
                }
            }
            if (contError == 0){
                break;
            }

    }

    imprimirSalida(comprobacion,n);

    return 0;


}

