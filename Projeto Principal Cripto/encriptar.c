#include <stdio.h>
#include <string.h>

// FunÃÂÃÂÃÂÃÂ§ÃÂÃÂÃÂÃÂ£o para encriptar usando XOR
void encriptar(const unsigned char *mensagem, unsigned char *cifrado, const unsigned char *chave, int tamanho) 
{
    for (int i = 0; i < tamanho; i++) 
    {
        cifrado[i] = mensagem[i] ^ chave[i];
    }
}

int main()
{
    char mensagem[256];  // Armazena a mensagem digitada pelo usuÃÂÃÂÃÂÃÂ¡rio (mÃÂÃÂÃÂÃÂ¡x. 255 caracteres + '\0')
    unsigned char chave[256]; // Armazena a chave (valores 0-255)
    unsigned char mensagemCifrada[256]; // Armazena a mensagem criptografada
    int tamanho;  // Tamanho da mensagem
    int chave_temp;  // Armazena temporariamente cada valor da chave (antes de converter para unsigned char)

    // Obter mensagem do usuÃÂÃÂÃÂÃÂ¡rio
    printf("Digite a mensagem a ser encriptada (max 255 caracteres): ");
    fgets(mensagem, sizeof(mensagem), stdin);
    
    // Remover quebra de linha
    mensagem[strcspn(mensagem, "\n")] = '\0'; // Remove a quebra de linha (\n) do final
    tamanho = strlen(mensagem); // Calcula o tamanho da mensagem

    // Obter chave do usuÃÂÃÂÃÂÃÂ¡rio (em inteiros)
    printf("Digite a chave em valores inteiros (0-255, separados por espaÃÂÃÂÃÂÃÂ§o):\n");
    for (int i = 0; i < tamanho; i++) 
    {
        scanf("%d", &chave_temp);  // LÃÂÃÂÃÂÃÂª um inteiro
        chave[i] = (unsigned char)(chave_temp % 256); // Garantir que estÃÂÃÂÃÂÃÂ¡ no intervalo 0-255
    }

    // Encriptando mensagem
    encriptar((unsigned char *)mensagem, mensagemCifrada, chave, tamanho);

    // Exibindo resultado
    printf("\nMensagem encriptada (valores inteiros): ");
    for (int i = 0; i < tamanho; i++) 
    {
        printf("%d ", mensagemCifrada[i]); // Mostra cada byte como inteiro (0-255)
    }
    printf("\n");

    // Salvando a mensagem criptografada em um arquivo TXT
    FILE *arquivo = fopen("mensagem_encriptada.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    
    fprintf(arquivo, "Mensagem encriptada (valores inteiros): ");
    for (int i = 0; i < tamanho; i++)
    {
        fprintf(arquivo, "%d ", mensagemCifrada[i]);
    }
    fprintf(arquivo, "\n");
    
    fclose(arquivo);
    printf("Mensagem encriptada salva no arquivo 'mensagem_encriptada.txt'\n");

    return 0;
}




/*#include <stdio.h>
#include <string.h>

// Funcao para encriptar usando XOR
void encriptar(const unsigned char *mensagem, unsigned char *cifrado, const unsigned char *chave, int tamanho) 
{
    for (int i = 0; i < tamanho; i++) 
    {
        cifrado[i] = mensagem[i] ^ chave[i];
    }
}

int main()
 {
    char mensagem[256];
    unsigned char chave[256];
    unsigned char mensagemCifrada[256];
    int tamanho;

    // Obter mensagem do usuario
    printf("Digite a mensagem a ser encriptada (max 255 caracteres): ");
    fgets(mensagem, sizeof(mensagem), stdin);
    
    // Remover quebra de linha
    mensagem[strcspn(mensagem, "\n")] = '\0';
    tamanho = strlen(mensagem);

    // Obter chave do usuario (em hex)
    printf("Digite a chave em hexadecimal (ex: 1a 2b 3c...):\n");
    for (int i = 0; i < tamanho; i++) 
    {
        scanf("%hhx", &chave[i]);
    }

    // Encriptando mensagem
    encriptar((unsigned char *)mensagem, mensagemCifrada, chave, tamanho);

    // Exibindo resultado
    printf("\nMensagem encriptada (hex): ");
    for (int i = 0; i < tamanho; i++) 
    {
        printf("%02x ", mensagemCifrada[i]);
    }
    printf("\n");

    // Salvando a mensagem criptografada em um arquivo TXT
    FILE *arquivo = fopen("mensagem_encriptada.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    
    fprintf(arquivo, "Mensagem encriptada: ");
    for (int i = 0; i < tamanho; i++)
    {
        fprintf(arquivo, "%02x ", mensagemCifrada[i]);
    }
    fprintf(arquivo, "\n");
    
    fclose(arquivo);
    printf("Mensagem encriptada salva no arquivo 'mensagem_encriptada.txt'\n");

    return 0;
}*/
    