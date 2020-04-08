#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char tmp[100];

int ZERO = 0;
int V0,V1,A0,A1,A2,A3,A4,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,S0,S1,S2,S3;
int S4,S5,S6,S7,RA;   //καταχωρητες 1-1 αντιστοιχια με την assembly mips

int W = 21;
int H = 11;
int startX = 1;
int TotalElements = 231;
char map[232] = "I.IIIIIIIIIIIIIIIIIII"
                "I....I....I.......I.I"
                "III.IIIII.I.I.III.I.I"
                "I.I.....I..I..I.....I"
                "I.I.III.II...II.I.III"
                "I...I...III.I...I...I"
                "IIIII.IIIII.III.III.I"
                "I.............I.I...I"
                "IIIIIIIIIIIIIII.I.III"
                "@...............I..II"
                "IIIIIIIIIIIIIIIIIIIII";



void printLabyrinth(void){
    int i=0,j=0,k=0;
    T0 = i;
    T1 = j;
    T2 = k;
    usleep(200000);
    printf("Labyrinth:\n");
    
    for_label_1:
    if(T0>=S4) goto exit_label;
    T1 = 0;
    for_label_2:
    if(T1>=S3) goto continue_label;
    tmp[T1] = map[T2];  //προσθηκη μιας σειρας στοιχειων του λαβυρινθου

    T1 = T1 + 1;
    T2 = T2 + 1;
    goto for_label_2;
          
    continue_label:
    // tmp[T4] = '\0';
    printf("%s\n",tmp); //εκτύπωση κάθε φορά του temp

    T0 = T0 +1;
    goto for_label_1;
    
    exit_label:
    return;
    
    
}

void makeMove(void){
    int stack[2];
    stack[0] = A0;
    stack[1] = RA;
    int S0 = A0; //S0 = index(startX)    
    int T1 = 1; 
        
    if(A0>=0) goto scnd;
        goto end_if;
    scnd:    
    if(A0<S1) goto if_label;
        goto end_if;

    if_label:
    if(map[A0] != '.') goto else_if;//ελεγχος για το σωστο path
        map[A0] = '*'; //αντικατασταση του με *
        printLabyrinth();//κληση της συναρτησης για εκτυπωση
        A0 = stack[0];
        
        if_1:
            A0= S0+T1;
            makeMove();             
            if(V0 != T1) goto if_2;//ελεγχος του δεξιου στοιχειου
                A0 = stack[0];
                map[A0] = '#';
                V0 = 1;
                return;

        if_2:
            A0= S0+S3;
             makeMove();
            
            if(V0 != T1) goto if_3;//ελεγχος του κατω στοιχειου
                A0 = stack[0];
                map[A0] = '#';
                V0 = 1;
                return;

        if_3:
            A0= S0-T1;
            makeMove();
           
            if(V0 != T1) goto if_4;//ελεγχος του αριστερου 
                A0 = stack[0];
                map[A0] = '#';
                V0 = 1;
                return;

        if_4:
            A0= S0-S3;
            makeMove();
            
            if(V0 != T1) goto end_if;//ελεγχος του πανω στοιχειου
               A0 = stack[0];
                map[A0] = '#';
                V0 = 1;
                return;

    else_if:
        if(map[A0] != '@') goto end_if;  //ευρεση του τελους
            map[A0] = '%';               //αντικατασταση με το % συμβολο

            printLabyrinth();
            V0 = 1;
            goto return_label;
            
    end_if:
        V0= 0;
    
    return_label:
    A0 = stack[0];
    S0 = stack[1];    
    return;    
}
int main(void){
    S3 = W;
    S4 = H;
    S1 = TotalElements;
    
    A0 = startX;
    makeMove();
    printLabyrinth();
    
    return 0;
}