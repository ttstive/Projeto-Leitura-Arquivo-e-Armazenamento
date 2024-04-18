#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_CHAR 50

struct DadosNotas {
    char nome[MAX_CHAR];
    char num[MAX_CHAR];
    char curso[MAX_CHAR];
    float nota1;
    float nota2;
    char situacao[MAX_CHAR]; // Adicionado campo para armazenar a situação (APROVADO ou REPROVADO)
};

void lendoArquivo(char* arquivo_notas, struct DadosNotas *alunos, int *num_alunos) {
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("/home/estevaolins/Documentos/Trabalho em C/DadosNotas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    // Ignora a primeira linha
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL && *num_alunos < MAX_ALUNOS) {
        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f", alunos[*num_alunos].nome, 
               alunos[*num_alunos].num, alunos[*num_alunos].curso, 
               &alunos[*num_alunos].nota1, &alunos[*num_alunos].nota2);
        (*num_alunos)++;
    }
    fclose(arquivo);
}

void DefineSituacao(struct DadosNotas *alunos, int num_alunos) {
    float media_passar  = 7;
    for (int i = 0; i < num_alunos; i++) {
        float media = (alunos[i].nota1 + alunos[i].nota2) / 2;
        if (media >= media_passar) {
            strcpy(alunos[i].situacao, "APROVADO");
        } else {
            strcpy(alunos[i].situacao, "REPROVADO");
        }
    }
}

void GuardarSituacao(struct DadosNotas *alunos, int num_alunos) {
    FILE *arquivo;
    arquivo = fopen("/home/estevaolins/Documentos/Trabalho em C/SituacaoAluno.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    for (int i = 0; i < num_alunos; i++) {
        fprintf(arquivo, "%s,%.2f,%.2f,%s\n", alunos[i].nome, (alunos[i].nota1 + alunos[i].nota2) / 2, alunos[i].situacao);
    }
    fclose(arquivo);
}

int main() {
    struct DadosNotas alunos[MAX_ALUNOS];
    int num_alunos = 0;
    
    lendoArquivo("DadosNotas.csv", alunos, &num_alunos);
    DefineSituacao(alunos, num_alunos);
    GuardarSituacao(alunos, num_alunos);
    
    return 0;
}
