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

void mdc_extendido(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return;
    }

    long long x1, y1;
    mdc_extendido(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}


long long int mod_inverso(long long a, long long m)
{
    long long x,y;
    mdc_extendido(a, m, &x, &y);
    return (x % m + m) % m; // garante que o resultado seja positivo
}

int guardar_txt(char tipo, void* a, void* b, int tamanho)
{
    /* Cria o arquivo no diretório atual
    e salva os dados nele
    Se o arquivo já existir, ele será sobrescrito
    Se o arquivo não existir, ele será criado */
    
    char diretorio[PATH_MAX - 32]; // -32 para evitar overflow
    char novo_arquivo[PATH_MAX]; 

    // Obtém o diretório atual
    if (getcwd(diretorio, sizeof(diretorio)) == NULL) 
    {
        perror("Nao foi possivel rastrear o diretorio atual\n");
        return 1;
    }

    // Cria o arquivo no diretório atual
    FILE *arquivo;
    if (tipo == 'i') // Chave Publica
    {
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/publica.txt", diretorio);
        arquivo = fopen(novo_arquivo, "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        int l = *(int*)a;
        int s = *(int*)b;
        fprintf(arquivo, "n = %d\ne = %d", l, s);
    }
    else if (tipo == 'c') // Chave Privada
    {
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/encriptado.txt", diretorio);
        arquivo = fopen(novo_arquivo, "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        int* m = (int*)a;
        for(int i = 0; i<tamanho; i++) fprintf(arquivo, "%d ", *(m+i));
    }
    else // Mensagem Descriptografada
    {
        snprintf(novo_arquivo, sizeof(novo_arquivo), "%s/descriptado.txt", diretorio);
        arquivo = fopen(novo_arquivo, "w");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo\n");
            return 1;
        }
        char *mensagem = (char*)a;
        fprintf(arquivo,"%s",mensagem);
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
    printf("Escolha uma das opcoes:\n1 - Gerar chave publica\n2 - Encriptar\n3 - Desencriptar\n");
    int entrada;
    scanf("%d", &entrada);
    getchar();
    
    if (entrada < 1 || entrada > 3)
    {
        printf("\nOpcao invalida\n");
        return 0;
    }

    else
    {
        if (entrada == 1)
        {
            long long p, q, e; // p e q são primos, e é coprimo a (p-1)(q-1)
            printf("\nDigite um numero primo 'p':\n");
            scanf("%lld",&p);
            // Verifica se p e q são primos
            while(!verificar_primo(p))
            {
                printf("\nEntrada invalida. Digite novamente um numero primo 'p':\n");
                scanf("%lld",&p);
            }
        
            printf("\nDigite um numero primo 'q':\n");
            scanf("%lld",&q);
            while(!verificar_primo(q) || p==q)
            {
                if(!verificar_primo(q))
                {
                    printf("\nEntrada invalida ('q' nao eh primo). Digite novamente um numero primo 'q':\n");
                }
                if(p==q)
                {
                    printf("\nEntrada invalida ('q' e 'p' sao iguais). Digite novamente um numero primo 'q':\n");
                }
                scanf("%lld",&q);
            }

            long long n = p * q; // chave pública
            long long z = (p - 1) * (q - 1); // para criar a outra chave pública;

            printf("\nDigite um expoente coprimo a (p - 1)*(q - 1):\n");
            scanf("%lld", &e); // e é coprimo a (p-1)(q-1)

            // Verifica se e é coprimo a (p-1)(q-1)
            while (e <= 1|| mdc(e, z) != 1) 
            {
                printf("\nO numero inserido nao eh coprimo a (p - 1)*(q - 1). Por favor, digite outro numero:\n");
                scanf("%lld", &e);
            }

            
            guardar_txt('i', &n, &e, 0);
            printf("\nChave publica salva em publica.txt\n\n");
        }

        else if (entrada == 2)
        {
            printf("\nDigite a mensagem a ser encriptada:\n");
            char* mensagem = ler_mensagem();
            long long n, e;
            printf("\nDigite 'n' da chave publica:\n");
            scanf("%lld",&n);
            printf("\nDigite 'e' da chave publica:\n");
            scanf("%lld",&e);

            int tamanho = strlen(mensagem);
            int *mens = (int *)malloc(tamanho * sizeof(int));
            int limite = conversor(mensagem,mens);
            for (int i = 0; i<limite; i++)
            {
                mens[i] = modpow((int)mens[i],e,n);
            }
            guardar_txt('c',mens,NULL, limite);
            printf("\nMensagem encriptada em encriptado.txt\n\n");
            free(mens);
            free(mensagem);
        }

        else //Entrada == 3
        {
            long long p, q, e;
            printf("\nDigite o valor de 'p':\n");
            scanf("%lld",&p);
            // Verifica se p e q são primos
            while(!verificar_primo(p))
            {
                printf("\nEntrada invalida. Digite novamente o valor de 'p':\n");
                scanf("%lld",&p);
            }
        
            printf("\nDigite o valor de 'q':\n");
            scanf("%lld",&q);
            while(!verificar_primo(q) || p==q)
            {
                if(!verificar_primo(q))
                {
                    printf("\nEntrada invalida ('q' nao eh primo). Digite novamente o valor de 'q':\n");
                }
                else
                {
                    printf("\nEntrada invalida ('q' e 'p' sao iguais). Digite novamente o valor de 'q':\n");
                }
                scanf("%lld",&q);
            }

            long long n = p * q; // chave pública
            long long z = (p - 1) * (q - 1); // para fazer a chave privada d;
            printf("\nDigite a chave publica 'e':\n"); // e é coprimo a (p-1)(q-1)
            scanf("%lld",&e);
            while (e <= 1|| mdc(e, z) != 1) 
            {
                printf("\nChave inválida, digite 'e' novamente:\n");
                scanf("%lld", &e);
            }

            long long d = mod_inverso (e, z); // d é o inverso do valor e

            // Ler o arquivo
            FILE *arquivo = fopen("dados.txt", "r");

            // Verifica se o arquivo foi aberto corretamente
            if (arquivo == NULL)
            {
                perror("Erro ao abrir o arquivo\n");
                return 1;
            }

            // Conta quantos números tem no arquivo
            int count = 0;
            int temp;
            while (fscanf(arquivo, "%d", &temp) == 1) // ler os números no arquivo.txt
            {
                count++;
            }

            // Reseta o ponteiro do arquivo para o início
            rewind(arquivo);
            
            int* codigos_crip = (int*)malloc(count*(sizeof(int))); // aloca o espaço para os números
            
            // Verifica se a alocação foi bem-sucedida
            if (codigos_crip == NULL) 
            {
                perror("Erro ao alocar memoria");
                exit(1);
            }
            
            // Lê os números do arquivo e aplica a fórmula de descriptografia
            // e armazena no vetor codigos_crip
            for(int i = 0; i<count; i++)
            {
                if (fscanf(arquivo, "%d", &codigos_crip[i]) != 1)
                {
                    perror("Erro ao ler o arquivo\n");
                    free(codigos_crip);
                    fclose(arquivo);
                    return 1;
                }
                codigos_crip[i] = modpow(codigos_crip[i],d,n);
                if(codigos_crip[i] == 28) codigos_crip[i] = 32;
                else codigos_crip[i] += 63;
            }
            char* mensagem = (char*)malloc(count+1);
            for(int i = 0; i<count; i++) mensagem[i] = (char)codigos_crip[i];
            mensagem[count+1] = '\0';
            fclose(arquivo);
            guardar_txt('s',mensagem,NULL,count+1);
            free(codigos_crip);
            free(mensagem);
            printf("\nMensagem descriptografada em descriptado.txt\n\n");
        }
    }
    return 0;
}