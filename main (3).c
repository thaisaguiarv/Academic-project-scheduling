#include <stdio.h>

void agendar_consulta()
{
	printf("Você escolheu o agendamento de consulta");
}

int main()
{
	printf("Bem Vindo ao programa.\nPor favor selecionar o agendamento.\n");
	int escolha;
	scanf("%d", &escolha);
	switch (escolha)
	{
	case 1:
		agendar_consulta();
		break;
	case 2:
		printf("Você escolheu o agendamento de exame.");
		break;
	default:
		printf("Escolha 1 para agendar consulta ou 2 para agendar exame.");
		break;
	}

	return 0;
}