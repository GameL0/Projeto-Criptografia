#include <stdio.h>

void criar_txt(long long int n,long long int e)
{
    FILE *arquivo;
    arquivo = fopen("chave.txt", "w");
    fprintf(arquivo, "%lld %lld", n, e);
    fclose(arquivo);
}

int eh_primo(long long int a) {
    if (a < 2)
        return 0;

    for (long long int divisor = 2; divisor * divisor <= a; divisor++) {
        if (a % divisor == 0)
            return 0;
    }

    return 1;
}

void divisores(long long int aux) {
    for (long long int i = 2; i * i <= aux; i++) {
        if (aux % i == 0) {
            printf("%lld ", i);
            if (i != aux / i)
                printf("%lld ", aux / i);
        }
    }
}

int verificar(long long int aux, long long int z) {
    for (long long int i = 2; i * i <= z; i++) {
        if (aux % i == 0 || z % i == 0) {
            long long int num = aux / i;
            long long int numz = z / i;
            return (num != numz);
        }
    }
    return 1;
}

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

long long int funcao(long long int e, long long int z) {
    long long int x, y;
    long long int mdc = euclides_estendido(e, z, &x, &y);

    if (mdc != 1)
        return -1;

    return (x % z + z) % z; // Garantindo que d seja positivo e menor que z
}

int main() {
    long long int p, q, z, n, e, d;

    scanf("%lld %lld", &p, &q);

    if (!eh_primo(p) || !eh_primo(q)) {
        printf("Os números escolhidos são inválidos. Por favor, digite dois números PRIMOS novamente: ");
        return 0;
    }

    n = p * q;
    z = (p - 1) * (q - 1);

    scanf("%lld", &e);

    if (e <= 1 || e >= z || !verificar(e, z)) {
        printf("O número escolhido é inválido, por favor, escolha outro.\n");
        return 0;
    }

    printf("O número %lld é válido\n", e);

    d = funcao(e, z);

    if (d != -1) {
        // printf("%lld\n", d);
        criar_txt(n, e);
    } else {
        printf("Não existe d satisfazendo a condição.\n");
        return 0;
    }

    return 0;
}
