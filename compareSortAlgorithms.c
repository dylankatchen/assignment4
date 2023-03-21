#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[],int l,int mid, int r)
{
	int lsiz=mid+1-l;
	int rsiz=r-mid;
	extraMemoryAllocated+=sizeof(int)*(lsiz);
	extraMemoryAllocated+=sizeof(int)*(rsiz);

	int* L=(int*)malloc(sizeof(int)*(lsiz));
	int* R=(int*)malloc(sizeof(int)*(rsiz));
	
	for(int i=0;i<lsiz;i++)
	{
		L[i]=pData[l+i];
	}
	for(int j=0;j<rsiz;j++)
	{
		R[j]=pData[j+mid+1];
	}
	int i=0;
	int j=0;
	int k=l;
	while(i<lsiz&&j<rsiz)
	{
		if(L[i]<=R[j])
		{
			pData[k]=L[i];
			i++;
		}
		else
		{
			pData[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<lsiz)
	{
		pData[k]=L[i];
		i++;
		k++;
	}
	while(j<rsiz)
	{
		pData[k]=R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}
void mergeSort(int pData[], int l, int r)
{
	
	if(l<r)
	{
		int mid= (l+r)/2;
		mergeSort(pData,l,mid);
		mergeSort(pData,mid+1,r);
		merge(pData,l,mid,r);
	}
	
}


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	
    int i,j,test;
    for (i = 1; i < n; i++)
    {
        test = pData[i];
        j = i - 1;
        while (j >= 0 && pData[j] > test)
        {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = test;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated


void bubbleSort(int* pData, int n)
{
	int temp;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j<n-i-1; j++)
		{
			if(pData[j]>pData[j+1])
			{
				temp=pData[j];
				pData[j]=pData[j+1];
				pData[j+1]=temp;
			}
		}
		
	}
	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int temp;
	for(int i=0;i<n-1;i++)
	{
		int min=i;
		for(int j=i+1;j<n;j++)
		{
			if(pData[j]<pData[min])
			{
				min=j;
			}
		}
		if(min!=i)
		{
			temp=pData[min];
			pData[min]=pData[i];
			pData[i]=temp;
		}
	}
}


// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
		FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		 for (int i = 0; i < dataSz; i++)
        {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }
        fclose(inFile);
		
		
	 
	}
	return dataSz;

}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
    
		if (dataSz <= 0)
			continue;

		pDataCopy = (int *)malloc(sizeof(int)*dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

        printArray(pDataSrc,dataSz);

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}

}

