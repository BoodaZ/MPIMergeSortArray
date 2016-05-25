//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
//#include <time.h>
#include <mpi.h>

using namespace std;

//Merge 
void merge(int *a, int *b, int l, int m, int r);

//main function for mearge
void mergeSort(int *a, int *b, int l, int r);

int main(int argc, char** argv)
{
	
	//intilize Array : 
	
	int ArraySize=6;
	int *original_array = new int[ArraySize] ;
	


	//start intialize MPI services:
	int Process_rank;
	int ProcessSize;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &Process_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcessSize);


	//Print array 
	if (Process_rank==0)
	{
		cout << "array before sorted:\n ";
		for (int c = 0; c <ArraySize; c++)
		{

			original_array[c] = rand() % ArraySize;
			cout << original_array[c];
				

		}
		cout << "\n";

	}
	// Divide the array
	int SizeForSub = ArraySize / ProcessSize;
	
	//send sub array
	int *sub_array = new int[SizeForSub];
	MPI_Scatter(original_array, SizeForSub, MPI_INT, sub_array, SizeForSub, MPI_INT, 0, MPI_COMM_WORLD);
	
	//show sub array
	for (int i = 0; i < ProcessSize; i++)
	{

		cout << "sub arry: " << Process_rank << "\n";
		for (int c = 0; c < SizeForSub; c++)
		{

			cout << sub_array[c];

		}
		printf("\n");
		break;
	}
	

	//apply merge sort for each process
	int *tmp_array = new int[SizeForSub];
	mergeSort(sub_array, tmp_array, 0, (SizeForSub - 1));
	
	// Gather the sorted subarrays 
	int *sorted =NULL;
	if(Process_rank== 0) 
	{
		
		sorted = new int[ArraySize];
		
	}
	
	MPI_Gather(sub_array, SizeForSub, MPI_INT, sorted, SizeForSub, MPI_INT, 0, MPI_COMM_WORLD);
	
	//call final mearge function
	if(Process_rank == 0) 
	{
		
		int *other_array =new int[ArraySize] ;
		mergeSort(sorted, other_array, 0, (ArraySize - 1));
		
		//show stored array
		cout<<"sorted array:\n";
		for(int c = 0; c <ArraySize; c++)
		{
			
			cout << sorted[c]; 
			
		}
			
	
		cout<<"\n\n\n";
			
		
		free(sorted);
		free(other_array);


	}
	free(original_array);
	free(sub_array);
	free(tmp_array);
	

	// Finalize MPI 
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

}

//merge Function
void merge(int *a, int *b, int l, int m, int r)
{
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	while ((h <= m) && (j <= r))
	{

		if (a[h] <= a[j])
		{
			b[i] = a[h];
			h++;
		}
		else
		{

			b[i] = a[j];
			j++;
		}
		i++;
	}
	if (m < h)
	{

		for (k = j; k <= r; k++)
		{

			b[i] = a[k];
			i++;
		}
	}

	else
	{
		for (k = h; k <= m; k++)
		{
			b[i] = a[k];
			i++;
		}
	}

	for (k = l; k <= r; k++)
	{
		a[k] = b[k];
	}

}


//Merge Sort Function: 
void mergeSort(int *a, int *b, int l, int r)
{

	int m;

	if (l < r) {

		m = (l + r) / 2;

		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);

	}

}
