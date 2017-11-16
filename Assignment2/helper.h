#include <stdio.h>
#include <string.h>
void cutString(int index, char * buf, char * (number[]), int * technology, int *paid){
    char *p;
    p = strtok(buf, " ");
    printf("p = %s \n",p);
    strcpy(number[index],p);
    p = strtok(NULL, " ");
    printf("p = %s \n",p);
    * (technology + index) = (int)(*p - '0');
    p = strtok(NULL, " ");
    printf("p = %s\n", p);
    * (paid + index) = (int)(*p - '0');

}

void readFile(char * (number[]), int * technology, int* paid){
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
            //printf("%s\n", buf); //输出
        }
        fclose(fp);
    }
}



void errorOutput(char * error){
    perror(error);
}
