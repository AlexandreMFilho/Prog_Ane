#include <stdio.h>
#include <math.h>
#include <string.h>

float Rotacao_esp(float*);
void Pega_valores(float*);
void Tipo_turbina(float*);
void Teste_velocidade(float*);
void Teste_diametro(float*);

/*Este programa deverá receber uma quantidade N de turbinas e solicitados os dados, no fim ele deverá informar
a melhor turbina com os devidos calculos e criterios de avaliação.
*/
float main(){
    float dados[20]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    char *nomes[20]={"altura(h)","potencia","rotacao_especifica","rpm(n)","vazao(q)","diametro(d)","gravidade(g)","rho","psi","delta","Diamemetro_especifico","Diametro_adequado","omega"};
    //EX1
    Pega_valores(dados);
    Tipo_turbina(dados);
    //Ex2 implementar um diagrama...
    //EX3
    Teste_velocidade(dados);
    //EX4 diametro especifico
    Teste_diametro(dados);
    //EX5 opcional, diagrama de rendimento.

    //printar tudo
    for(int i =0;i<13;i++){
        printf("\n%s:%f\n",nomes[i],dados[i]);
    }
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
        printf("Digite n:\n");
        scanf("%f",&n);
        printf("Digite Q:\n");
        scanf("%f",&q);
        dados[3]=n;
        dados[4]=q;
        nq = (n* sqrt(q))/pow(dados[0],(0.75));
        return nq;
    }else{
        return Rotacao_esp(dados);
    }
}

void Tipo_turbina(float* dados){
    if(dados[2] <= 20 && dados[0] <=1767 && dados[1]<=22.8){                                //pelton
        printf("A melhor turbina é Pelton.\n");
    }else if((dados[2]>20&&dados[2]<100)&&(dados[0]>=45&&dados[0]<750)&&(dados[1]<=825)){      //Francis
        printf("A melhor turbina é Francis.\n");
    }else if((dados[2]>95&&dados[2]<310)&&(dados[0]>2&&dados[0]<=60)&&(dados[1]<=75)){         //Keplan
        printf("A melhor turbina é Keplan.\n");
    }
}
void Teste_velocidade(float* dados){
    float rho,psi,delta,omega,q,d,n,g,h;
    if(dados[4] == 0){
        printf("Digite Q:\n");
        scanf("%f",&q);
        dados[4]=q;
    }
    if(dados[3]==0){
        printf("Digite n:\n");
        scanf("%f",&n);
        dados[3]=n;
    }
    if(dados[5]==0){
        printf("Digite D:\n");
        scanf("%f",&d);
        dados[5]=d;
    }
    if(dados[6]==0){
        printf("Digite G:\n");
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
}
//     0            1           2                3          4           5           6             7     8      9        10                      11                 12
//"altura(h)","potencia","rotacao_especifica","rpm(n)","vazao(q)","diametro(d)","gravidade(g)","rho","psi","delta","Diamemetro_especifico","Diametro_adequado","omega"
void Teste_diametro(float* dados){
    float dq = 0,da=0;
    dq = (dados[5]*pow(dados[6]*dados[0],0.25))/sqrt(dados[4]);
    dados[10]=dq;
    da = (4*dados[10]*sqrt(dados[4]))/(pow(3.14,2)*pow(dados[6]*dados[0],0.25));
    dados[11]=da;
}
