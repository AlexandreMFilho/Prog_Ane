#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>

float Rotacao_esp(float*);
void Pega_valores(float*);
void Tipo_turbina(float*,char**);
void Teste_velocidade(float*,char**);
void Teste_diametro(float*,char**);

/*Este programa deverá receber uma quantidade N de turbinas e solicitados os dados, no fim ele deverá informar
a melhor turbina com os devidos calculos e criterios de avaliação.
*/
float main(){
    float dados[20]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    char *nomes[20]={"Altura: ","Potencia: ","Rotacao especifica: ","Rpm: ","Vazao: ","Diametro: ","Gravidade: ","Rho: ","Psi: ","Delta: ","Diamemetro especifico: ","Diametro adequado: ","Omega: "};
    char *resp[10];
    system("clear");
    Pega_valores(dados);
    Tipo_turbina(dados,resp);
    Teste_velocidade(dados,resp);
    Teste_diametro(dados,resp);
    system("clear");
    printf("-------------Dados-------------\n");
    for(int i=0;i<13;i++){
        printf("%s%f\n",nomes[i],dados[i]);
    }
    printf("-------------------------------\n");
    for(int i=0;i<3;i++){
        printf("%s",resp[i]);
    }
    printf("\n");
}

void Pega_valores(float *data){
    printf("Digite a altura de queda:\n");
    scanf("%f",&data[0]);
    printf("Digite a potencia:\n");
    scanf("%f",&data[1]);
    data[2] = Rotacao_esp(data);
}

float Rotacao_esp(float* dados){
    float aux;
    float nq,n,h,q;
    printf("Voce ja possui a rotacao especifica ou deseja calcula-la?\n1 - Ja possuo.\n2 - Desejo calcular.\n");
    scanf("%f",&aux);
    if(aux == 1.0){
        printf("Digite a rotacao especifica:\n");
        scanf("%f",&nq);
        return nq;
    }
    if(aux == 2.0){
        printf("Digite a rotacao em rpm:\n");
        scanf("%f",&n);
        printf("Digite a vazao:\n");
        scanf("%f",&q);
        dados[3]=n;
        dados[4]=q;
        nq = (n* sqrt(q))/pow(dados[0],(0.75));
        return nq;
    }else{
        return Rotacao_esp(dados);
    }
}

void Tipo_turbina(float* dados,char** resp){
    if(dados[2] <= 20 && dados[0] <=1767 && dados[1]<=22.8){                                //pelton
        resp[0]= "Pela tabela de comparacao a melhor turbina é Pelton.\n";
    }else if((dados[2]>20&&dados[2]<100)&&(dados[0]>=45&&dados[0]<750)&&(dados[1]<=825)){      //Francis
        resp[0]= "Pela tabela de comparacao a melhor turbina é Francis.\n";
    }else if((dados[2]>95&&dados[2]<310)&&(dados[0]>2&&dados[0]<=60)&&(dados[1]<=75)){         //Keplan
        resp[0]= "Pela tabela de comparacao a melhor turbina é Keplan.\n";
    }
}
void Teste_velocidade(float* dados,char**resp){
    float rho,psi,delta,omega,q,d,n,g,h;
    if(dados[4] == 0){
        printf("Digite a vazao:\n");
        scanf("%f",&q);
        dados[4]=q;
    }
        if(dados[3]==0){
        printf("Digite a rotacao em rpm:\n");
        scanf("%f",&n);
        dados[3]=n;
    }
    if(dados[5]==0){
        printf("Digite o diametro:\n");
        scanf("%f",&d);
        dados[5]=d;
    }
    if(dados[6]==0){
        printf("Digite a gravidade:\n");
        scanf("%f",&g);
        dados[6]=g;
    }
    rho = (pow(2,0.75)*dados[4])/(pow(3.14,2)*dados[3]*pow(dados[5],3));
    psi = (2*dados[6]*dados[0])/(pow(3.14,2)*pow(dados[3],2)*pow(dados[5],2));
    delta = pow((pow(psi,0.5)/rho),0.5);
    omega = pow((rho/pow(psi,1.5)),0.5);
    dados[7]=rho;
    dados[8]=psi;
    dados[9]=delta;
    dados[12]=omega;
    if(omega <0.15){    //Pelton
        resp[1]= "A melhor turbina é Pelton de acordo com a velocidade especifica.\n";
    }else if(omega>0.28&&omega<2.1){   //Francis
        resp[1]= "A melhor turbina é Francis de acordo com a velocidade especifica.\n";
    }else if(omega>2.3&&omega<5.1){     //Keplan
        resp[1]= "A melhor turbina é Keplan de acordo com a velocidade especifica.\n";
    }else{
        resp[1]= "De acordo com a velocidade especifica essa turbina nao ira funcionar.\n";
    }
}
void Teste_diametro(float* dados,char**resp){
    float dq = 0,da=0;
    int n;
    dq = (dados[5]*pow(dados[6]*dados[0],0.25))/sqrt(dados[4]);
    dados[10]=dq;
    da = (4*dados[10]*sqrt(dados[4]))/(pow(3.14,2)*pow(dados[6]*dados[0],0.25));
    dados[11]=da;
    n=sprintf(resp[2],"O Diametro adequado eh %f.\n",da);
}
