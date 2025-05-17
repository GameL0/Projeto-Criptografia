#include <stdio.h>

// Esta função cria (ou sobrescreve) um arquivo chamado "chave.txt"
// e escreve dentro dele os valores de n e e (as “chaves” públicas).
void criar_txt(long long int n, long long int e) {
    FILE *arquivo;
    arquivo = fopen("chave.txt", "w");     // Abre o arquivo em modo “escrita”
    fprintf(arquivo, "%lld %lld", n, e);   // Grava os dois números
    fclose(arquivo);                       // Fecha o arquivo (salva)
}

// Verifica se um número 'a' é primo (só divisível por 1 e por ele mesmo).
int eh_primo(long long int a) {
    if (a < 2)
        return 0;  // Números menores que 2 não são primos

    // Tenta dividir 'a' por todos os números de 2 até sqrt(a)
    for (long long int divisor = 2; divisor * divisor <= a; divisor++) {
        if (a % divisor == 0)
            return 0;  // achou um divisor, não é primo
    }

    return 1;  // passou por todos os testes, é primo
}

// (Opcional) Imprime todos os divisores de 'aux' exceto 1 e ele mesmo.
void divisores(long long int aux) {
    for (long long int i = 2; i * i <= aux; i++) {
        if (aux % i == 0) {
            printf("%lld ", i);
            if (i != aux / i)
                printf("%lld ", aux / i);
        }
    }
}

// Verifica se e e z são “co-primos” (não possuem divisores em comum além de 1).
// Retorna 1 se são válidos, 0 caso contrário.
int verificar(long long int aux, long long int z) {
    // Tenta encontrar um divisor comum
    for (long long int i = 2; i * i <= z; i++) {
        if (aux % i == 0 || z % i == 0) {
            long long int num = aux / i;
            long long int numz = z / i;
            // Se os quocientes não forem iguais, não são co-primos
            return (num != numz);
        }
    }
    return 1;  // não encontrou divisores comuns, são co-primos
}

// Algoritmo de Euclides estendido: encontra o máximo divisor comum (mdc)
// de a e b, e também coeficientes x e y tais que a*x + b*y = mdc(a,b).
long long int euclides_estendido(long long int a, long long int b, long long int *x, long long int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long int x1, y1;
    long long int mdc = euclides_estendido(b % a, a, &x1, &y1);
    // Atualiza x e y com base nos resultados recursivos
    *x = y1 - (b / a) * x1;
    *y = x1;
    return mdc;
}

// A partir de e e z, calcula o inverso modular d (chave privada)
// tal que (e * d) mod z = 1. Se não existir, retorna -1.
long long int funcao(long long int e, long long int z) {
    long long int x, y;
    long long int mdc = euclides_estendido(e, z, &x, &y);
    if (mdc != 1)
        return -1;  // não são co-primos, não há inverso
    // Ajusta para garantir um valor positivo entre 0 e z-1
    return (x % z + z) % z;
}

int main() {
    long long int p, q, z, n, e, d;

    // Lê dois números do usuário: p e q
    scanf("%lld %lld", &p, &q);

    // Verifica se p e q são primos
    if (!eh_primo(p) || !eh_primo(q)) {
        printf("Os números escolhidos são inválidos. Por favor, digite dois números PRIMOS novamente: ");
        return 0;  // encerra o programa
    }

    n = p * q;                  // n será parte da chave pública
    z = (p - 1) * (q - 1);      // phi(n), usado no cálculo da chave privada

    // Lê o expoente público e (deve ser co-primo de z)
    scanf("%lld", &e);
    if (e <= 1 || e >= z || !verificar(e, z)) {
        printf("O número escolhido é inválido, por favor, escolha outro.\n");
        return 0;
    }

    printf("O número %lld é válido\n", e);

    // Calcula d, a chave privada
    d = funcao(e, z);
    if (d != -1) {
        criar_txt(n, e);  // grava n e e em "chave.txt"
    } else {
        printf("Não existe d satisfazendo a condição.\n");
        return 0;
    }

    return 0;
}
