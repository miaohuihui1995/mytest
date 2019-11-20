#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
	int r, a, b, x, x1, N, P, i;
	float p_right;
	int steps = 0;
	int count_b = 0;
	int count_a = 0;
	double p_b;
	double t1, t2;
	double duration;

	printf("input parameters a, b, x, N, p_right(decimal form), P: ");
	scanf("%d %d %d %d %f %d", &a, &b, &x, &N, &p_right, &P);

	//Convert decimal(p_right) to fraction to get numerator(p) and denominator(q)
	double p_f = p_right;
	int q = 1;

	while(p_f - (float)(int)p_f > 1e-6)
	{
		p_f *= 10;
		q *= 10;
	}
	int p = (int) p_f;

	int max;
	int min;
	if(p > q)
	{
		max = p;
		min = q;
	}
	else
	{
		max = q;
		min = p;
	}
	int hcf = max % min;
	while(hcf)
	{
		max = min;
		min = hcf;
		hcf = max % min;
	}
	p /= min;
	q /= min;

	//Realization with Monte Carlo
	srand(time(0) + rand());

	t1 = omp_get_wtime();
	omp_set_num_threads(P);
	#pragma omp parallel for
	for(i = 0; i < N; i++)
	{
		x1 = x;
		for( ; ; )
   		{
      			r = rand() % q;
			if(r < p)
			{
				x1 += 1;
			}
			else
			{
				x1 -= 1;
			}
			#pragma omp atomic
			steps += 1;

			if(x1 == a)
			{
				#pragma omp atomic
				count_a += 1;
				break;
			}
			else if(x1 == b)
			{
				#pragma omp atomic
				count_b += 1;
				break;
			}
		}
	}
	#pragma omp barrier
	t2 = omp_get_wtime();
	duration = (double)(t2 - t1);
	p_b = (float)count_b / N;
	printf("%f\n", (float)count_a / N);

	FILE *fp = NULL;

	fp = fopen("/home/miaohuihui/omp/montecarlo/stats.txt", "w+");
	fprintf(fp, "%f %d %fs %d %d %d %d %f %d\n", p_b, steps / N, duration, a, b, x, N, p_right, P);
	fclose(fp);

	return 0;
}
