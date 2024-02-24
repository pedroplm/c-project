#include <stdio.h>

typedef struct empresa {
    char nome[50];
    int cnpj;
    struct endereco{
        char rua[50];

        int numero;
        char bairro[50];
        char cidade[50];
        char estado[50];
    }endereco;
}empresa;



void create(){

    empresa *e;
    FILE *fp;
    int n, i, j;
    printf("\nQuantas empresas quer cadastrar?");
    scanf("%d", &n);

    e = (empresa*)calloc(n, sizeof(empresa));
    fp = fopen("empresas.txt", "w");

    for(i = 0; i<n; i++){
        printf("\n-----------------");
        printf("\nNome da empresa: ");
        scanf("%s", &e[i].nome);
        fflush(stdin);
        printf("\nCNPJ (apenas numeros): ");
        scanf("%d", &e[i].cnpj);
        fflush(stdin);
        printf("\n--Endereco da empresa--");
        printf("\nRua: ");
        scanf("%s", &e[i].endereco.rua);
        fflush(stdin);
        printf("\nNumero: ");
        scanf("%d", &e[i].endereco.numero);
        fflush(stdin);
        printf("\nBairro: ");
        scanf("%s", &e[i].endereco.bairro);
        fflush(stdin);
         printf("\nCidade: ");
        scanf("%s", &e[i].endereco.cidade);
        fflush(stdin);
        printf("\nEstado: ");
        scanf("%s", &e[i].endereco.estado);
        fflush(stdin);
        printf("\n-----------------");
        fwrite(&e[i],sizeof(empresa),1,fp);
    }
    fclose(fp);

}
void display(){
    empresa e1;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    while(fread(&e1, sizeof(empresa),1,fp)){
        printf("\n-----------------");
        printf("\nNOME DA EMPRESA = %s", e1.nome);
        printf("\nCNPJ DA EMPRESA = %d", e1.cnpj);
        printf("\nESTADO: %s", e1.endereco.estado);
        printf("\nCIDADE: %s", e1.endereco.cidade);
        printf("\nBAIRRO: %s", e1.endereco.bairro);
        printf("\nRUA: %s", e1.endereco.rua);
        printf("\nNUMERO: %d", e1.endereco.numero);
        printf("\n-----------------");
    }


    fclose(fp);

}



int numEmpresas(){
    empresa e1;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    fseek(fp,0,SEEK_END);
    int n = ftell(fp)/sizeof(empresa);
    printf("\n----------------------------------------------------");
    printf("\n\n Numero total de empresas cadastradas: %d", n);
    printf("\n----------------------------------------------------");
    fclose(fp);

    return n;

}

void searchEmpresas(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp;
    fp = fopen("empresas.txt", "r");

    printf("Coloque o numero do CNPJ da empresa (apenas  numeros): ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\n--------- EMPRESA: %s --------- ", e1.nome);
            printf("\nCNPJ: %d", e1.cnpj);
            printf("\nESTADO: %s", e1.endereco.estado);
            printf("\nCIDADE: %s", e1.endereco.cidade);
            printf("\nBAIRRO: %s", e1.endereco.bairro);
            printf("\nRUA: %s", e1.endereco.rua);
            printf("\nNUMERO: %d", e1.endereco.numero);
            printf("\n----------------------------------------------------");
        }

    }
    if(!found)
    {
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }


    fclose(fp);
}

