#include <stdio.h>
#include <math.h>



int verificar_primo(long long a){
    if (a < 2) return 0; // menores que 2 não são primos

    if (a == 2 || a == 3) return 1; // 2 e 3 são primos

    if (a % 2 == 0 || a % 3 == 0) return 0; // elimina pares e múltiplos de 3

    long long limite = (long long) sqrt((double)a);

    for (long long i = 5; i <= limite; i += 6) {
        if (a % i == 0 || a % (i + 2) == 0)
        return 0;
    }
    return 1;
}



int main()
{
    long long int p, q, n, z;

    // Scanf de dois numeros do usuario: p e q
    scanf("%lld %lld", &p, &q);

    if (!verificar_primo(p) || !verificar_primo(q)) {
        printf("Os números inseridos são inválidos. Por favor, digite dois números PRIMOS novamente\n");
        return 0; 
    }

    n = p * q; // chave pública é o produto de p e q
    z = (p - 1) * (q - 1); // phi(n) = (p-1)(q-1)

    scanf("%lld", &e) // le a chave publica

    if (e <= 1 || e >= z){
        printf("A chave inserida é inválida. Por favor, digite uma chave válida\n");
        return 0;
    }

    return 0;
}
