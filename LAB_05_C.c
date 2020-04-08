#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char temp[100]; //Global


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
    int i,j,k=0;
    usleep(200000);
    printf("Labyrinth:\n");   
    for(i=0;i<H;i++){
        for(j=0; j<W; j++){
            temp[j] = map[k]; //προσθηκη μιας σειρας στοιχειων του λαβυρινθου
            k++;
        }              
        temp[j+1]='\0';
        printf("%s\n", temp); //εκτύπωση κάθε φορά του temp
                      
    }
}

int makeMove(int index){
    if(index<0 || index>=TotalElements)
        return 0;
    if(map[index] == '.'){ //ελεγχος για το σωστο path
        map[index] = '*';  //αντικατασταση του με *   
        printLabyrinth();  //κληση της συναρτησης για εκτυπωση                         
    
        if(makeMove(index+1) == 1){//ελεγχος του δεξιου στοιχειου
            map[index] = '#';   
            return 1;
        }
        if(makeMove(index+W) == 1){//ελεγχος του κατω στοιχειου
            map[index] = '#';
            return 1;
        }
        if(makeMove(index-1) == 1){//ελεγχος του αριστερου στοιχειου
            map[index]= '#' ;
            return 1;
        }
        if(makeMove(index-W)==1){//ελεγχος του πανω στοιχειου
            map[index] = '#';
           return 1;
        }
    }
    else if(map[index] == '@'){//ευρεση του τελους
        map[index] = '%';      //αντικατασταση με το % συμβολο
        printLabyrinth();
        return 1;
    }
    return 0;
}

int main(){
    makeMove(startX);
    printLabyrinth();
   
    return 0;
}

