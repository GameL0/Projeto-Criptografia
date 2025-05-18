#include <stdio.h>
#include <limits.h> // path_max
#include <unistd.h> // getcwd()
#include <stdlib.h> // malloc, realloc, free, exit
#include <math.h>   // sqrt()
#include <string.h> // strlen()
#include <ctype.h>  // toupper()


long long modpow(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

char* ler_mensagem()
{
    int tamanho = 0;
    int capacidade = 64;
    int c;
    char* mensagem = (char*)malloc(capacidade);
    if (mensagem == NULL) 
    {
        perror("Erro ao alocar memoria");
        exit(1);
    }
    while((c = getchar())!= '\n' && c != EOF)
    {
        c = toupper(c);
        mensagem[tamanho++] = (char)c;
        if(tamanho >= capacidade)
        {
            capacidade *= 2;
            char *novo_buffer = realloc(mensagem, capacidade);
            if (novo_buffer == NULL) 
            {
                free(mensagem);
                perror("Erro ao realocar memoria\n");
                exit(1);
            }
            mensagem = novo_buffer;
        }
    }
    mensagem[tamanho] = '\0';
    return mensagem;
}

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

void chaves(long long int* p, long long int* q, long long int* e)
{
    printf("Digite um par de numeros primos (p e q):\n");
    scanf("%lld %lld", p, q);
    
    while (!verificar_primo(*p) || !verificar_primo(*q)) 
    {
        printf("Entrada invalida (algum numero nao eh primo). Por favor, digite dois numeros PRIMOS novamente:\n");
        scanf("%lld %lld", p, q);
    }
}

long long int mdc(long long int p, long long int q)
{
    if (p < 0) p = - p;
    while (q != 0)
    {
        long long int resto = p % q;
        p = q;
        q = resto;
    }
    return p; // mdc
}

int guardar_txt(char tipo, void* a, void* b, int tamanho)
{
    char diretorio[PATH_MAX - 32];
    char novo_arquivo[PATH_MAX];
    if (getcwd(diretorio, sizeof(diretorio)) == NULL)
    {
        perror("Nao foi possivel rastrear o diretorio atual\n");
        return 1;
    }
    
    FILE *arquivo;
    arquivo = fopen("dados.txt", "w");
    snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/dados.txt", diretorio);

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo\n");
        return 1;
    }

    if (tipo == 'i')
    {
        int l = *(int*)a;
        int s = *(int*)b;
        fprintf(arquivo, "%d %d", l, s);
    }
    else if (tipo == 'c')
    {
        int* m = (int*)a;
        for(int i = 0; i<tamanho; i++) fprintf(arquivo, "%d ", *(m+i));
    }
    else
    {
        char *mensagem = (char*)a;
        fprintf(arquivo, "%s", mensagem);
    }
    
    fclose(arquivo);
    return 0;
}

int conversor(char mensagem[], int mensagem_c[])
{
    int i = 0;
    while(mensagem[i]!='\0' && mensagem[i]!='\n')
    {
        if(mensagem[i] == 32) mensagem_c[i] = 28;
        else mensagem_c[i] = mensagem[i] - 63;
        i++;
    }
    return i;
}

int main()
{
    printf("Escolha uma das opcoes:\n1 - Gerar chave publica\n2 - Encriptar\n3 - Desencriptar\n\n");
    int entrada;
    scanf("%d", &entrada);
    getchar();
    
    if (entrada < 1 || entrada > 3)
    {
        printf("Opcao invalida\n");
        return 0;
    }

    else
    {
        if (entrada == 1)
        {
            long long p, q, e;
            chaves(&p, &q, &e);

            long long n = p * q; // chave pública
            long long z = (p - 1) * (q - 1); // para criar a outra chave pública;

            printf("\nDigite um expoente coprimo a (p - 1)*(q - 1):\n");
            scanf("%lld", &e);
            printf("\n");

            while (e <= 1|| mdc(e, z) != 1) 
            {
                printf("O numero inserido nao eh coprimo. Por favor, digite outro numero:\n");
                scanf("%lld", &e);
            }

            guardar_txt('i', &n, &e, 0);
            printf("Chave publica e privada geradas e salvas em dados.txt\n");
        }

        if (entrada == 2)
        {
            printf("Digite a mensagem a ser encriptada:\n");
            char* mensagem = ler_mensagem();
            int n, e;
            printf("Digite 'n' na chave a chave pública:\n");
            scanf("%d",&n);
            printf("Digite 'e' na chave a chave pública:\n");
            {
                scanf("%d",&e);
            }
            int tamanho = strlen(mensagem);
            int *mens = (int *)malloc(tamanho * sizeof(int));
            int limite = conversor(mensagem,mens);
            for (int i = 0; i<limite; i++)
            {
                mens[i] = modpow((int)mens[i],e,n);
            }
            guardar_txt('c',mens,NULL, limite);
            free(mens);
            free(mensagem);
        }

        if (entrada == 3)
        {
            long long p, q, e;
            chaves(&p, &q, &e);

            long long n = p * q; // chave pública
            long long z = (p - 1) * (q - 1); // para criar a outra chave pública;

            printf("\nDigite um expoente coprimo a (p - 1)*(q - 1):\n");
            scanf("%lld", &e);
            printf("\n");

            while (e <= 1|| mdc(e, z) != 1) 
            {
                printf("O numero inserido nao eh coprimo. Por favor, digite outro numero:\n");
                scanf("%lld", &e);
            }

            FILE *arquivo = fopen("dados.txt", "r");
            if (arquivo == NULL)
            {
                perror("Erro ao abrir o arquivo\n");
                return 1;
            }
            
            int valor;
            while (fscanf(arquivo, "%d", &valor) == 1)
            {
                // analise individual dos numeros
            }

            fclose(arquivo);
            return 0;
        }
    }
    return 0;
}
