#include <iostream>
#include <cstring>
#include <cmath>
#define NMAX 1005
#define CMAX 10005
#define NROPERATORI 17
#define INFINIT 1000000
using namespace std;
char *p;
int vf_valori=-1,vf_operatori=-1,indice;
struct variabile
{
    char nume[CMAX];
    double valoare;
} var[NMAX],stiva_valori[NMAX];
struct operatorii
{
    char nume[10];
    int prioritate;
} operatori[20],stiva_operatori[NMAX];
bool diferitInfinit(double valoare)
{
    bool val;
    val=!((abs(valoare))>=INFINIT);
    return val;
}
void intrebari(operatorii A[NMAX],variabile B[NMAX],bool &esteCazDeNedeterminare)
{
    double aux;
    if(A[vf_operatori].nume[0]=='+')
    {
        if(diferitInfinit(B[vf_valori].valoare) && diferitInfinit(B[vf_valori-1].valoare))
        {
        aux=B[vf_valori].valoare+B[vf_valori-1].valoare;
        vf_valori--;
        if(diferitInfinit(aux))
        B[vf_valori].valoare=aux;
        else
            B[vf_valori].valoare=INFINIT;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=INFINIT;
        }
    }
    if(A[vf_operatori].nume[0]=='-')
    {
        if(diferitInfinit(B[vf_valori].valoare) && diferitInfinit(B[vf_valori-1].valoare))
        {
        aux=B[vf_valori-1].valoare-B[vf_valori].valoare;
        vf_valori--;
         if(diferitInfinit(aux))
        B[vf_valori].valoare=aux;
        else
            B[vf_valori].valoare=INFINIT;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=INFINIT;
        }
    }
    if(A[vf_operatori].nume[0]=='*')
    {
        if(B[vf_valori].valoare==0 || B[vf_valori-1].valoare==0)
        {
            vf_valori--;
            B[vf_valori].valoare=0;
        }
        else
        if(diferitInfinit(B[vf_valori].valoare) && diferitInfinit(B[vf_valori-1].valoare))
        {
        aux=B[vf_valori].valoare*B[vf_valori-1].valoare;
        vf_valori--;
        if(diferitInfinit(aux))
        B[vf_valori].valoare=aux;
        else
            B[vf_valori].valoare=INFINIT;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=INFINIT;
        }
    }
    if(A[vf_operatori].nume[0]=='/')
    {
        if(B[vf_valori].valoare==0)
        {
            esteCazDeNedeterminare=true;
            cout<<"S-a ajuns la o impartire la 0"<<'\n';
            return;
        }
        else
            if(diferitInfinit(B[vf_valori-1].valoare))
        {
        aux=B[vf_valori-1].valoare/B[vf_valori].valoare;
        vf_valori--;
        B[vf_valori].valoare=aux;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=INFINIT;
        }
    }
    if(A[vf_operatori].nume[0]=='^')
    {
        if(B[vf_valori-1].valoare==0 && B[vf_valori].valoare==0)
        {
            esteCazDeNedeterminare=true;
            cout<<"S-a ajuns la cazul 0 la puterea 0"<<'\n';
            return;
        }
        else
            if(B[vf_valori-1].valoare==0)
        {
           vf_valori--;
           B[vf_valori].valoare=0;
        }
        else
            if(B[vf_valori].valoare==0)
        {
            vf_valori--;
            B[vf_valori].valoare=1;
        }
        else
            if(!diferitInfinit(B[vf_valori-1].valoare) || !diferitInfinit(B[vf_valori].valoare))
        {
            vf_valori--;
            B[vf_valori].valoare=INFINIT;
        }
        else
        {
        aux=pow(B[vf_valori-1].valoare,B[vf_valori].valoare);
        vf_valori--;
        if(diferitInfinit(aux))
        B[vf_valori].valoare=aux;
        else
            B[vf_valori].valoare=INFINIT;
        }
    }
    if(A[vf_operatori].nume[0]=='#')
    {
        if(diferitInfinit(B[vf_valori].valoare) || diferitInfinit(B[vf_valori-1].valoare))
        {
        aux= B[vf_valori].valoare != B[vf_valori-1].valoare;
        vf_valori--;
        B[vf_valori].valoare=aux;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=0;
        }
    }
    if(A[vf_operatori].nume[0]=='=')
    {
        if(diferitInfinit(B[vf_valori].valoare) && diferitInfinit(B[vf_valori-1].valoare))
        {
        aux= B[vf_valori].valoare == B[vf_valori-1].valoare;
        vf_valori--;
        B[vf_valori].valoare=aux;
        }
        else
        {
            vf_valori--;
            B[vf_valori].valoare=0;
        }
    }
    if(A[vf_operatori].nume[0]=='<')
    {
        aux= B[vf_valori-1].valoare < B[vf_valori].valoare;
        vf_valori--;
        B[vf_valori].valoare=aux;
    }
    if(A[vf_operatori].nume[0]=='>')
    {
        aux= B[vf_valori-1].valoare > B[vf_valori].valoare;
        vf_valori--;
        B[vf_valori].valoare=aux;
    }
    if(strcmp(A[vf_operatori].nume,"cos")==0)
    {
        if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=cos(B[vf_valori].valoare);
        B[vf_valori].valoare=aux;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
    if(strcmp(A[vf_operatori].nume,"sin")==0)
    {
        if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=sin(B[vf_valori].valoare);
        B[vf_valori].valoare=aux;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
    if(strcmp(A[vf_operatori].nume,"ln")==0)
    {
        if(B[vf_valori].valoare<=0)
        {
            esteCazDeNedeterminare=true;
            cout<<"S-a ajuns la ln dintr-un numar negativ sau egal cu 0"<<'\n';
            return;
        }
        else
            if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=log(B[vf_valori].valoare);
        B[vf_valori].valoare=aux;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
    if(strcmp(A[vf_operatori].nume,"exp")==0)
    {
        if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=exp(B[vf_valori].valoare);
        if(diferitInfinit(aux))
        B[vf_valori].valoare=aux;
        else
            B[vf_valori].valoare=INFINIT;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
    if(strcmp(A[vf_operatori].nume,"abs")==0)
    {
        if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=abs(B[vf_valori].valoare);
        B[vf_valori].valoare=aux;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
    if(strcmp(A[vf_operatori].nume,"rad")==0)
    {
        if(B[vf_valori].valoare<0)
        {
            esteCazDeNedeterminare=true;
            cout<<"S-a ajuns la radical dintr-un numar negativ"<<'\n';
            return;
        }
        else
            if(diferitInfinit(B[vf_valori].valoare))
        {
        aux=sqrt(B[vf_valori].valoare);
        B[vf_valori].valoare=aux;
        }
        else
            B[vf_valori].valoare=INFINIT;
    }
}
void rezolva(operatorii A[NMAX],variabile B[NMAX],int indice,bool &esteCazDeNedeterminare)
{
    if(strcmp(operatori[indice].nume,")")!=0)
    {
        while(A[vf_operatori].prioritate>=operatori[indice].prioritate && vf_operatori>=0)
        {
            intrebari(A,B,esteCazDeNedeterminare);
            if(esteCazDeNedeterminare)
                return;
            vf_operatori--;
        }
        strcpy(A[++vf_operatori].nume,operatori[indice].nume);
        A[vf_operatori].prioritate=operatori[indice].prioritate;
    }
    else
    {
        while(A[vf_operatori].nume[0]!='(')
        {
            intrebari(A,B,esteCazDeNedeterminare);
            if(esteCazDeNedeterminare)
                return;
            vf_operatori--;
        }
        vf_operatori--;
    }

}
int greseala_operatori(char expresie[],char *p, int numarVariabile)
{

    char st[CMAX],curent[CMAX],dr[CMAX];
    bool stVariabila=false,drVariabila=false;
    bool curentSemn=false;
    bool ok=0;
    int indice=-1,indiceSemnSt=-1,indiceSemnDr=-1,poz=0;
    st[0]=NULL;
    curent[0]=NULL;
    dr[0]=NULL;
    p=strtok(expresie," ");
    while(p!=NULL)
    {
        strcpy(curent,p);
        p=strtok(NULL," ");
        poz+=strlen(curent);
        if(p==NULL)
            break;
        strcpy(dr,p);
        if((strcmp(curent,"sin")==0 || strcmp(curent,"cos")==0  || strcmp(curent,"rad")==0  || strcmp(curent,"exp")==0  || strcmp(curent,"abs")==0 || strcmp(curent,"ln")==0 )&& strcmp(dr,"(")!=0 )
        {
            cout<<"Nu ai paranteza deschisa dupa "<<curent<<" pe pozitia "<<poz<<", ";
            return 0;
        }
        curentSemn=false;
        indice=-1;
        for(int i=0; i<NROPERATORI && indice==-1; ++i)
        {
            if(strcmp(curent,operatori[i].nume)==0 && operatori[i].prioritate>=1 && operatori[i].prioritate<=4)
                indice=i;
            if(strcmp(curent,operatori[i].nume)==0)
                curentSemn=true;
        }
        if(indice!=-1) ///termenul curent este de prioritate 1,2,3 sau 4
        {
            stVariabila=false;
            drVariabila=false;
            bool esteSemn=false;
            for(int i=1; i<=numarVariabile && !stVariabila; i++)
                if(strcmp(st,var[i].nume)==0)
                    stVariabila=true;
            for(int i=0; i<NROPERATORI && !stVariabila && !esteSemn; ++i)
                if(strcmp(st,operatori[i].nume)==0)
                    esteSemn=true,indiceSemnSt=i;
            if(!esteSemn)
                stVariabila=true;
            esteSemn=false;
            for(int i=1; i<=numarVariabile && !drVariabila; i++)
                if(strcmp(dr,var[i].nume)==0)
                    drVariabila=true;
            for(int i=0; i<NROPERATORI && !drVariabila && !esteSemn; ++i)
                if(strcmp(dr,operatori[i].nume)==0)
                    esteSemn=true,indiceSemnDr=i;
            if(!esteSemn)
                drVariabila=true;
            if(!((stVariabila && drVariabila) || (stVariabila && indiceSemnDr==0) || (indiceSemnSt==1 && drVariabila) || (indiceSemnSt==1 && indiceSemnDr==0) || (stVariabila && indiceSemnDr>=11) || (indiceSemnSt==1 && indiceSemnDr>=11)))
            {
                cout<<"Trebuie sa ai un termen sau o functie de prioritate 5 in stanga si in dreapta unui operator"<<'\n';
                cout<<"pe pozitia "<<poz-1<<", ";
                return 0;
            }
        }
        else if(!curentSemn)
        {
            if(ok==0)
                indiceSemnSt=0;
            else
                indiceSemnSt=-1;
            indiceSemnDr=-1;
            for(int i=0; i<NROPERATORI && indiceSemnSt==-1; ++i)
                if(strcmp(st,operatori[i].nume)==0)
                    indiceSemnSt=i;
            for(int i=0; i<NROPERATORI && indiceSemnDr==-1; ++i)
                if(strcmp(dr,operatori[i].nume)==0)
                    indiceSemnDr=i;
            if(!((indiceSemnSt<11 && indiceSemnSt!=1 && indiceSemnSt>=0)&& (indiceSemnDr<11 && indiceSemnDr !=0 && indiceSemnDr>=0)))
            {
                cout<<"Trebuie sa ai un operator cu prioritatea de la 1 la 4 intre doi termeni sau intre un termen si o paranteza deschisa"<<'\n';
                if(st[strlen(st)-1]==')')
                  cout<<"intre caracterele de pe pozitiile "<<poz-2<<" si "<<poz-1<<", ";
                else
                  cout<<"intre caracterele de pe pozitiile "<<poz-1<<" si "<<poz<<", ";

                return 0;
            }
        }
        ok=1;
        strcpy(st,curent);
    }
    return 1;
}


int greseala_parantezare(char expresie[]) ///greselile in functie de inchiderea parantezelor
{
    int i=0,contor=0,l;
    l=strlen(expresie);
    while(i<=l)
    {
        if(contor<0) /// paranteze inchisa e in fata uneia deschise deci fals
        {
            cout<<"La pozitia"<<' '<<i-1<<' ';
            return 0;
        }
        if(expresie[i]=='(')
        {
            if(expresie[i+1]==')') ///nu am element intre paranteze deci fals
            {
                cout<<"Nu ai niciun termen intre parantezele de pe pozitiile"<<' '<<i<<" si "<<i+1<<", ";
                return 0;
            }
            contor++;
        }
        else if(expresie[i]==')')
        {
            if(expresie[i+1]=='(') /// nu am operator intre paranteze deci fals
            {
                cout<<"Nu ai niciun operator intre parantezele de pe pozitiile"<<' '<<i<<" si "<<i+1<<", ";
                return 0;
            }
            contor--;
        }
        i++;
    }
    if (contor==0)
    {
        return 1;
    }
    else
    {
        cout<<"La pozitia"<<' '<<i-1<<' ';
        return 0;
    }

}
void initializare_operatori()
{
    strcpy(operatori[0].nume,"(");
    operatori[0].prioritate=0;
    strcpy(operatori[1].nume,")");
    operatori[1].prioritate=0;
    strcpy(operatori[2].nume,"+");
    operatori[2].prioritate=1;
    strcpy(operatori[3].nume,"-");
    operatori[3].prioritate=1;
    strcpy(operatori[4].nume,"*");
    operatori[4].prioritate=2;
    strcpy(operatori[5].nume,"/");
    operatori[5].prioritate=2;
    strcpy(operatori[6].nume,"^");
    operatori[6].prioritate=3;
    strcpy(operatori[7].nume,"#");
    operatori[7].prioritate=4;
    strcpy(operatori[8].nume,"=");
    operatori[8].prioritate=4;
    strcpy(operatori[9].nume,"<");
    operatori[9].prioritate=4;
    strcpy(operatori[10].nume,">");
    operatori[10].prioritate=4;
    strcpy(operatori[11].nume,"cos");
    operatori[11].prioritate=5;
    strcpy(operatori[12].nume,"sin");
    operatori[12].prioritate=5;
    strcpy(operatori[13].nume,"ln");
    operatori[13].prioritate=5;
    strcpy(operatori[14].nume,"exp");
    operatori[14].prioritate=5;
    strcpy(operatori[15].nume,"abs");
    operatori[15].prioritate=5;
    strcpy(operatori[16].nume,"rad");
    operatori[16].prioritate=5;
}
void resetare(char x[], int dim)
{
    for(int i=0; i<dim; i++)
        x[i]=NULL;
}
void insereaza0(char sir[])
{
    int lg;
    lg=strlen(sir);
    for(int i=0;i<lg;i++)
        if(sir[i]=='-')
         if(sir[i-1]=='(' || i==0)
    {
     for(int j=lg-1;j>=i;j--)
             sir[j+1]=sir[j];
     sir[i]='0';
    }
}
int main()
{
    char expresie[CMAX],expresie_copy[CMAX],aux[CMAX];
    resetare(expresie,CMAX);
    bool esteCuvant=false,esteSubSir=false;
    bool esteParantezataCorect=false;
    bool esteScrisaCorect=false;
    bool esteChiarVariabila=false;
    int numarVariabile=0,cntrAux=0,lgExpresie,lgAux,nr=0;
    initializare_operatori();
    cout<<"Introdu expresia: ";
    cin.getline(expresie,CMAX);
    cout<<"Introdu numarul de variabile: ";
    cin>>numarVariabile;
    if(numarVariabile)
    cout<<"Citeste fiecare variabila folosita in expresie,cu tipul: NUME 'SPATIU' VALOARE"<<'\n';
    for(int i=1; i<=numarVariabile; ++i)
        cin>>var[i].nume>>var[i].valoare;
    insereaza0(expresie);
    lgExpresie=strlen(expresie);
    esteParantezataCorect=greseala_parantezare(expresie);
    if(!esteParantezataCorect)
        cout<<"expresia nu a fost parantezata corect!"<<'\n';
    else
    {
        expresie[lgExpresie++]=')';
        resetare(aux,CMAX);
        for(int i=0; i<lgExpresie; ++i)
        {
            if(expresie[i]!=' ' && !(expresie[i]>='0' && expresie[i]<='9'))
                aux[cntrAux++]=expresie[i];
            else if((expresie[i]>='0' && expresie[i]<='9') && cntrAux!=0)
                aux[cntrAux++]=expresie[i];
            for(int j=0; j<NROPERATORI && !esteCuvant; j++)
                if(strcmp(aux,operatori[j].nume)==0)
                    esteCuvant=true;
            if(esteCuvant)
            {
                esteCuvant=false;
                if(i-cntrAux>=0 && expresie[i-cntrAux]!=' ')
                {
                    for(int j=lgExpresie-1; j>=i-cntrAux+1; --j)
                        expresie[j+1]=expresie[j];
                    expresie[i-cntrAux+1]=' ';
                    lgExpresie++;
                }
                for( int j=lgExpresie-1; j>=i+1; --j)
                    expresie[j+1]=expresie[j];
                expresie[i+1]=' ';
                lgExpresie++;
                resetare(aux,CMAX);
                cntrAux=0;
            }
            else
            {
                esteSubSir=false;
                for(int j=1; j<=numarVariabile; ++j)
                    {
                    if(strcmp(aux,var[j].nume)==0)
                        esteCuvant=true;
                    else
                      {
                        aux[cntrAux++]=expresie[i+1];
                        if(strstr(var[j].nume,aux)!=NULL && strcmp(strstr(var[j].nume,aux),var[j].nume)==0)
                         esteSubSir=true;
                        aux[cntrAux-1]=NULL; cntrAux--;
                      }
                    }
                if(esteCuvant && !esteSubSir)
                {
                    esteCuvant=false;
                    if(i-cntrAux>=0 && expresie[i-cntrAux]!=' ')
                    {
                        for(int j=lgExpresie-1; j>=i-cntrAux+1; --j)
                            expresie[j+1]=expresie[j];
                        expresie[i-cntrAux+1]=' ';
                        lgExpresie++;
                    }
                    for( int j=lgExpresie-1; j>=i+1; --j)
                        expresie[j+1]=expresie[j];
                    expresie[i+1]=' ';
                    lgExpresie++;
                    resetare(aux,CMAX);
                    cntrAux=0;
                }
                esteCuvant=false;
            }
        }
        strcpy(expresie_copy,expresie);
        esteScrisaCorect=greseala_operatori(expresie_copy,p,numarVariabile);
        if(!esteScrisaCorect)
            cout<<"expresia nu este scrisa corect!"<<'\n';
        else
        {
            strcpy(stiva_operatori[++vf_operatori].nume,"(");
            stiva_operatori[vf_operatori].prioritate=0;
            bool esteSemn=false;
            bool esteVariabila=false;
            bool esteCazDeNedeterminare=false;
            p=strtok(expresie," ");
            while(p)
            {
                esteSemn=false;
                for(int i=0; i<NROPERATORI && !esteSemn; ++i)
                    if(strcmp(operatori[i].nume,p)==0)
                        esteSemn=true,indice=i;
                if(esteSemn)
                {
                    if(strcmp(p,"(")==0)
                    {
                        strcpy(stiva_operatori[++vf_operatori].nume,p);
                        stiva_operatori[vf_operatori].prioritate=0;
                    }
                    else if(operatori[indice].prioritate>stiva_operatori[vf_operatori].prioritate && strcmp(operatori[indice].nume,")")!=0)
                    {
                        strcpy(stiva_operatori[++vf_operatori].nume,operatori[indice].nume);
                        stiva_operatori[vf_operatori].prioritate=operatori[indice].prioritate;
                    }
                    else if(operatori[indice].prioritate<=stiva_operatori[vf_operatori].prioritate && strcmp(operatori[indice].nume,")")!=0)
                        rezolva(stiva_operatori,stiva_valori,indice,esteCazDeNedeterminare);
                    else if(strcmp(operatori[indice].nume,")")==0)
                        rezolva(stiva_operatori,stiva_valori,indice,esteCazDeNedeterminare);
                    if(esteCazDeNedeterminare)
                        break;
                }
                else
                {
                    esteVariabila=false;
                    for(int i=1; i<=numarVariabile && !esteVariabila; ++i)
                        if(strcmp(var[i].nume,p)==0)
                            esteVariabila=true,indice=i;
                    if(esteVariabila)
                        stiva_valori[++vf_valori].valoare=var[indice].valoare;
                    else
                    {
                        lgAux=strlen(p);
                        nr=0;
                        for(int i=0; i<lgAux; ++i)
                            nr=nr*10+p[i]-'0';
                        stiva_valori[++vf_valori].valoare=nr;
                    }
                }
                p=strtok(NULL," ");
            }
            if(!esteCazDeNedeterminare)
                {
                if(stiva_valori[0].valoare==INFINIT)
                cout<<"INFINIT"<<'\n';
                else
                    cout<<"Valoarea expresiei este: "<<stiva_valori[0].valoare;
                }
        }
    }
    return 0;
}