void updateEmpresas(){
    empresa e1;
    int nCNPJ, found = 0;
    FILE *fp, *fp1;

    fp = fopen("empresas.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros) que deseja alterar : ");
    scanf("%d", &nCNPJ);

    while(fread(&e1, sizeof(empresa),1,fp))
    {

        if(e1.cnpj == nCNPJ){
            found = 1;
            printf("\n-----------------");
            printf("\nNovo nome da empresa: ");
            scanf("%s", &e1.nome);
            fflush(stdin);
            printf("\nNovo CNPJ (apenas numeros): ");
            scanf("%d", &e1.cnpj);
            fflush(stdin);
            printf("\n--Novo Endereco da empresa--");
            printf("\nRua: ");
            scanf("%s", &e1.endereco.rua);
            fflush(stdin);
            printf("\nNumero: ");
            scanf("%d", &e1.endereco.numero);
            fflush(stdin);
            printf("\nBairro: ");
            scanf("%s", &e1.endereco.bairro);
            fflush(stdin);
            printf("\nCidade: ");
            scanf("%s", &e1.endereco.cidade);
            fflush(stdin);
            printf("\nEstado: ");
            scanf("%s", &e1.endereco.estado);
            fflush(stdin);
            printf("\n-----------------");
        }
        fwrite(&e1, sizeof(empresa),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("empresas.txt", "w");

        while(fread(&e1,sizeof(empresa), 1, fp1)){
            fwrite(&e1,sizeof(empresa), 1,fp);
        }

        fclose(fp);
        fclose(fp1);
    }
    else{
        printf("\n----------------------------------------------------");
        printf("\nEmpresa nao encontrada");
        printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
        printf("\n----------------------------------------------------");
    }


    fclose(fp);
}

void delEmpresas(){
    empresa e1;
    int nCNPJ, opt, found = 0;
    FILE *fp, *fp1;

    fp = fopen("empresas.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Coloque o numero do CNPJ da empresa (apenas  numeros) que deseja apagar : ");
    scanf("%d", &nCNPJ);
    printf("Tem certeza que deseja apagar?:\n0. SIM\n1.Não\n\n \t:\t ");
    scanf("%d", &opt);

    if (opt == 0){

        while(fread(&e1, sizeof(empresa),1,fp))
        {

            if(e1.cnpj == nCNPJ){
                found = 1;
            } else{
                fwrite(&e1, sizeof(empresa),1,fp1);
            }
        }
        fclose(fp);
        fclose(fp1);
        if(found){
            fp1 = fopen("temp.txt", "r");
            fp = fopen("empresas.txt", "w");

            while(fread(&e1,sizeof(empresa), 1, fp1)){
                fwrite(&e1,sizeof(empresa), 1,fp);
            }

            fclose(fp);
            fclose(fp1);
        }
        else{
            printf("\n----------------------------------------------------");
            printf("\nEmpresa nao encontrada");
            printf("\nConfirme o CNPJ em:\n\t\t 2. Mostrar empresas cadastradas.");
            printf("\n----------------------------------------------------");
        }
    }



    fclose(fp);
}



void append(){
    empresa *e;
    FILE *fp;
    int n, i, j;

    printf("Quantas empresas quer cadastrar?\n\t :");
    scanf("%d", &n);

    e = (empresa*)calloc(n, sizeof(empresa));
    fp = fopen("empresas.txt", "a");

    for(i = 0; i<n; i++){
         printf("\n-----------------");
        printf("\nNome da empresa: ");
        scanf("%s", &e[i].nome);
        fflush(stdin);
        printf("\nCNPJ (apenas numeros): ");
        scanf("%d", &e[i].cnpj);
        fflush(stdin);
        printf("\n--Endereco da empresa--");
        printf("\nRua: ");
        scanf("%s", &e[i].endereco.rua);
        fflush(stdin);
        printf("\nNumero: ");
        scanf("%d", &e[i].endereco.numero);
        fflush(stdin);
        printf("\nBairro: ");
        scanf("%s", &e[i].endereco.bairro);
        fflush(stdin);
         printf("\nCidade: ");
        scanf("%s", &e[i].endereco.cidade);
        fflush(stdin);
        printf("\nEstado: ");
        scanf("%s", &e[i].endereco.estado);
        fflush(stdin);
        printf("\n-----------------");
        fwrite(&e[i],sizeof(empresa),1,fp);
    }
    fclose(fp);
}
int main(){
    int ch;

    do {
        printf("\n1. Cadastrar Empresa");
        printf("\n2. Mostrar empresas Cadastradas");
        printf("\n3. Adicionar Empresa");
        printf("\n4. Numero de empresas");
        printf("\n5. Procurar Empresa");
        printf("\n6. Alterar Empresa");
        printf("\n7. Apagar Empresa");
        printf("\n0. exit");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch){

            case 1:
                if (delEmpresas>0){
                    append();
                } else {
                    create();
                }
            break;
            case 2:
                display();
            break;
            case 3:
                append();
            break;
            case 4:
                numEmpresas();
            break;
            case 5:
                searchEmpresas();
            break;
            case 6:
                updateEmpresas();
            break;
            case 7:
                delEmpresas();
            break;
        }
    }while(ch!=0);

    return 0;
}
