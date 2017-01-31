#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

#define TAM 11
#define pos_i 2
#define pos_j 0
#define cor 7
#define cor_mapa 32

int MAP[TAM][TAM];
int pi,pj;
int op;
int nivel=1;

HANDLE hConsole;    //mudar cor
char buf[1024];     //imprimir .txt
FILE *file;         //imprimir .txt
size_t nread;       //imprimir .txt


struct monstros{
    int vida,atk,def,key,i,j,vidamaxima;
}monstro[TAM*3];
struct player{
    int vida,vidamaxima,atk,def,key,exp,level,mov;
    char nome[6];
}p;
struct ranking{
    int pos,mov;
    char nome[6];
}ranking[11],aux,jogador;
void mostraranking(){
    int i,j,k,n;
    file = fopen("ranking.txt", "r");
    if (file) {
        while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
            fwrite(buf, 1, nread, stdout);
            if (ferror(file)) {
                /* deal with error */
            }
            fclose(file);
        }
    for(k=1;k<=3;k++){
        switch(k){
            case 1: file = fopen("ranking1.txt", "r"); j=13; i=13; break;
            case 2: file = fopen("ranking2.txt", "r"); j=33; i=13; break;
            case 3: file = fopen("ranking3.txt", "r"); j=53; i=13; break;
        }
        if (file == NULL)
            printf("Erro ao abrir para leitura");
        else {
            while (!feof(file))
                for(n=0;n<=10;n++)
                    fscanf(file,"%d %s %d",&ranking[n].pos,ranking[n].nome,&ranking[n].mov);
        fclose(file);
        }
        gotoxy(j+4,i-1);
            printf("FASE %i",k);
        for(n=1;n<=10;n++){
            gotoxy(j,i);
            printf("%.2d %.6s %.3d\n",ranking[n].pos,ranking[n].nome,ranking[n].mov);
            i++;
        }
    }
    getch();
    system("cls");
}
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
int irand(int min, int max) {
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}
void newplayer(){
    p.vidamaxima=50;
    p.vida=p.vidamaxima;
    p.atk=10;
    p.def=5;
    p.key=0;
    p.exp=0;
    p.level=1;
    p.mov=0;
}
void level_jogador(){
    if(p.exp>=100&&p.level<5){
        p.vidamaxima=p.vidamaxima*1.1;
        p.vida=p.vidamaxima;
        p.atk=p.atk+1;
        p.def=p.def+1;
        p.exp=p.exp-100;
        p.level=p.level+1;
    }
}
void gerar_monstros(){
    MAP[0][0]=2;
    int n,i,j;
    for(n=0;n<TAM*nivel;n++){
        srand(time(NULL));
        do{
            i=irand(0,TAM-1);
            j=irand(0,TAM-1);
        }while(MAP[i][j]==1 || i==0&&j==0 || i==TAM-1&&j==TAM-1);
        MAP[i][j]=1;
    }
    n=0;
    for(i=0;i<TAM;i++)
        for(j=0;j<TAM;j++)
            if(MAP[i][j]==1){
                monstro[n].key = 0;
                monstro[n].vidamaxima = irand(20,30);
                monstro[n].vida = monstro[n].vidamaxima;
                monstro[n].atk = irand(7,10);
                monstro[n].def = irand(1,5);
                monstro[n].i = i;
                monstro[n].j = j;
                n++;
            }
    n=irand(0,TAM*nivel-1);
    monstro[n].key=1;
    monstro[n].vidamaxima = irand(25,40);
    monstro[n].vida = monstro[n].vidamaxima;
    monstro[n].atk = irand(8,15);
    monstro[n].def = irand(3,7);
}
void clearmap(){
    int i,j;
    for(i=0;i<TAM;i++)
        for(j=0;j<TAM;j++)
            MAP[i][j]=0;
}
void grades(){
    int i,j;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor_mapa);
    gotoxy(pos_j+1,pos_i+1);
    printf("%c",201);
    gotoxy(pos_j+TAM*2+1,pos_i+1);
    printf("%c",187);
    gotoxy(pos_j+1,pos_i+TAM*2+1);
    printf("%c",200);
    gotoxy(pos_j+TAM*2+1,pos_i+TAM*2+1);
    printf("%c",188);
    for(i=2;i<=TAM*2;i++){
        gotoxy(pos_j+i,pos_i+1);
        if(i % 2 == 0)
            printf("%c",205);
        else
            printf("%c",203);
    }
    for(i=2;i<=TAM*2;i++){
        gotoxy(pos_j+i,pos_i+TAM*2+1);
        if(i % 2 == 0)
            printf("%c",205);
        else
            printf("%c",202);
    }
    for(i=2;i<=TAM*2;i++){
        gotoxy(pos_j+1,pos_i+i);
        if(i % 2 == 0)
            printf("%c",186);
        else
            printf("%c",204);
    }
    for(i=2;i<=TAM*2;i++){
        gotoxy(pos_j+TAM*2+1,pos_i+i);
        if(i % 2 == 0)
            printf("%c",186);
        else
            printf("%c",185);
    }
    for(i=3;i<=TAM*2-1;i=i+2){
        for(j=2;j<=TAM*2;j++){
            gotoxy(pos_j+j,pos_i+i);
        if(j % 2 == 0)
            printf("%c",205);
        else
            printf("%c",206);
        }
    }
    for(i=2;i<=TAM*2;i=i+2){
        for(j=3;j<=TAM*2;j=j+2){
            gotoxy(pos_j+j,pos_i+i);
            printf("%c",186);
        }
    }
    SetConsoleTextAttribute(hConsole, cor);
}
void movimento(){
    int tecla,i,j,n,passou=0;
    do{
        grades();
        status();
        mostramap();
        MAP[pi][pj]=0;
        tecla = getch();
        if(tecla==27){
            system("cls");
            main();
        }
        gotoxy(TAM*2+2+pos_j+1+12,pos_i+3);
        printf("\t");
        gotoxy(TAM*2+2+pos_j+1+11,pos_i+4);
        printf("\t");
        gotoxy(TAM*2+2+pos_j+1+11,pos_i+5);
        printf("\t");
        gotoxy(TAM*2+2+pos_j+1+10,pos_i+6);
        printf("\t");
        gotoxy(TAM*2+2+pos_j+1+12,pos_i+7);
        printf("\t");
        for(i=11;i<18;i++){
            gotoxy(TAM*2+2+pos_j+1,pos_i+i);
            printf("\t\t\t\t\t\t");
        }
        switch( tecla ){
            case 72: //cima
                if (pi > 0){
                    if(MAP[pi-1][pj]==1)
                        batalha(pi-1,pj);//batalha
                    else{
                        pi--;
                        p.mov++;
                        if(p.vida<p.vidamaxima)
                            p.vida++;
                    }
                }
                break;
            case 80: //baixo
                if (pi < TAM-1){
                    if(MAP[pi+1][pj]==1)
                        batalha(pi+1,pj);
                    else{
                        pi++;
                        p.mov++;
                        if(p.vida<p.vidamaxima)
                            p.vida++;
                    }
                }
                break;
            case 75: //esquerda
                if(pj>0){
                    if(MAP[pi][pj-1]==1)
                        batalha(pi,pj-1);
                    else{
                        pj--;
                        p.mov++;
                        if(p.vida<p.vidamaxima)
                            p.vida++;
                    }
                }
                break;
            case 77: //direita
                if (pj < TAM-1){
                    if(MAP[pi][pj+1]==1)
                        batalha(pi,pj+1);
                    else{
                        pj++;
                        p.mov++;
                        if(p.vida<p.vidamaxima)
                            p.vida++;
                    }
                }
                break;
        }
        MAP[pi][pj]=2;
        status();
        if(pi==TAM-1 && pj==TAM-1 && p.key==1)
            passou=1;
    }while( p.vida>0 && passou!=1);
}
void mostramap(){
    int i,j;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor_mapa);
    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            gotoxy(pos_j+j*2+2,pos_i+i*2+2);
            switch (MAP[i][j]){
                //case 1: printf("X"); break //mostrar monstro
                case 2: printf("%c",514); break;
                default: printf(" "); break;
            }
        }
    }
    gotoxy(pos_j+j*2,pos_i+i*2);
    printf("%c", 178);
    SetConsoleTextAttribute(hConsole, cor);
}
void status(){
    int i,j,monstros=0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(i=pi-1;i<=pi+1;i++)
        if(i>=0 && i<TAM)
            for(j=pj-1;j<=pj+1;j++)
                if(j>=0 && j<TAM)
                    if(MAP[i][j]==1)
                        monstros++;
    SetConsoleTextAttribute(hConsole, 15);
    gotoxy(pos_j+(TAM*2-1)/2-1,pos_i);
    printf("NIVEL %d",nivel);
    gotoxy(TAM*2+2+pos_j+1,pos_i+2);
    printf("Monstros promixos: %d",monstros);
    gotoxy(TAM*2+2+pos_j+1,pos_i+3);
    printf("%c Vida: %.2d/%d",3,p.vida,p.vidamaxima);
    gotoxy(TAM*2+2+pos_j+1,pos_i+4);
    printf("Ataque: %.2d",p.atk);
    gotoxy(TAM*2+2+pos_j+1,pos_i+5);
    printf("Defesa: %.2d",p.def);
    gotoxy(TAM*2+2+pos_j+1,pos_i+6);
    printf("Level: %.2d",p.level);
    gotoxy(TAM*2+2+pos_j+1,pos_i+7);
    printf("Exp: %.2d/100",p.exp);
    gotoxy(TAM*2+2+pos_j+1,pos_i+8);
    printf("Possui chave: ");
    if(p.key==1)
        printf("Sim");
    else
        printf("Nao");
    gotoxy(TAM*2+2+pos_j+1,pos_i+9);
    printf("Movimentos: %.3d",p.mov);
    SetConsoleTextAttribute(hConsole, cor);
}
void batalha (int i, int j){
    int n,atkreal,b,ix=25,exp;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(n=0;n<TAM*nivel;n++)
        if(monstro[n].i==i&&monstro[n].j==j)
            break;
    atkreal = irand(1,p.atk);
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(TAM*2+2+pos_j+1+11,pos_i+11);
    printf("B A T A L H A");
    gotoxy(TAM*2+2+pos_j+1+4,pos_i+12);
    printf("Player");
    gotoxy(TAM*2+2+pos_j+1,pos_i+13);
    printf("Ataque: %.2d/%.2d",atkreal,p.atk);
    gotoxy(TAM*2+2+pos_j+1,pos_i+14);
    printf("Defesa: %d",p.def);
    if(atkreal>monstro[n].def)
        monstro[n].vida=monstro[n].vida-(atkreal-monstro[n].def);
    if(monstro[n].vida<=0){
        monstro[n].vida=0;
        MAP[i][j]=0;
        if(monstro[n].key==1)
            p.key=1;
        exp=irand(5,20);
        p.exp += exp;
        level_player();
        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(TAM*2+2+pos_j+1+12,pos_i+7);
        printf("+%.2d!",exp);
        SetConsoleTextAttribute(hConsole, 14);
        gotoxy(TAM*2+2+pos_j+1,pos_i+16);
        printf("Monstro derrotado!");
        gotoxy(TAM*2+2+pos_j+1,pos_i+17);
        printf("Ganhou %.2d pontos de experiencia.",exp);
        SetConsoleTextAttribute(hConsole, cor);
    }
    else
    {
        gotoxy(TAM*2+2+pos_j+1,pos_i+16);
        printf("\t\t\t\t");
        gotoxy(TAM*2+2+pos_j+1,pos_i+17);
        printf("\t\t\t\t\t\t");
        gotoxy(TAM*2+2+pos_j+1+24,pos_i+12);
        printf("Monstro");
        atkreal = irand(1,monstro[n].atk);
        gotoxy(TAM*2+2+pos_j+1+20,pos_i+14);
        printf("Ataque: %.2d/%.2d",atkreal,monstro[n].atk);
        gotoxy(TAM*2+2+pos_j+1+20,pos_i+15);
        printf("Defesa: %d",monstro[n].def);
        if(atkreal>p.def){
            p.vida=p.vida-(atkreal-p.def);
            gotoxy(TAM*2+2+pos_j+1+14,pos_i+3);
            SetConsoleTextAttribute(hConsole, 12);
            printf("-%d",atkreal-p.def);
            SetConsoleTextAttribute(hConsole, cor);
            if(p.vida<=0)
                p.vida=0;
        }else
            gotoxy(TAM*2+2+pos_j+1+12,pos_i+3);
            printf("\t\t");
    }
    gotoxy(TAM*2+2+pos_j+1+20,pos_i+13);
    printf("Vida: %.2d/%.2d",monstro[n].vida,monstro[n].vidamaxima);
}
void level_player(){
    if(p.exp>=100&&p.level<5){
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(TAM*2+2+pos_j+1+12,pos_i+3);
        printf("+%d!",p.vidamaxima/10);
        gotoxy(TAM*2+2+pos_j+1+11,pos_i+4);
        printf("+1!");
        gotoxy(TAM*2+2+pos_j+1+11,pos_i+5);
        printf("+1!");
        gotoxy(TAM*2+2+pos_j+1+10,pos_i+6);
        printf("+1!");
        SetConsoleTextAttribute(hConsole, cor);
        p.vida+=p.vidamaxima*0.1;
        p.vidamaxima*=1.1;
        p.atk++;
        p.def++;
        p.exp-=100;
        p.level++;
    }
}
void fim_fase(){
    if(p.vida==0){
        system("cls");
        SetConsoleTextAttribute(hConsole, 12);
        PlaySound("gameover.wav", NULL, SND_FILENAME);
        PlaySound("yousuck.wav", NULL, SND_FILENAME);
        file = fopen("gameover.txt", "r");
        if (file) {
            while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
                fwrite(buf, 1, nread, stdout);
            if (ferror(file)) {
                /* deal with error */
            }
            fclose(file);
        }
        getch();
        system("cls");
    }
    else{
        wranking();
        if(nivel<3){
            p.vida=p.vidamaxima;
            p.mov=0;
            p.key=0;
            pi=pj=0;
        }
        else{
            PlaySound("good.wav", NULL, SND_ASYNC|SND_FILENAME);
            file = fopen("parabens.txt", "r");
            if (file) {
                while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
                    fwrite(buf, 1, nread, stdout);
                if (ferror(file)) {
                    /* deal with error */
                }
                fclose(file);
            }
            getch();
            system("cls");
        }
        nivel++;
    }
}
void wranking(){
    int i,j,k;
    system("cls");

    switch(nivel){
        case 1: file = fopen("ranking1.txt", "r+");break;
        case 2: file = fopen("ranking2.txt", "r+");break;
        case 3: file = fopen("ranking3.txt", "r+");break;
    }
    if (ferror(file)){
        /*erro*/
    }
    else {
        while (!feof(file))
            for(i=0;i<=10;i++)
                fscanf(file,"%d %s %d",&ranking[i].pos,ranking[i].nome,&ranking[i].mov);
    }
    jogador.mov=p.mov;
    for(i=1;i<=10;i++){
        if(jogador.mov<=ranking[i].mov){
            jogador.pos=i;
            for(j=i;j<10;j++)
                ranking[j].pos++;
            ranking[10]=jogador;
            break;
        }
    }
    for(i=10;i>1;i--)
        if(ranking[i].pos<ranking[i-1].pos){
            aux=ranking[i];
            ranking[i]=ranking[i-1];
            ranking[i-1]=aux;
        }

    for(i=1;i<=10;i++)
        printf("%.2d %.6s %.3d\n",ranking[i].pos,ranking[i].nome,ranking[i].mov);
    if(jogador.pos!=0){
        gotoxy(4,jogador.pos);
        printf("       %.3d",p.mov);
        gotoxy(4,jogador.pos);
        i=0;
        do{
            gotoxy(4+i,jogador.pos);
            p.nome[i] = getch();
            switch(p.nome[i]){
                case 13: //enter
                    for(k=i;k<6;k++)
                        p.nome[k]=255;
                    i=6;
                    break;
                case 8: //apagar
                    if(i>0){
                        gotoxy(4+i-1,jogador.pos);
                        printf(" ",p.nome[i]);
                        i--;
                    }
                    break;
                default: //tecla
                    printf("%c",p.nome[i]);
                    i++;
                    break;
            }
        }while(i<6);
        strcpy(ranking[jogador.pos].nome,p.nome);
        rewind(file);
        fprintf(file,"00 ------ 000\n");
        for(i=1;i<=10;i++)
            fprintf(file,"%.2d %s %.3d\n",ranking[i].pos,ranking[i].nome,ranking[i].mov);
    }
    else
        getch();
    fclose(file);
    system("cls");
}
int abertura(){
    int op=1,aux,x,y;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    newplayer();
    SetConsoleTextAttribute(hConsole, 10);
    file = fopen("inicio.txt", "r");
    if (file) {
        while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
            fwrite(buf, 1, nread, stdout);
        if (ferror(file)) {
            /* deal with error */
        }
    fclose(file);
    }
    SetConsoleTextAttribute(hConsole, 15);
    PlaySound("intro.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    gotoxy(19,20);
    printf("%c",201);
    gotoxy(19,24);
    printf("%c",200);
    gotoxy(31,20);
    printf("%c",187);
    gotoxy(31,24);
    printf("%c",188);
    for(x=20;x<31;x++)
        for(y=20;y<=24;y=y+4){
            gotoxy(x,y);
            printf("%c",205);
        }
    for(x=19;x<=31;x=x+12)
        for(y=21;y<24;y++){
            gotoxy(x,y);
            printf("%c",186);
        }
    do{
        aux=getch();
        switch(aux){
            case 77:
                if(op<3)
                    op++;
                else
                    op=1;
                break;
            case 75:
                if(op>1)
                    op--;
                else
                    op=3;
                break;
        }
        switch(op){
            case 1:
                SetConsoleTextAttribute(hConsole, 10);
                gotoxy(1,1);
                system("cls");
                file = fopen("inicio.txt", "r");
                if (file) {
                    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
                        fwrite(buf, 1, nread, stdout);
                if (ferror(file)) {
                    /* deal with error */
                }
                fclose(file);
                }
                SetConsoleTextAttribute(hConsole, 15);
                gotoxy(19,20);
                printf("%c",201);
                gotoxy(19,24);
                printf("%c",200);
                gotoxy(31,20);
                printf("%c",187);
                gotoxy(31,24);
                printf("%c",188);
                for(x=20;x<31;x++)
                    for(y=20;y<=24;y=y+4){
                        gotoxy(x,y);
                        printf("%c",205);
                    }
                for(x=19;x<=31;x=x+12)
                    for(y=21;y<24;y++){
                        gotoxy(x,y);
                        printf("%c",186);
                    }
                break;
            case 2:
                SetConsoleTextAttribute(hConsole, 10);
                gotoxy(1,1);
                system("cls");
                file = fopen("inicio.txt", "r");
                if (file) {
                    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
                        fwrite(buf, 1, nread, stdout);
                if (ferror(file)) {
                        /* deal with error */
                }
                fclose(file);
                }
                SetConsoleTextAttribute(hConsole, 15);
                gotoxy(36,20);
                printf("%c",201);
                gotoxy(36,24);
                printf("%c",200);
                gotoxy(48,20);
                printf("%c",187);
                gotoxy(48,24);
                printf("%c",188);
                for(x=37;x<48;x++)
                    for(y=20;y<=24;y=y+4){
                        gotoxy(x,y);
                        printf("%c",205);
                    }
                for(x=36;x<=48;x=x+12)
                    for(y=21;y<24;y++){
                        gotoxy(x,y);
                        printf("%c",186);
                    }
                break;
            case 3:
                SetConsoleTextAttribute(hConsole, 10);
                gotoxy(1,1);
                system("cls");
                file = fopen("inicio.txt", "r");
                if (file) {
                    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
                        fwrite(buf, 1, nread, stdout);
                    if (ferror(file)) {
                        /* deal with error */
                    }
                fclose(file);
                }
                SetConsoleTextAttribute(hConsole, 15);
                gotoxy(52,20);
                printf("%c",201);
                gotoxy(52,24);
                printf("%c",200);
                gotoxy(64,20);
                printf("%c",187);
                gotoxy(64,24);
                printf("%c",188);
                for(x=53;x<64;x++)
                    for(y=20;y<=24;y=y+4){
                        gotoxy(x,y);
                        printf("%c",205);
                    }
                for(x=52;x<=64;x=x+12)
                    for(y=21;y<24;y++){
                        gotoxy(x,y);
                        printf("%c",186);
                    }
                break;

        }
    }while(aux!=13);
    PlaySound(NULL, 0, 0);
    system("cls");
    return op;
}
void mostrar_nivel(){
    switch(nivel){
        case 1:
            file = fopen("1.txt", "r");
            PlaySound("wantssome.wav", NULL, SND_ASYNC|SND_FILENAME);
            break;
        case 2:
            file = fopen("2.txt", "r");
            PlaySound("letsrock.wav", NULL, SND_ASYNC|SND_FILENAME);
            break;
        case 3:
            file = fopen("3.txt", "r");
            PlaySound("ready.wav", NULL, SND_ASYNC|SND_FILENAME);
            break;
    }
    SetConsoleTextAttribute(hConsole, 14);
    if (file) {
        while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
            fwrite(buf, 1, nread, stdout);
        if (ferror(file)) {
            /* deal with error */
        }
        fclose(file);
    }
    getch();
    system("cls");
}
void jogo(){
    nivel=1;
    newplayer();
    do{
        mostrar_nivel();
        clearmap();
        pi=pj=0;
        gerar_monstros();
        movimento();
        fim_fase();
    }while(p.vida>0 && nivel<=3);
}
int main(){
    do{
        op=abertura();
        switch(op){
            case 3: exit(0);
            case 2: mostraranking(); break;
            case 1: jogo(); break;
        }
    }while(op!=0);
}
