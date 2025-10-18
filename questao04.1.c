#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b){
    int resto;

    // Alteração na linha abaixo
    // colocaremos b != 0 para continuar até o resto ser zero
    while(b != 0){
        resto = a % b;
        printf("Algotítmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        // alteração na linha abaixo
        // b recebe o valor do resto calculado
        b = resto;
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    // alteração na linha abaixo
    // verificar se o inverso modular existe
    if(mdcComPassos(a, m) != 1){
        printf("O inverso modular nao existe, pois MDC(%d, %d) != 1\n", A, B);
        return -1;
    }

    while (m != 0){
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if( x1 < 0) 
    // alteração na linha abaixo
    // garantir que o inverso modular seja positivo, em criptografia e aritmética
    // modular, trabalhamos com o menor representante positivo.
        x1 += m0;
    printf("\n Substituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod){
    long long res = 1;
    long long b = base % mod;
    while(exp > 0){
        // alteração na linha abaixo
        // verificar se o expoente é ímpar pois só assim multiplicamos a base ao resultado
        if (exp % 2 == 1) 
            res = (res * b) % mod;
        
        b = (b * b) % mod;
        exp >>= 1; // exp = exp / 2
    }
    return (int)res;
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    // alteração na linha abaixo
    // calcular o inverso modular de G mod Zn com exibição dos passos pois precisamos calcular o inverso para a congruência
    int inverso = inversoModular(G, Zn);
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d\n", H, inverso, Zn);
    printf("Sendo %d o inverso de %d.\n", inverso, G);

    // alteração na linha abaixo
    // calcular a congruência de a^x mod n1 com exibição dos passos para se obter o resultado final
    int resultado = powMod(a, x, n1);
    printf("Valor final da congruencia: %d\n", resultado);

    return 0;
}