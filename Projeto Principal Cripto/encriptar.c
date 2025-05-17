#include <stdio.h>
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

    return 0;
}
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
}