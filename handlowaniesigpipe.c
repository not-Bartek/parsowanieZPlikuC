#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Funkcja, która wykona się, gdy wystąpi SIGPIPE
void my_handler(int signum) {
    // Uwaga: wewnątrz handlera powinno się używać tylko funkcji "async-signal-safe"
    // printf technicznie nie jest bezpieczny, ale w prostych przykładach wybacza błędy
    const char msg[] = "\n>>> Otrzymałem SIGPIPE! Przeciwnik zamknął rurę! <<<\n";
    write(STDOUT_FILENO, msg, sizeof(msg)-1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = my_handler; // Podpinamy naszą funkcję
    sigemptyset(&sa.sa_mask);   // Nie blokujemy innych sygnałów
    sa.sa_flags = 0;

    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        perror("Błąd sigaction");
        return 1;
    }

    int pipefd[2];
    pipe(pipefd);
    close(pipefd[0]); // Zamykamy czytelnika

    printf("Próbuję pisać do zamkniętej rury...\n");
    write(pipefd[1], "boom", 4);

    printf("Program kontynuuje pracę po wykonaniu handlera.\n");

    return 0;
}