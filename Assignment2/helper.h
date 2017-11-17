#include <stdio.h>
#include <string.h>
//author : Zihao Li
//Student Id: W1273148
//split the string
void cutString(int index, char * buf, char * (number[]), int * technology, int *paid){
    char *p;

    p = strtok(buf, " ");
    number[index] = (char *) malloc(sizeof(char*));
    strcpy(number[index],p);

    p = strtok(NULL, " ");
    * (technology + index) = (int)(*p - '0');

    p = strtok(NULL, " ");
    * (paid + index) = (int)(*p - '0');

}

int readFile(char * (number[]), int * technology, int* paid){
    FILE *fp;
    int size;
    char buf[1024];
    int index = 0;
    if((fp=fopen("Verification_Database.txt","r"))==NULL) {
        printf("File cannot be opened\n");
    } else{
        printf("File opened for reading\n");
        while(!feof(fp)){
            fgets(buf,1024,fp);
            if(feof(fp)){
                break;
            }
            printf("%s\n",buf);
            cutString(index, buf, number, technology, paid);
            index++;
        }
        fclose(fp);
    }
    return index;
}

void copyMemory(char * src, char * des, int len){
    for(int i = 0 ; i < len; i++){
        *(des + i) = *(src + i);
    }
}

void errorOutput(char * error){
    perror(error);
}
