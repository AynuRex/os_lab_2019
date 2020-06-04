#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct factorialArgs
{
    int num;
    int mod;
    int cur_thread_num;
    int thread_num;
    int k;
};

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void factorial(void* _arg)
{
    struct factorialArgs* arg = _arg;
    for (int i = arg->cur_thread_num; i <= arg->k; i += arg->thread_num)
    {
        pthread_mutex_lock(&mut);
        arg->num = (arg->num * i) % arg->mod;
        pthread_mutex_unlock(&mut);
    }
}

int main(int argc, char **argv)
{
    int thread_num = -1, mod = -1, k = -1;
    
    static struct option options[] = {
                                    {"k", required_argument, 0, 0},
                                    {"thread_num", required_argument, 0, 0},
									                  {"mod", required_argument, 0, 0},
                                    {"h", no_argument, 0, 0},
								                  	{0, 0, 0, 0}
                                    };

    while (1)
	{
		int option_index = 0;
		int c = getopt_long(argc, argv, "k", options, &option_index);
		
		if(c == -1)
			break;
		
		switch(c)
		{
			case 0:
			{
				switch(option_index)
				{
                    case 0:
                    {
                        k = atoi(optarg);
                        if (k < 0)
                        {
                            printf("K must be a positive number or 0. Now K is %d\n", k);
                        }
                    }
					case 1:
					{
						thread_num = atoi(optarg);
						if (thread_num < 1)
						{
								printf("thread_num must be a positive number. Now thread_num is %d\n", thread_num);
								return -1;
						}
						break;
					}
		
					case 2:
                    {
						mod = atoi(optarg);
						if (mod < 0)
						{
								printf("Mod must be a positive number. Now mod is %d\n", mod);
								return -1;
						}
						break;
                    }
                    case 3:
                    {
                        printf("Use: ./parallelFactorialMod --k [num] --thread_num [num] --mod [mod]\n");
                        return 0;
                    }
				}
				break;
			}
			case '?':
				break;
		
			default:
				printf("getopt returned character code 0%o?\n", c);
		}
	}

    int cur_thread_num = 0;
    pthread_t* thArray = (pthread_t*)malloc(sizeof(pthread_t) * cur_thread_num);
    struct factorialArgs* arg = (struct factorialArgs*)malloc(sizeof(struct factorialArgs));
    arg->num = 1;
    arg->mod = mod;
    arg->thread_num = thread_num;
    arg->k = k;
    for (cur_thread_num = 0; cur_thread_num < thread_num; cur_thread_num++)
    {
        arg->cur_thread_num = cur_thread_num + 1;
        if (pthread_create(thArray + cur_thread_num, NULL, (void*)factorial, (void*)arg) != 0)
        {
                perror("pthread_create");
                exit(1);
        }
    }

    cur_thread_num--;

    for (; cur_thread_num >= 0; cur_thread_num--)
    {
        if (pthread_join(thArray[cur_thread_num], NULL) != 0)
        {
            perror("pthread_join");
            exit(1);
        }
    }

    printf ("Answer: %d", arg->num);
    free(thArray);

    return 0;
}