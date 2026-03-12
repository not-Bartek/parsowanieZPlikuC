#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf;
    char msg[] = "Wiadomosc przez rure!";

    // 1. Tworzymy rurę przed forkiem!
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    cpid = fork(); // 2. Tworzymy proces potomny

    if (cpid == -1) {
        perror("fork");
        return 1;
    }

    if (cpid == 0) {    /* --- KOD DZIECKA --- */
        close(pipefd[1]); // Dziecko tylko czyta, więc zamyka koniec do pisania

        printf("Dziecko odbiera: ");
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        
        close(pipefd[0]);
        _exit(0); // Dziecko kończy pracę

    } else {            /* --- KOD RODZICA --- */
        close(pipefd[0]); // Rodzic tylko pisze, więc zamyka koniec do czytania

        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]); // Zamykamy, żeby dziecko dostało EOF (koniec danych)

        // 3. Waitowanie na końcu
        printf("Rodzic: Czekam na dziecko (PID: %d)...\n", cpid);
        wait(NULL); 
        printf("Rodzic: Dziecko zakonczylo, ja tez koncze.\n");
    }

    return 0;
}