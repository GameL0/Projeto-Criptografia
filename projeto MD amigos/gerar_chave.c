#include <stdio.h>

// esta funcao cria ou sobrescreve um arquivo chamado "chave.txt"
// e escreve dentro dele os valores de n e e (as chaves publicas).
void criar_txt(long long int n, long long int e) {
    FILE *arquivo;
    arquivo = fopen("chave.txt", "w");     // abre o arquivo em modo escrita
    fprintf(arquivo, "%lld %lld", n, e);   // grava os dois numeros
    fclose(arquivo);                       // fecha o arquivo
}

// verifica se um numero a e primo
int eh_primo(long long int a) {
    if (a < 2)
        return 0;  // numeros menores que 2 nao sao primos

    for (long long int divisor = 2; divisor * divisor <= a; divisor++) {
        if (a % divisor == 0)
            return 0;  // achou divisor, nao e primo
    }
    return 1;  // primo
}

// opcional: imprime todos os divisores de aux exceto 1 e ele mesmo
void divisores(long long int aux) {
    for (long long int i = 2; i * i <= aux; i++) {
        if (aux % i == 0) {
            printf("%lld ", i);
            if (i != aux / i)
                printf("%lld ", aux / i);
        }
    }
}

// verifica se aux e z sao coprimos (sem fatores em comum alem de 1)
// retorna 1 se forem validos, 0 caso contrario
int verificar(long long int aux, long long int z) {
    for (long long int i = 2; i * i <= z; i++) {
        if (aux % i == 0 || z % i == 0) {
            long long int num = aux / i;
            long long int numz = z / i;
            return (num != numz);
        }
    }
    return 1;  // coprimos
}

// algoritmo de euclides estendido: encontra mdc(a,b) e coeficientes x,y tais que a*x + b*y = mdc(a,b)
long long int euclides_estendido(long long int a, long long int b, long long int *x, long long int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long int x1, y1;
    long long int mdc = euclides_estendido(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return mdc;
}

// calcula inverso modular d tal que (e * d) mod z = 1; se nao existir retorna -1
long long int funcao(long long int e, long long int z) {
    long long int x, y;
    long long int mdc = euclides_estendido(e, z, &x, &y);
    if (mdc != 1)
        return -1;  // sem inverso

    return (x % z + z) % z;  // ajusta para valor positivo entre 0 e z-1
}

int main() {
    long long int p, q, z, n, e, d;

    // le dois numeros do usuario: p e q
    scanf("%lld %lld", &p, &q);

    // verifica se p e q sao primos
    if (!eh_primo(p) || !eh_primo(q)) {
        printf("Os numeros escolhidos sao invalidos. Por favor, digite dois numeros primos novamente: ");
        return 0;
    }

    n = p * q;                  // n usado na chave publica
    z = (p - 1) * (q - 1);      // phi(n)

    // le o expoente publico e (deve ser coprimo de z)
    scanf("%lld", &e);
    if (e <= 1 || e >= z || !verificar(e, z)) {
        printf("O numero escolhido e invalido, por favor, escolha outro.\n");
        return 0;
    }

    printf("O numero %lld e valido\n", e);

    // calcula d, a chave privada
    d = funcao(e, z);
    if (d != -1) {
        criar_txt(n, e);  // grava n e e em "chave.txt"
    } else {
        printf("Nao existe d satisfazendo a condicao.\n");
        return 0;
    }

    return 0;
}