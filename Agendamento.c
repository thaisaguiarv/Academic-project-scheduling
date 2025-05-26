#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[50];
    char data[11];
    char horario[6];
    char tipoConsulta[30];
    char medico[50];
    char local[50];
} Consulta;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificarHorarioDisponivel(const char* data, const char* horario, const char* medico) {
    FILE *file = fopen("consultas.txt", "r");
    if (!file) return 1; // Arquivo ainda não existe, horário está disponível.

    char linha[256];
    Consulta temp;

    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
            temp.nome, temp.data, temp.horario, temp.tipoConsulta, temp.medico, temp.local);

        if (strcmp(temp.data, data) == 0 &&
            strcmp(temp.horario, horario) == 0 &&
            strcmp(temp.medico, medico) == 0) {
            fclose(file);
            return 0; // Conflito encontrado
        }
    }

    fclose(file);
    return 1;
}

void agendarConsulta() {
    Consulta consulta;
    int opcao;

    printf("\n=== Agendamento de Consulta ===\n");
    printf("Nome do paciente: ");
    fgets(consulta.nome, sizeof(consulta.nome), stdin);
    strtok(consulta.nome, "\n");

    printf("Tipo de consulta: ");
    fgets(consulta.tipoConsulta, sizeof(consulta.tipoConsulta), stdin);
    strtok(consulta.tipoConsulta, "\n");

    printf("Data (DD/MM/AAAA): ");
    fgets(consulta.data, sizeof(consulta.data), stdin);
    strtok(consulta.data, "\n");

    printf("Escolha um medico:\n");
    printf("1. Dr. Ana Silva - Clinica Centro - Horarios: 08:00, 10:00, 14:00\n");
    printf("2. Dr. Carlos Lima - Clinica Norte - Horarios: 09:00, 11:00, 15:00\n");
    printf("3. Dra. Beatriz Rocha - Clinica Sul - Horarios: 08:30, 13:00, 16:00\n");
    printf("Opcao (1-3): ");
    scanf("%d", &opcao);
    limparBuffer();

    switch(opcao) {
        case 1:
            strcpy(consulta.medico, "Dr. Ana Silva");
            strcpy(consulta.local, "Clinica Centro");
            break;
        case 2:
            strcpy(consulta.medico, "Dr. Carlos Lima");
            strcpy(consulta.local, "Clinica Norte");
            break;
        case 3:
            strcpy(consulta.medico, "Dra. Beatriz Rocha");
            strcpy(consulta.local, "Clinica Sul");
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }

    printf("Horario desejado (HH:MM): ");
    fgets(consulta.horario, sizeof(consulta.horario), stdin);
    strtok(consulta.horario, "\n");

    if (!verificarHorarioDisponivel(consulta.data, consulta.horario, consulta.medico)) {
        printf("Este horario ja esta ocupado para o medico escolhido.\n");
        return;
    }

    FILE *file = fopen("consultas.txt", "a");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s;%s;%s;%s;%s;%s\n",
            consulta.nome, consulta.data, consulta.horario,
            consulta.tipoConsulta, consulta.medico, consulta.local);
    fclose(file);

    printf("Consulta agendada com sucesso!\n");
}

void listarConsultas() {
    FILE *file = fopen("consultas.txt", "r");
    if (!file) {
        printf("Nenhuma consulta agendada.\n");
        return;
    }

    Consulta consulta;
    char linha[256];

    printf("\n=== Consultas Agendadas ===\n");
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               consulta.nome, consulta.data, consulta.horario,
               consulta.tipoConsulta, consulta.medico, consulta.local);

        printf("Paciente: %s\n", consulta.nome);
        printf("Data: %s  Hora: %s\n", consulta.data, consulta.horario);
        printf("Tipo: %s\n", consulta.tipoConsulta);
        printf("Medico: %s\n", consulta.medico);
        printf("Local: %s\n", consulta.local);
        printf("-----------------------------\n");
    }

    fclose(file);
}

void editarConsulta() {
    char nomeBusca[50];
    printf("\nDigite o nome do paciente para editar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    strtok(nomeBusca, "\n");

    FILE *file = fopen("consultas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Consulta consulta;
    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               consulta.nome, consulta.data, consulta.horario,
               consulta.tipoConsulta, consulta.medico, consulta.local);

        if (strcmp(consulta.nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("Nova data (DD/MM/AAAA): ");
            fgets(consulta.data, sizeof(consulta.data), stdin);
            strtok(consulta.data, "\n");

            printf("Novo horario (HH:MM): ");
            fgets(consulta.horario, sizeof(consulta.horario), stdin);
            strtok(consulta.horario, "\n");

            if (!verificarHorarioDisponivel(consulta.data, consulta.horario, consulta.medico)) {
                printf("Este horario ja esta ocupado para o medico escolhido.\n");
                fclose(file);
                fclose(temp);
                remove("temp.txt");
                return;
            }
        }

        fprintf(temp, "%s;%s;%s;%s;%s;%s\n",
                consulta.nome, consulta.data, consulta.horario,
                consulta.tipoConsulta, consulta.medico, consulta.local);
    }

    fclose(file);
    fclose(temp);
    remove("consultas.txt");
    rename("temp.txt", "consultas.txt");

    if (encontrado)
        printf("Consulta editada com sucesso!\n");
    else
        printf("Consulta nao encontrada.\n");
}

void cancelarConsulta() {
    char nomeBusca[50];
    printf("\nDigite o nome do paciente para cancelar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    strtok(nomeBusca, "\n");

    FILE *file = fopen("consultas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Consulta consulta;
    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               consulta.nome, consulta.data, consulta.horario,
               consulta.tipoConsulta, consulta.medico, consulta.local);

        if (strcmp(consulta.nome, nomeBusca) == 0) {
            encontrado = 1;
            continue; // Não grava esta linha no novo arquivo (remoção)
        }

        fprintf(temp, "%s;%s;%s;%s;%s;%s\n",
                consulta.nome, consulta.data, consulta.horario,
                consulta.tipoConsulta, consulta.medico, consulta.local);
    }

    fclose(file);
    fclose(temp);
    remove("consultas.txt");
    rename("temp.txt", "consultas.txt");

    if (encontrado)
        printf("Consulta cancelada com sucesso!\n");
    else
        printf("Consulta nao encontrada.\n");
}

int main() {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Agendar nova consulta\n");
        printf("2. Consultar agendamentos\n");
        printf("3. Editar consulta\n");
        printf("4. Cancelar consulta\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: agendarConsulta(); break;
            case 2: listarConsultas(); break;
            case 3: editarConsulta(); break;
            case 4: cancelarConsulta(); break;
            case 5: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
