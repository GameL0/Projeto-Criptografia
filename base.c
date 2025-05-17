#include <stdio.h>
#include <unistd.h>   // para getcwd()
#include <limits.h>   // para PATH_MAX
#include <math.h>    // para sqrt()
#include "encriptar.c"

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


// Funcao que calcula o MDC (GCD) via algoritmo de Euclides
long long int gcd(long long int a, long long int b) 
{
    // garante que a >= 0 e b >= 0
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0)
    {
        long long int r = a % b;
        a = b;
        b = r;
    }
}

long long int verificar_coprimo(long long int a, long long int b) 
{
    return (gcd(a, b) == 1);
}

long long int funcao(long long int e, long long int z)
{
    long long int x,y;
    long long int mdc = euclides_estendido(e, z, &x, &y);
    
    if (mc != 1) return -1; // sem inverso

    return (x % z + z) % z; // retorna o inverso positivo
}

long long int euclides_estendido(long long int a, long long int b, long long int *x, long long int *y) 
{
    if (a == 0) 
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long long int x1, y1;
    long long int mdc = euclides_estendqido(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return mdc;
}


void criar_txt()
{
    char cwd[PATH_MAX - 32]; // reserva espao extra para "/chave_publica.txt"
    char path[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        snprintf(path, sizeof(path), "%s/chave_publica.txt", cwd);


        FILE *numeros = fopen(path, "w");
    
        if (numeros == NULL)
        {
            printf("Erro ao criar o arquivo.\n");
            return 1;
        }
    
        fprintf(numeros, "%d %d\n", p, q);
    
        fclose(numeros);
    
            printf("Chave publica salva em '%s'.\n", path);
        }
        else
        {
            perror("Erro ao obter o diretorio atual!\n");
            return 1;
        }
}


int main()
{
    printf("Digite um numero de 1 a 3:\n");
    int entrada;
    scanf("%d", &entrada);
    
    if (entrada < 1 || entrada > 3)
    {
        printf("Opo invlida\n");
        return 0;
    }

    else
    {
        if (entrada == 1)
        {
            long long int p, q, z, e;
            printf("Digite um par de numeros primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
            
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
            printf("Os numeros inseridos so invalidos. Por favor, digite dois numeros PRIMOS novamente\n");
            scanf("%lld %lld", &p, &q);
            }
        
        n = p * q; // n  usado na chave publica
        z = (p - 1) * (q - 1); // z  usado na chave privada phi(n)
        
        
        printf("\nDigite um expoente coprimo a (p - 1)(q - 1):\n");
        // le o expoente publico e (deve ser coprimo de z)
        scanf("%lld\n", &e);

        while (e <= 1 || e >= z || !gcd(e, z)) 
        {
            printf("O numero inserido no  coprimo, por favor digite outro numero\n");
            scanf("%lld", &e);
        }

        // calcula d, a chave privada
        d = funcao(e, z);



        char cwd[PATH_MAX - 32]; // reserva espao extra para "/chave_publica.txt"
        char path[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != NULL) 
        {
            snprintf(path, sizeof(path), "%s/chave_publica.txt", cwd);


            FILE *numeros = fopen(path, "w");
    
            if (numeros == NULL)
            {
                printf("Erro ao criar o arquivo.\n");
                return 1;
            }
    
            fprintf(numeros, "%d %d\n", p, q);
    
            fclose(numeros);
    
            printf("Chave publica salva em '%s'.\n", path);
        }
        else
        {
            perror("Erro ao obter o diretrio atual\n");
            return 1;
        }
        }
        
        if (entrada == 2)
        {
            printf("Digite a mensagem de texto a encriptar:\n");
            // receber mensagem de texto
            
// =======
            printf("\n");

// >>>>>>> ff25afeeb7866ed2f1471723105b0e206dbc8225
        }

        if (entrada == 3)
        {
            long long int p, q, z, e;
            printf("Digite um par de numeros primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
            
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
            printf("Os numeros inseridos so invalidos. Por favor, digite dois numeros PRIMOS novamente\n");
            scanf("%lld %lld", &p, &q);
            }
        
            n = p * q; // numero usado na chave publica
            z = (p - 1) * (q - 1); // z  usado na chave privada phi(n)
            
            
            printf("\nDigite um expoente coprimo a (p - 1)(q - 1):\n");
            // le o expoente publico e (deve ser coprimo de z)
            scanf("%lld\n", &e);

            while (e <= 1 || e >= z || !gcd(e, z)) 
            {
                printf("O numero inserido no  coprimo, por favor digite outro numero\n");
                scanf("%lld", &e);
            }
        }
    }
}