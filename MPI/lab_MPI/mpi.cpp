#include <stdio.h>
#include <time.h>
#include "mpi.h"


int* get_interval(int, int, int*);
inline void print_palin_range(int, int);

int main(int argc, char** argv)
{
	int thread, thread_size;
	int* thread_range, interval[] = { 1, 10000 };
	double cpu_time_start, cpu_time_fini;

	MPI_Status status;

	MPI_Init(&argc, &argv);

	// Отримуємо номер конкретного процесу на якому запущена програма
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);

	// Отримуємо кількість запущених процесів
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size);

	if (thread == 0)
	{
		// Відправляємо кожному процесу інтервал
		for (int to_thread = 1; to_thread < thread_size; to_thread++)
			MPI_Send(&interval, 2, MPI_INT, to_thread, 0, MPI_COMM_WORLD);

		cpu_time_start = MPI_Wtime();
	}
	// Якщо процес не перший - чекамо дані
	else
		MPI_Recv(&interval, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	thread_range = get_interval(thread, thread_size, interval);

	print_palin_range(thread_range[0], thread_range[1]);

	if (thread == 0)
	{
		cpu_time_fini = MPI_Wtime();
		printf("CPU Time: %lf ms\n", (cpu_time_fini - cpu_time_start) * 1000);
	}

	MPI_Finalize();
	return 0;
}

int* get_interval(int proc, int size, int* interval)
{
	int* range = new int[2];
	int interval_size = (interval[1] - interval[0]) / size;

	range[0] = interval[0] + interval_size * proc;
	range[1] = interval[0] + interval_size * (proc + 1);
	range[1] = range[1] == interval[1] - 1 ? interval[1] : range[1];
	return range;
}

inline void print_palin_range(int ibeg, int iend)
{
	for (int i = ibeg; i <= iend; i++)
	{
		int digit, rev = 0, num = i;
		do
		{
			digit = num % 10;
			rev = (rev * 10) + digit;
			num = num / 10;
		} while (num != 0);
		if (rev == i) printf("Palindrom value ---> %d\n", i);

	}
}
