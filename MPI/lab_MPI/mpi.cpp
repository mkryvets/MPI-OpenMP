#include <stdio.h>
#include <time.h>
#include "mpi.h"
#include <vector>


int* get_interval(int, int, int*);
inline void print_palin_range(int, int);
std::vector< int > palindrom_vector;


int main(int argc, char** argv)
{
	int thread, thread_size;
	int* thread_range, interval[] = { 1, 1000 };
	double cpu_time_start, cpu_time_fin, res_time;

	MPI_Status status;

	// init the MPI execution environment
	MPI_Init(&argc, &argv);
	// get the rank (num) of running process 
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);
	// get the amount of processes
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size);

	if (thread == 0) {
		// send interval for each process
		for (int thread_num = 1; thread_num < thread_size; thread_num++)
			// send buffer, num of elements in send buffer, type of that elements,
			// process rank, message tag, communicator
			MPI_Send(&interval, 2, MPI_INT, thread_num, 0, MPI_COMM_WORLD);

		//cpu_time_start = MPI_Wtime();
	}
	// otherwise blocking receive for a message
	else
		// address of receive buffer, max num of elements in receive buffer, type, rank of source,
		// message tag, communicator
		MPI_Recv(&interval, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	// get the range for current thread
	thread_range = get_interval(thread, thread_size, interval);

	cpu_time_start = MPI_Wtime();

	// get all palindroms from this range
	print_palin_range(thread_range[0], thread_range[1]);

	// fin of processes
	cpu_time_fin = MPI_Wtime();
	// print results
	res_time = cpu_time_fin - cpu_time_start;
	printf("CPU Time: %lf ms\n", res_time * 1000);

	MPI_Finalize();
	return 0;
}

// gets the num of process, amount of all process, arr with interval
// returns range for certain process
int* get_interval(int proc, int size, int* interval)
{
	int* range = new int[2];
	int interval_size = (interval[1] - interval[0]) / size;

	// get the beginning and the end of range for proc
	range[0] = interval[0] + interval_size * proc;
	range[1] = interval[0] + interval_size * (proc + 1);
	// in case of the last process
	range[1] = range[1] == interval[1] - 1 ? interval[1] : range[1];
	return range;
}

inline void print_palin_range(int ibeg, int iend)
{
	for (int i = ibeg; i <= iend; i++)
	{
		int digit, rev = 0, num = i;
		// get the rev - reversed of i
		do
		{
			digit = num % 10;
			rev = (rev * 10) + digit;
			num = num / 10;
		} while (num != 0);
		// if reversed is base i -> palindrom

		if (rev == i) printf("Palindrom - %d\n", i);
		// if (rev == i) palindrom_vector.push_back(i);
	}
}