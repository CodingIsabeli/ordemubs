#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
    int idade;
    char sexo;
    char endereco[100];
    float pressao;
    int pontos;

} Paciente;

Paciente *pacientes = NULL;
int qtd = 0, cap = 0;

// Salvar no arquivo txt
void salvarDados()
{

    FILE *arquivo = fopen("pacientes.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    for (int i = 0; i < qtd; i++)
    {

        fprintf(arquivo, "%d %s %d %d %c %s %.2f\n",
                pacientes[i].id,
                pacientes[i].nome,
                pacientes[i].idade,
                pacientes[i].pontos,
                pacientes[i].sexo,
                pacientes[i].endereco,
                pacientes[i].pressao);
    }

    fclose(arquivo);
}

// Expande capacidade de acordo com a necessidade (alocação dinamica)
void expC()
{
    cap += 10;
    pacientes = realloc(pacientes, cap * sizeof(Paciente));
}

// Pra determinar a ordem dos pacientes com desempate por idade ou id
void ordenarPacientes()
{
    for (int i = 0; i < qtd - 1; i++)
    {
        for (int j = i + 1; j < qtd; j++)
        {

            if (pacientes[i].pontos < pacientes[j].pontos)
            {

                Paciente temp = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = temp;
            }

            else if (pacientes[i].pontos == pacientes[j].pontos)
            {

                if (pacientes[i].idade > 60 && pacientes[j].idade > 60)
                {
                    if (pacientes[i].idade < pacientes[j].idade)
                    {
                        Paciente temp = pacientes[i];
                        pacientes[i] = pacientes[j];
                        pacientes[j] = temp;
                    }
                }

                else
                {
                    if (pacientes[i].id > pacientes[j].id)
                    {

                        Paciente temp = pacientes[i];
                        pacientes[i] = pacientes[j];
                        pacientes[j] = temp;
                    }
                }
            }
        }
    }
}

int interpretarResp()
{
    int resp;

    while (1)
    {
        scanf("%d", &resp);

        if (resp == 1)
        {
            return 1;
        }
        else if (resp == 0)
        {
            return 2;
        }
        else
        {
            printf("Opcao invalida! Tente novamente: ");
        }
    }
}
// Caso escolha a opção 1(cadastro)
void cadastrarPaciente()
{
    if (qtd >= cap)
    {
        expC();
    }

    Paciente p;

    if (qtd == 0)
    {
        p.id = 1;
    }
    else
    {
        p.id = pacientes[qtd - 1].id + 1;
    }

    int pontos = 0;

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);

    printf("Idade: ");
    scanf("%d", &p.idade);

    if (p.idade > 60 || p.idade < 5)
    {
        pontos += 2;
    }

    printf("Sexo (F ou M): ");
    scanf(" %c", &p.sexo);

    printf("Endereco: ");
    scanf(" %[^\n]", p.endereco);

    printf("Pressao arterial: ");
    scanf("%f", &p.pressao);

    printf("Sofre de alguma doenca cronica? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 5;
    }

    printf("Tem dor forte? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 3;
    }

    printf("Tem febre? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 2;
    }

    printf("Tem dificuldade para respirar? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 4;
    }

    printf("Tem sangramento? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 5;
    }

    printf("Esta com mal estar geral? (1-sim / 0-nao): ");
    if (interpretarResp() == 1)
    {
        pontos += 1;
    }

    p.pontos = pontos;

    pacientes[qtd++] = p;

    printf("Paciente cadastrado com sucesso.\n");

    salvarDados();
}

// Caso escolha a opção 2(lista)
void listarPacientes()
{
    if (qtd == 0)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    ordenarPacientes();

    printf("\nLista de pacientes (prioridade):\n");
    printf("ID | Nome\t | idade\t | Pontos\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < qtd; i++)
    {
        printf("%d  | %s\t | %d\t\t | %d\n",
               pacientes[i].id, pacientes[i].nome, pacientes[i].idade, pacientes[i].pontos);
    }
}

// Caso escolha a opção 3(apagar)
void removerPaciente()
{
    if (qtd == 0)
    {
        printf("Nenhum paciente para remover.\n");
        return;
    }

    int id;
    printf("Digite o ID do paciente a remover: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < qtd; i++)
    {
        if (pacientes[i].id == id)
        {
            encontrado = 1;
            for (int j = i; j < qtd - 1; j++)
            {
                pacientes[j] = pacientes[j + 1];
            }
            qtd--;
            printf("Paciente removido com sucesso.\n");
            break;
        }
    }

    if (encontrado == 0)
    {
        printf("Paciente com ID %d nao encontrado.\n", id);
    }

    salvarDados();
}

// Caso escolha a opção 4(editar pelo id)
void editarPaciente()
{
    if (qtd == 0)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    int id;

    listarPacientes();

    printf("Digite o ID do paciente a editar: ");
    scanf("%d", &id);

    for (int i = 0; i < qtd; i++)
    {
        if (pacientes[i].id == id)
        {
            printf("Editando paciente %s (ID %d):\n", pacientes[i].nome, pacientes[i].id);

            printf("Nome: ");
            scanf(" %[^\n]", pacientes[i].nome);

            printf("Idade: ");
            scanf("%d", &pacientes[i].idade);

            printf("Sexo (F ou M): ");
            scanf(" %c", &pacientes[i].sexo);

            printf("Endereco: ");
            scanf(" %[^\n]", pacientes[i].endereco);

            printf("Pressao arterial: ");
            scanf("%f", &pacientes[i].pressao);

            printf("Paciente editado com sucesso.\n");

            salvarDados();

            return;
        }
    }

    printf("Paciente com ID %d nao encontrado.\n", id);
}

// Carregar dados do arquivo
void buscarDados()
{
    FILE *f = fopen("pacientes.txt", "r");

    if (f == NULL)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    free(pacientes);
    pacientes = NULL;
    qtd = 0;
    cap = 0;

    Paciente temp;

    while (fscanf(f, "%d %s %d %d %c %s %f\n",
                  &temp.id, temp.nome, &temp.idade, &temp.pontos, &temp.sexo, temp.endereco, &temp.pressao) != EOF)
    {

        if (qtd >= cap)
        {
            expC();
        }

        pacientes[qtd++] = temp;
    }

    fclose(f);
}

void princ()
{
    int opcao;

    do
    {
        printf("\nOrdem de atendimento da UBS\n");
        printf("1. Cadastrar paciente\n");
        printf("2. Listar pacientes\n");
        printf("3. Remover paciente\n");
        printf("4. Editar paciente\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            cadastrarPaciente();
            break;
        case 2:
            listarPacientes();
            break;
        case 3:
            removerPaciente();
            break;
        case 4:
            editarPaciente();
            break;
        case 5:
            printf("Saida realizada com sucesso\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente: \n");
            scanf("%d", &opcao);
        }

    } while (opcao != 5);
}

int main()
{

    buscarDados();
    princ();
    free(pacientes);
    return 0;
    
}