#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    long n = 10000;

    if (argc > 1) {
        n = strtol(argv[1], NULL, 10);
        if (n < 1) {
            fprintf(stderr, "Uso: %s [N]   (N entero positivo)\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    pid = fork();

    if (pid < 0) {
        perror("Error en fork()");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        for (long i = n; i >= 1; i--) {
            printf("Hijo  (PID %d): %ld\n", getpid(), i);
        }
    }
    else {
        for (long i = 1; i <= n; i++) {
            printf("Padre (PID %d): %ld\n", getpid(), i);
        }
        wait(NULL);
        printf("Padre (PID %d): el hijo (PID %d) ha terminado.\n", getpid(), pid);
    }

    return  EXIT_SUCCESS;
}