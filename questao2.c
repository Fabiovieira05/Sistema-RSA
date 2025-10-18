#include <stdio.h>
#include <stdlib.h>

//mdc para o mmc
long long mdc(long long a, long long b) {
    long long resto;
    while (b != 0) {
        resto = a % b;
        printf("    - MDC Passo: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    printf("    - MDC Resultado: %lld\n", a);
    return a;
}

//faz o mmc usando o mdc
long long mmc(long long a, long long b) {
    long long divisor = mdc(a, b);
    long long resultado = a * (b / divisor);
    printf("\nCalculando MMC(%lld, %lld): (%lld * %lld) / %lld = %lld\n", a, b, a, b, divisor, resultado);
    return resultado;
}

int main() {
    printf("Integrantes do Grupo:\n");
    printf("Artur Fernandes Galdino - 241010923\n");
    printf("Fábio Alessandro Santos Vieira - 241011804\n\n");

    printf("'CHAVES PERIÓDICAS'\n\n O programa encontra o primeiro ano de uso simultâneo de todas as chaves.\n Cada chave possui um ciclo de ativação em anos, todas começando no ano 0.\n O programa procurará por essa sincronização até o ano 50.\n\n");
    

    //le a quantidade de chaves
    int n;
    printf("Digite a quantidade de chaves(1 a 10): ");
    scanf("%d", &n);

    //valida a quantidade
    while (n < 1 || n > 10) {
        printf("Quantidade invalida. Digite novamente(entre 1 e 10): ");
        scanf("%d", &n);
    }

    //le os ciclos das chaves
    long long ciclos[10];
    for (int i = 0; i < n; i++) {
        printf("Digite o ciclo da chave %d(entre 2 e 20): ", i + 1);
        scanf("%lld", &ciclos[i]);

        //valida os ciclos
        while (ciclos[i] < 2 || ciclos[i] > 20)
        {
            printf("Ciclo invalido. Digite novamente o ciclo %d(entre 2 e 20): ", i + 1);
            scanf("%lld", &ciclos[i]);
        }
        
    }

    //primeiro ciclo
    long long resultado = ciclos[0];  

    //calcula o mmc de todos os ciclos
    printf("\nCalculando o MMC de todos os ciclos:\n");
    for (int i = 1; i < n; i++) {
        resultado = mmc(resultado, ciclos[i]);
        if(resultado > 50){
            break;
        }
    }


     // Resultado final
    printf("\n RESULTADO FINAL \n");
    
    if (resultado > 0 && resultado <= 50) {
        printf("O primeiro ano futuro em que todas as chaves podem ser usadas simultaneamente e: %lld\n", resultado);
    } else {
        printf("Nao e possivel sincronizar todas as chaves dentro do limite de 50 anos.\n");
    }

    return 0;
}