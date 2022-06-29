#include <stdio.h>
#include <unistd.h>
int N = 100;
void calc_frequency(int freq[N], int arr[N])
{
	for (int i = 0; i < N; i++)
	{
		freq[arr[i]]++;
	}
}
int even_add(int arr[N])
{
	int ret = 0;
	for (int i = 0; i < N; i++)
	{
		if (arr[i] % 2 == 0)
		{
			ret += arr[i];
		}
	}
	return ret;
}
int odd_add(int arr[N])
{
	int ret = 0;
	for (int i = 0; i < N; i++)
	{
		if (arr[i] % 2 != 0)
		{
			ret += arr[i];
		}
	}
	return ret;
}

void sort(int arr[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < i; j++)
		{
			int temp;
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				break;
			}
		}
	}
}

int main()
{
	int pid_1, pid_2, pid_3;
	int arr[] = {2, 1, 5, 6, 9, 12, 15, 22, 3, 11, 2, 9, 8, 7, 12};
	N = sizeof(arr) / sizeof(int);
	int freq[100] = {0};

	pid_1 = fork();

	if (pid_1 != 0)
	{ // parent process;
		printf("%d process calculating frequency\n", getpid());
		calc_frequency(freq, arr);
	}
	else
	{
		pid_2 = fork();
		if (pid_2 != 0)
		{
			printf("%d process calculating evensum\n", getpid());
			even_add(arr);
		}
		else
		{
			printf("%d process calculating oddsum\n", getpid());
			odd_add(arr);

			pid_3 = fork();

			if (pid_3 == 0)
			{
				printf("%d process sorting\n", getpid());
				sort(arr);
			}
		}
	}
}