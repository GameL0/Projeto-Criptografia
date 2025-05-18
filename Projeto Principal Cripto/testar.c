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
    while(exp>0)
    {
        result *= base % mod;
        result %= mod;
        exp--;
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

int mdc_extendido(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    
    *x = y1;
    *y = x1 - (a / b) * y1;

    return mdc_extendido(b, a % b, &x1, &y1);
}


long long int mod_inverso(long long a, long long m)
{
    long long x,y;
    mdc_extendido(a, m, &x, &y);

    return (x % m + m) % m; // garante que o resultado seja positivo
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

    
    if (tipo == 'i') // Chave Publica
    {
        arquivo = fopen("publica.txt", "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/publica.txt", diretorio);
        int l = *(int*)a;
        int s = *(int*)b;
        fprintf(arquivo, "%d %d", l, s);
    }
    else if (tipo == 'c') // Chave Privada
    {
        arquivo = fopen("encriptado.txt", "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/encriptado.txt", diretorio);
        int* m = (int*)a;
        for(int i = 0; i<tamanho; i++) fprintf(arquivo, "%d ", *(m+i));
    }
    else // Mensagem Descriptografada
    {
        arquivo = fopen("descriptado.txt", "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/descriptado.txt", diretorio);
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
            printf("Digite um par de numeros primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
        
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
                printf("Entrada invalida (algum numero nao eh primo). Por favor, digite dois numeros PRIMOS novamente:\n");
                scanf("%lld %lld", &p, &q);
            }

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
            printf("Digite 'n' da chave publica:\n");
            scanf("%d",&n);
            printf("Digite 'e' da chave publica:\n");
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
            printf("Dê o valor de 'p' e 'q':\n");
            scanf("%lld%lld",&p,&q);
            printf("Dê a chave publica 'e':\n");
            scanf("%d",&e);
            printf("\n");

            long long z = (p - 1) * (q - 1); // para fazer a chave privada d;

            FILE *arquivo = fopen("dados.txt", "r");
            if (arquivo == NULL)
            {
                perror("Erro ao abrir o arquivo\n");
                return 1;
            }

            // d é o inverso do valor e
            long long d = mod_inverso (e, z);
            
            int valor;
            while (fscanf(arquivo, "%d", &valor) == 1)
            {
                valor = modpow(valor, d, n);
                fprintf(arquivo, "%d", valor);
                // converter numeros pra letras
            }

            fclose(arquivo);
            return 0;
        }
    }
    return 0;
}