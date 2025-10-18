#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// funcao auxiliar para calcular potência, necessária para a fórmula de sigma(N)
long long potencia(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

int main() {

    printf("Integrantes do Grupo:\n");
    printf("Artur Fernandes Galdino - 241010923\n");
    printf("Fábio Alessandro Santos Vieira - 241011804\n\n");

    int n;
    printf("A RAZAO DE EFICIENCIA DE UM NUMERO\n\n O programa calcula a razao de eficiencia de um numero N,\n que e definida como a razao entre a soma dos divisores de N (sigma(N))\n e o numero de divisores de N (tau(N)).\n\n");
    
    printf("Digite um unico inteiro N (1 <= N <= 105): ");
    scanf("%d", &n);

    // Validação da entrada
    while(n < 1 || n > 105) {
        printf("Valor invalido. Digite novamente um unico inteiro N (1 <= N <= 105): ");
        scanf("%d", &n);
    }


    int temp_n = n;
    long long tau_n = 1;   // tau(N) armazena o número de divisores
    long long sigma_n = 1; // sigma(N) armazena a soma dos divisores

    // Passo 1: Fatoração Prima utilizando Trial Division
    printf("1. Fatoracao prima (N = p1^a1 * p2^a2 * ...):\n");
    printf("   Lista de fatores primos e seus expoentes:\n"); 

    for (int i = 2; i * i <= temp_n; i++) {
        if (temp_n % i == 0) {
            int count = 0;
            while (temp_n % i == 0) {
                temp_n /= i;
                count++;
            }
            printf("   - Fator: %d, Expoente (a): %d\n", i, count);
            // Aplicando a fórmula: tau(N) = (a1+1)*(a2+1)*...
            tau_n *= (count + 1);
            printf("     (Contribuicao para τ: %d + 1 = %d)\n", count, count + 1); 
            // Aplicando a fórmula: sigma(N) = (p1^(a1+1)-1)/(p1-1) * ...
            sigma_n *= (potencia(i, count + 1) - 1) / (i - 1);
            printf("     (Contribuicao para σ: ( %d^(%d + 1) - 1 ) / ( %d - 1 ) = %lld )\n", i, count, i, (potencia(i, count + 1) - 1) / (i - 1));
        }
    }

    // Se sobrou um número > 1, ele também é um fator primo
    if (temp_n > 1) {
        printf("   - Fator: %d, Expoente (a): 1\n", temp_n);
        tau_n *= 2;
        printf("     (Contribuicao para τ: 1 + 1 = 2)\n");
        sigma_n *= (temp_n + 1);
        printf("     (Contribuicao para σ: ( %d^(1 + 1) - 1 ) / ( %d - 1 ) = %d )\n\n", temp_n, temp_n, temp_n + 1);    
    }

    // Passo 2: Exibição dos Cálculos Intermediários de tau e sigma 
    printf("2. CALCULOS INTERMEDIARIOS:\n");
    printf("   - Calculo de τ(N) (numero de divisores): %lld\n", tau_n);//soma do tau de cada primo que compoe o N
    printf("   - Calculo de σ(N) (soma dos divisores): %lld\n\n", sigma_n);//multiplicacao do sigma de cada primo que compoe o N

    // Passo 3: Cálculo da Razão de Eficiência
    double razao = 0.0;
    if (tau_n != 0) {
        razao = (double)sigma_n / tau_n; // [cite: 107]
    }
    printf("3. RESULTADO FINAL (Razao de Eficiencia):\n"); // [cite: 125]
    printf("   Razao(%d) = σ(%d) / τ(%d) = %lld / %lld\n", n, n, n, sigma_n, tau_n);


    // Saída formatada como número real com duas casas decimais [cite: 110]
    printf("\n   >> A Razao de Eficiencia de %d e: %.2f\n\n", n, razao);


    return 0;
}