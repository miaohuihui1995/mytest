#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
	int p, q, r, a, b, x, x1, N, P, i;
	int steps = 0;
	int count_b = 0;
	double p_b;
	double t1, t2;
	double duration;
	float m;

	printf("input parameters(attention: probability is expressed as a fraction like p/q, p - numerator, q - denominator) a, b, x, N, p, q, P: ");
	scanf("%d %d %d %d %d %d %d", &a, &b, &x, &N, &p, &q, &P);
	m = (float)p / q;

	srand(time(0) + rand());

	switch(P)
	{
	case 1 :
		//one thread
		t1 = omp_get_wtime();
		omp_set_num_threads(1);
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
				steps += 1;

				if(x1 == a)
				{
					break;
				}
				else if(x1 == b)
				{
					count_b += 1;
					break;
				}
			}
		}
		t2 = omp_get_wtime();
		duration = (double)(t2 - t1);
		p_b = (float)count_b / N;

		break;

	case 2:
		//two threads
		t1 = omp_get_wtime();
		omp_set_num_threads(2);
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

		break;

	case 4:
		//four threads
		t1 = omp_get_wtime();
		omp_set_num_threads(4);
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

		break;

	case 8:
		//eight threads
		t1 = omp_get_wtime();
		omp_set_num_threads(8);
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

		break;

	case 16:
		//sixteen threads
		t1 = omp_get_wtime();
		omp_set_num_threads(16);
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

		break;

	default:
		printf("Error: only 1, 2, 4, 8, 16 can be entered for P!\n");
	}

	FILE *fp = NULL;

	fp = fopen("/home/miaohuihui/omp/montecarlo/stats.txt", "w+");
	fprintf(fp, "%f %d %fs %d %d %d %d %f %d\n", p_b, steps / N, duration, a, b, x, N, m, P);
	fclose(fp);

	return 0;
}
