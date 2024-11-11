#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N	8

struct targs {
	int id;
	int var;
};

int shared;

char threads[8][16] = { "Threads:", "because", "who", "doesn’t", "love", "simultaneous", "chaos", "management?" };

void *routine(void *args)
{
	int count;
	struct targs *targs = (struct targs *)args;

	printf("Thread %d && var = %d\n", targs->id, targs->var);

    // ++shared;
    // printf("shared var from thread %d: %d\n\n", targs->id, shared);

	// while(1)
	// 	count++;

    return NULL;
	// return threads[targs->id];
}

int main(void)
{

	pthread_t threads[N];
	struct targs thread_args[N];
	int i, rc;

	for (i = 0; i < N; i++) {
		thread_args[i].id = i;
		thread_args[i].var = i * i;
		rc = pthread_create(&threads[i], NULL, routine, &thread_args[i]);
		if (rc != 0) {
			perror("Create");
			exit(1);
		}
	}

	for (i = 0; i < N; i++) {
        char *ret = NULL;

		// rc = pthread_join(threads[i], (void **)&ret);
		rc = pthread_join(threads[i], NULL);

        if (ret != NULL) {
            printf("%s\n", ret);
        }

		if (rc != 0) {
			perror("Join");
			exit(1);
		}
	}

	return 0;
}
