#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "kolejki.h"

/*

    • Na początku niech serwer i klient wypisują na ekranie nazwę, deskryptor i atrybuty utworzonej kolejki.
    • Serwer niech wypisuje na ekranie otrzymany komunikat oraz wynik wykonanego działania, a klient wynik otrzymany od serwera - sprawdzić, czy oba 
        wyniki się zgadzają!

*/

void wyjscie(void)
{
    kolejka_usun(KOLEJKA_NAZWA);
}

void sygnal_wyjscie(int signal)
{
    printf("\nSygnał przerwania, usuwanie kolejki\n");
    exit(EXIT_SUCCESS);
}

int main()
{

    int PID_klienta;
    char string[DLUGOSC_KOMUNIKATU];
    int liczba1;
    int liczba2;
    char operator;
    int wynik;
    char wynik_s[DLUGOSC_KOMUNIKATU];
    mqd_t kolejka_desk;
    mqd_t odpowiedz;

    const double max_dlugosc_czekania = 4.0;

    kolejka_desk = kolejka_utworz(KOLEJKA_NAZWA, O_RDONLY);
    printf("Utworzono kolejkę \"%s\" o deskryptorze %d\n", KOLEJKA_NAZWA, kolejka_desk);

    if (atexit(wyjscie) != 0)
    {
        perror("atexit error");
        _exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sygnal_wyjscie) == SIG_ERR)
    {
        perror("Błąd signal");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    while (1)
    {

        // czytaj komunikat z kolejki
        kolejka_odbierz(kolejka_desk, string, NULL);

        sscanf(string, "[%d] %d%c%d", &PID_klienta, &liczba1, &operator, & liczba2);

        printf("Odebrano zapytanie od [%d] - działanie %d %c %d\n", PID_klienta, liczba1, operator, liczba2);

        // wykonaj obliczenie

        if (operator== '+')
        {
            wynik = liczba1 + liczba2;
            sprintf(wynik_s, "%d", wynik);
        }
        else if (operator== '-')
        {
            wynik = liczba1 - liczba2;
            sprintf(wynik_s, "%d", wynik);
        }
        else if (operator== '*')
        {
            wynik = liczba1 * liczba2;
            sprintf(wynik_s, "%d", wynik);
        }
        else if (operator== '/')
        {
            wynik = liczba1 / liczba2;
            sprintf(wynik_s, "%d", wynik);
        }
        else
        {
            sprintf(wynik_s, "Błąd: nieznany operator");
        }

        // czekaj losową ilość czasu
        sleep((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100);

        // odtwórz kolejkę do nadania odpowiedzi
        sprintf(string, "/%d", PID_klienta);
        odpowiedz = kolejka_otworz(string, O_WRONLY);

        // odpowiedz
        printf("Wysyłanie odpowiedzi %s do procesu %d\n", wynik_s, PID_klienta);
        kolejka_wyslij(odpowiedz, wynik_s, 1);
        kolejka_zamknij(odpowiedz);
    }

    kolejka_usun(KOLEJKA_NAZWA);

    printf("\n\nSerwer: koniec procesu\n");

    return 0;
}