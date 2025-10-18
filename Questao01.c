#include <stdio.h>
#include <stdlib.h>

// Verifica se é primo
int primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Não é primo
    }   
    return 1;
}

// Função para calcular o MDC pelo algoritmo de Euclides (long long)
long long mdc(long long a, long long b) {
    long long restoDivisao;
    printf("Calculando MDC entre %lld e %lld pelo algoritmo de Euclides\n", a, b);
    while (b != 0) {
        restoDivisao = a % b;
        printf("%lld mod %lld = %lld\n", a, b, restoDivisao);
        a = b;
        b = restoDivisao;
    }

    return a;
}

// Implementação do método ρ de Pollard
long long fatoracaoPollard(long long n) {
    long long X0 = 2;
    long long Y0 = 2;
    long long d = 1;
    long long count = 1;
    
    printf("Metodo p de Pollard para N = %lld\n", n);
    printf("Semente X0 = 2\n\n");

    while (d == 1) {
        // g(x) = (x * x + 1) mod n
        X0 = (X0 * X0 + 1) % n;
        Y0 = (Y0 * Y0 + 1) % n;
        Y0 = (Y0 * Y0 + 1) % n;

        long long diferenca = llabs(X0 - Y0);

        printf("Interação número %lld\n", count++);
        printf("x = %lld \ny = %lld\n", X0, Y0);
        printf("mdc(|%lld - %lld|, %lld) = mdc(%lld, %lld)\n", X0, Y0, n, diferenca, n);
        d = mdc(diferenca, n);
    }

    printf("\nFator nao trivial encontrado: %lld\n\n", d);
    return d;
}

long long inversoModular(long long E, long long z) {
    long long t = 0, novoT = 1;
    long long r = z, novoR = E;

    while (novoR != 0) {
        long long quociente = r / novoR;
        long long temp;

        temp = novoT;
        novoT = t - quociente * novoT;
        t = temp;

        temp = novoR;
        novoR = r - quociente * novoR;
        r = temp;
    }

    if (r > 1) {
        return -1; // Inverso modular não existe
    }
    if (t < 0) {
        t += z;
    }
    return t;
}

