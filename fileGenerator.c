#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>

int main(){

long int i;

int num;

srand(time(NULL));

FILE *rfile;
FILE *bfile;

rfile = fopen("f1.txt","w");

bfile = fopen("b1.bin","wb");

	for(i=0;i<10104;i++){

		num = (rand()%50);

		fprintf(rfile,"%d\n",num);

		fwrite(&num,sizeof(int),1,bfile);


	}

fclose(rfile);

fclose(bfile);

}
