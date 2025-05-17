#include <stdio.h>
#include <unistd.h>   // para getcwd()
#include <limits.h>   // para PATH_MAX
#include <math.h>    // para sqrt()
#include <string.h>
#include <stdlib.h> // para malloc()

int verificar_primo(long long a)
{
    if (a < 2) return 0; // menores que 2 não são primos

    if (a == 2 || a == 3) return 1; // 2 e 3 são primos

    if (a % 2 == 0 || a % 3 == 0) return 0; // elimina pares e múltiplos de 3

    double limite = sqrt((double)a);

    for (long long i = 5; i <= limite; i += 6) {
        if (a % i == 0 || a % (i + 2) == 0) return 0;
    }
    return 1;
}

// Funcao que calcula o MDC (GCD) via algoritmo de Euclides
long long int gcd(long long int a, long long int b) 
{
    if (a < 0) a = -a;
    while (b != 0)
    {
        long long int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long int euclides_estendido(long long int a, long long int b, long long int *x, long long int *y) // calcular MDC
{
    if (a == 0) 
    {
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

long long inverso_modular(long long e, long long z) 
{
    long long x, y;
    long long mdc = euclides_estendido(e, z, &x, &y);
    if (mdc != 1) return -1;
    return (x % z + z) % z;
}

long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;              // garante base < mod
    while (exp > 0) {
        // se o bit menos significativo de exp for 1, multiplica no resultado
        if (exp & 1) {
            result = ( (__int128)result * base ) % mod;
        }
        // eleva base ao quadrado para o próximo bit
        base = ( (__int128)base * base ) % mod;
        exp >>= 1;            // avança para o próximo bit
    }
    return result;
}

int salvar_em_arquivo(char tipo, void* dado1, void* dado2) // função para salvar dados em um arquivo
    // Obtém o diretório atual
    // O tamanho máximo do caminho é PATH_MAX - 32 para evitar estouro de buffer
    // e garantir espaço para o nome do arquivo
{   
    char cwd[PATH_MAX - 32];
    char path[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Erro ao obter o diretório atual");
        return 1;
    }
    FILE *arquivo = fopen("dados.txt", "w");  // <<< limpa o arquivo!
    snprintf(path, sizeof(path), "%s/dados.txt", cwd);

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Verifica o tipo e escreve conforme o caso
    if (tipo == 'i') // dois inteiros
    {
        int a = *(int*)dado1;
        int b = *(int*)dado2;
        fprintf(arquivo, "Números: %d %d\n", a, b);
    }
    else if (tipo == 's') // string
    {
        char* mensagem = (char*)dado1;
        fprintf(arquivo, "Mensagem: %s\n", mensagem);
    }
    else
    {
        fprintf(arquivo, "Tipo desconhecido.\n");
    }

    fclose(arquivo);
    return 0;
}

void ler_linha(char* buffer) {
    int capacidade = 64;
    int tamanho = 0;
    buffer = (char*)malloc(capacidade);
    if (buffer == NULL) {
        perror("Erro ao alocar memoria");
        exit(1);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[tamanho++] = (char)c;

        if (tamanho >= capacidade) {
            capacidade *= 2;
            char *novo_buffer = realloc(buffer, capacidade);
            if (novo_buffer == NULL) {
                free(buffer);
                perror("Erro ao realocar memoria");
                exit(1);
            }
            buffer = novo_buffer;
        }
    }

    buffer[tamanho] = '\0';
    return buffer;
}


int main()
{
    printf("Escolha uma das opcoes:\n1 - Gerar chave publica\n2 - Encriptar\n3 - Desencriptar\n\n");
    int entrada;
    scanf("%d", &entrada);
    
    if (entrada < 1 || entrada > 3)
    {
        printf("Opcao invalida\n");
        return 0;
    }
    else
    {
        if (entrada == 1)
        {
            long long int p, q, z, n, e, d;
            printf("Digite um par de numeros primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
            
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
            printf("Entrada invalida (alguma numero nao eh primo). Por favor, digite dois numeros PRIMOS novamente:\n");
            scanf("%lld %lld", &p, &q);
            }
        
            n = p * q; // n  usado na chave publica
            z = (p - 1) * (q - 1); // z  usado na chave privada phi(n)
            
            
            printf("\nDigite um expoente coprimo a (p - 1)*(q - 1):\n");
            // le o expoente publico e (deve ser coprimo de z)
            scanf("%lld", &e);
            printf("\n");

            while (e <= 1|| gcd(e, z) != 1) 
            {
                printf("O numero inserido nao eh coprimo, por favor digite outro numero:\n");
                scanf("%lld", &e);
            }

            // calcula d, a chave privada
            d = inverso_modular(e, z);
            if (d == -1)
            {
                printf("Nao existe inverso modular para esse e. \n");
                return 1;
            }
            salvar_em_arquivo('i', &p, &q);
            printf("Chave publica e privada geradas e salvas em dados.txt\n");
        }
        
        if (entrada == 2)
        {
            printf("Digite a mensagem de texto a encriptar:\n");
            char *mensagem;
            ler_linha(mensagem);
            // free(mensagem);  // libera a memoria alocada
            printf("\n");
        }

        if (entrada == 3)
        {
            long long int p, q, z, n, e, d;
            printf("Digite um par de numeros primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
            
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
            printf("Entrada invalida (alguma numero nao eh primo). Por favor, digite dois numeros PRIMOS novamente:\n");
            scanf("%lld %lld", &p, &q);
            }
        
            n = p * q; // n  usado na chave publica
            z = (p - 1) * (q - 1); // z  usado na chave privada phi(n)
            
            
            printf("\nDigite um expoente coprimo a (p - 1)*(q - 1):\n");
            // le o expoente publico e (deve ser coprimo de z)
            scanf("%lld", &e);
            printf("\n");

            while (e <= 1 || gcd(e, z) != 1) 
            {
                printf("O numero inserido nao eh coprimo, por favor digite outro numero:\n");
                scanf("%lld", &e);
            }

            d = inverso_modular(e, z);

            if (d == -1)
            {
                printf("Nao existe inverso modular para esse e.\n");
                return 0;
            }


            
        }
        printf("\n");
    }

    return 0;
    
}


// // inicio da descriptografia:
//             printf("Digite a mensagem criptografada, e pressione Enter:\n");

//             char *mensagem = ler_linha(); // ler memsagem criptografada
//             getchar(); // consome o '\n' deixado pelo scanf 

//             char linha[PATH_MAX];

//             if (!fgets(linha, sizeof(linha), stdin))
//             {
//                 printf("Erro ao ler mensagem cifrada.\n");
//                 return 0;
//             }

            
//             char *token = strtok(linha, "\t\n");
//             while (token) 
//             {
//                 long long c = atoll(token);
//                 //long long m = modpow(c, d, n);
//                 int m;
//                 printf("%c", (char)m);
//                 token = strtok(NULL, "\t\n");
//             }