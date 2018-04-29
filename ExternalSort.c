#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void WriteInFile(int buffer[],FILE** writeFile,FILE** readableFile,long int bufferSize);

long int min(long int x,long int y);

void merge(int arr[],long int l,long int m,long int r);

void Sort(int arr[],long int n);

void readIntoArray(FILE** readFile,int buffer[],long long int fileSize);

int getmin(int inputbuffer[],int numfiles,FILE** resultfile);

void fillbuffer(int inputbuffer[],int minfile,FILE** file,long int tempfileSizes[]);


int main(){

clock_t begin = clock();

char inputfilename[100];
int numfiles,j;

printf("Enter file name\n");
scanf("%s",inputfilename);

FILE *p;

FILE *result;

result = fopen("result.txt","w");	//Final sorted file

p = fopen(inputfilename,"rb");

fseek(p,0,SEEK_END);

long long int fileSize = ftell(p);	//Size of input file
int filenumber = 1;

fseek(p,0,SEEK_SET);

// Calculate number of temp files

	if(fileSize%(100*sizeof(int)) == 0){

	numfiles = fileSize/(100*sizeof(int));		

	}

	else{

	numfiles = fileSize/(100*sizeof(int)) + 1;

	}

char filename[100];

char filenameReadable[100];

printf("fileSize = %lld\n",fileSize);

printf("Number of files = %d\n",numfiles);

FILE *files[numfiles+1];

FILE *filesReadable[numfiles+1];

long int tempfileSizes[numfiles+1];

// For each file read 100 numbers


int buffer[100];

int i = 0;

for(i=0;i<100;i++){

buffer[i] = -1;


}


	while(ftell(p) != fileSize){
	
		
	readIntoArray(&p,buffer,fileSize);		// Store buffer size into array
	
	i = 0;
	
	while(buffer[i] != -1 && i < 100){
	i++;
	
	}
	
	//printf("Buffer Size = %d\n",i); 
	
	Sort(buffer,i);					// Sort the array
	
	
	sprintf(filename,"%d.bin",filenumber);
	
	sprintf(filenameReadable,"%d.txt",filenumber);
	
	//printf("filename = %s\n",filename);

	files[filenumber] = fopen(filename,"wb");
	
	filesReadable[filenumber] = fopen(filenameReadable,"w");
	
	WriteInFile(buffer,&files[filenumber],&filesReadable[filenumber],i);	// Write sorted array in file
	
	 tempfileSizes[filenumber] = ftell(files[filenumber]);
	
	//printf("tempfileSizes[%d] = %ld\n",filenumber,tempfileSizes[filenumber]);
	
	fclose(files[filenumber]);
	
	fclose(filesReadable[filenumber]);
	
		for(i=0;i<100;i++){

		buffer[i] = -1;


		}
	
	filenumber = filenumber + 1;


	}
	
	
	//********** all files created********
	
	
int inputbuffer[numfiles+1];

	for(i=0;i<=numfiles;i++){

	buffer[i] = -1;

	}	
	
// put all the file pointers at start

//Initially fill the array
// Last file will have atleast one element

int num;
	
for(i=1;i<=numfiles;i++){

	sprintf(filename,"%d.bin",i);

	files[i] = fopen(filename,"rb");
	
	fread(&num,sizeof(int),1,files[i]);

	inputbuffer[i] = num;

}


int minfile;

int finishedfiles;

while(1){

//Get the least number in present inputbuffer


minfile = getmin(inputbuffer,numfiles,&result);

// This will refill buffer
// If file ended it will refill with -1

fillbuffer(inputbuffer,minfile,&files[minfile],tempfileSizes);



//Calculate number of finished files
finishedfiles = 0;

	for(i=1;i<=numfiles;i++){

		if(ftell(files[i]) == tempfileSizes[i]){

		finishedfiles++;

		}

	}

	// condition for while to end
	if(finishedfiles == numfiles){
	minfile = getmin(inputbuffer,numfiles,&result);
	break;
	}



}



fclose(result);

//Close all file pointers
//remove extra files created			
		
for(i=1;i<=numfiles;i++){

	sprintf(filename,"%d.bin",i);
	sprintf(filenameReadable,"%d.txt",i);
	fclose(files[i]);
	remove(filenameReadable);
	remove(filename);


}

// Printing execution time

clock_t end = clock();

double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;

printf("Time Spent = %f\n",time_spent);
	
}

//***********************************************************
//  This function refills the buffer from corresponding file
//  after the min number is added
//
//  If that file has ended, it adds -1
//
//***********************************************************

void fillbuffer(int inputbuffer[],int minfile,FILE** file,long int tempfileSizes[]){


int num;

if(ftell(*file) >= tempfileSizes[minfile]){

inputbuffer[minfile] = -1;
return;

}

fread(&num,sizeof(int),1,*file);

inputbuffer[minfile] = num;


}

//***********************************************************
//  This function adds min num from buffer to final file
//  return the filenumber from which the number was added
//
//***********************************************************


int getmin(int inputbuffer[],int numfiles,FILE** resultfile){


int i;
int minfile;
int min;

// give first non negative number as min

for(i=1;i<=numfiles;i++){

	if(inputbuffer[i] != -1){

	min = inputbuffer[i];
	break;

	}


}

for(i=1;i<=numfiles;i++){

	if(inputbuffer[i] <= min && inputbuffer[i] != -1){
	min = inputbuffer[i];
	minfile = i;

	}

}

fprintf(*resultfile,"%d\n",min);

return minfile;

}

//***********************************************************
//  This function reads from the input buffer (Sorted) 
//  and writes it in a temp file
//
//***********************************************************


void WriteInFile(int buffer[],FILE** writeFile,FILE** readableFile,long int bufferSize){

long int i;


	for(i = 0;i<bufferSize;i++){

	fwrite(&buffer[i],sizeof(int),1,*writeFile);
	fprintf(*readableFile,"%d\n",buffer[i]);

	}


}

//***********************************************************
//  This function reads from the original file 
//  and writes it into input buffer
//
//***********************************************************

void readIntoArray(FILE** readFile,int buffer[],long long int fileSize){

long int i;

int num;

	for(i = 0 ;i < 100 ;i++){

	fread(&num,sizeof(int),1,*readFile);

	buffer[i] = num;

		if(ftell(*readFile) == fileSize){

		return;

		}

	}


}

void Sort(int arr[],long int n)
{
   long int curr_size; 
   long int left_start; 
 

   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
  
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {

           long int mid = left_start + curr_size - 1;
 
           long int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           merge(arr, left_start, mid, right_end);
       }
   }
}


void merge(int arr[],long int l,long int m,long int r)
{
    long int i, j, k;
    long int n1 = m - l + 1;
    long int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


long int min(long int x,long int y) { return (x<y)? x :y; }


