// Função para realizar exponenciação modular 
long long potenciaModular(long long base, long long expoente, long long mod, long long totient) {
    long long res = 1;
    base %= mod;

    printf("(%lld ^ %lld) mod %lld\n", base, expoente, mod);

    if (mdc(base, mod) == 1) {
         printf("Teorema de Euler (pois mdc(%lld, %lld) = 1).\n", base, mod);
         // O expoente é reduzido pelo totiente (z).
         printf("Reducao do expoente pelo totiente z = %lld.\n", totient);
         printf("Reducao do expoente pelo totiente z = %lld.\n", expoente);
         printf("Reducao do expoente pelo totiente z = %lld.\n", totient);
         printf("Reducao do expoente pelo totiente z = %lld.\n", expoente);
         expoente = expoente % totient;
         printf("Expoente reduzido para: %lld\n", expoente);
    } else {
        printf("Reducao por Divisao Euclidiana (pois mdc(%lld, %lld) != 1).\n", base, mod);
    }

    while (expoente > 0) {
        if (expoente % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        expoente = expoente / 2;
    }
    return res;
}

int main() {
    
    int N1, N2;
    printf("Digite dois numeros inteiros entre 100 e 9999, tais que cada N deve ser produtos de primos distintos\n");
    if (scanf("%d %d", &N1, &N2) != 2) {
        printf("Entrada invalida\n");
        return 0;
    }

    // Verifica se os numeros são iguais
    if (N1 == N2) {
        printf("Os numeros não podem ser iguais\n");
        return 0;
    }
    // Verifica se os numeros são primos
    if (primo(N1) || primo(N2)) {
        printf("Os numeros não podem ser primos\n");
        return 0;
    }
    // Verifica se os numeros estão no intervalo
    if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999) {
        printf("Entrada invalida\n");
        return 0; 
    }
    // Apenas estetica
    printf("\n");

    printf("Etapa 1: Fatoração Interativa (Método ρ de Pollard)\n");

    long long p = fatoracaoPollard(N1);
    long long q = fatoracaoPollard(N2);

    printf("Fatores primos encontrados:\np = %lld\nq = %lld\n", p, q);

    printf("Etapa 2: Geração das Chaves RSA\n");

    long long n = p * q;
    long long z = (p - 1) * (q - 1);
    printf("Módulo n = p * q = %lld * %lld = %lld\n", p, q, n);
    printf("Totiente de Euler z = (p-1)*(q-1) = %lld\n", z); 

    // expoente público E
    long long E;
    for (E = 2; E < z; E++) {
        if (mdc(E, z) == 1){
            break;
        }
    }
    printf("E = %lld\n", E);
    long long d = inversoModular(E, z);

    printf("Chaves Geradas:\n");
    printf("Chave pública (n, E) = (%lld, %lld)\n", n, E);
    printf("Chave privada (n, d) = (%lld, %lld)\n", n, d);

    printf("Etapa 3 - Codificação (Criptografia) e Decodificação (Descriptografia)\n");
    char string[100];
    printf("Digite a mensagem para criptografar (letras maiusculas, sem acentos): ");
    scanf(" %[^\n]s", string);
    
    int tamanho = strlen(string); // ver o tamanho da string
    long long stringCodificada[100];
    
    printf("\nCriptografando...\n");
    int count = 0;
    for (int i = 0; i < tamanho; i++) {
        long long valor;
        if (string[i] == ' ') {
            valor = 0;
        } else {
            valor = toupper(string[i]) - 'A' + 11; // A = 11, B= 12, …, Z= 36. Espaço = 00
        }

        // Validação para garantir que M < n
        if (valor >= n) {
             printf("\nO valor da letra '%c' (%lld) e maior ou igual ao modulo n (%lld).\n", toupper(string[i]), valor, n);
             printf("A criptografia nao pode continuar. Use numeros N1 e N2 maiores.\n");
             return 1;
        }

        printf("\nCriptografando caractere '%c' (bloco M=%lld):\n", string[i], valor);

        stringCodificada[count] = potenciaModular(valor, E, n, z);
        printf("Resultado C = M^%lld mod %lld\n", E, n);
        printf("C = %lld\n", stringCodificada[count]);
        count++;
    }
    
    printf("\nMensagem Cifrada (blocos): ");
    for(int i = 0; i < count; i++) printf("%lld ", stringCodificada[i]);
    printf("\n");

    printf("\nDecodificando...\n");
    char stringDecodificada[101];
    for (int i = 0; i < count; i++) {
        printf("\nDecodificando bloco C=%lld:\n", stringCodificada[i]);
        long long m_decodificado = potenciaModular(stringCodificada[i], d, n, z);
        printf("Resultado M = C^%lld mod %lld\n", d, n);
        printf("M = %lld\n", m_decodificado);
        if (m_decodificado == 0) {
            stringDecodificada[i] = ' ';
        } else {
            stringDecodificada[i] = m_decodificado - 11 + 'A';
        }
    }
    stringDecodificada[count] = '\0';

    printf("\n3. RESULTADO FINAL:\n");
    printf("Mensagem Original: %s\n", string);
    printf("Mensagem Decifrada: %s\n", stringDecodificada);

    // Converte a mensagem original para maiúsculas
    char stringUpper[101];
    for(int i = 0; i < tamanho; ++i) stringUpper[i] = toupper(string[i]);
    stringUpper[tamanho] = '\0';

    if (strcmp(stringUpper, stringDecodificada) == 0) {
        printf("\nConfirmacao: A mensagem decifrada e identica a original.\n");
    }
    else{
        printf("\nAlerta: A mensagem decifrada nao corresponde a original.\n");
    }
    return 0;
}