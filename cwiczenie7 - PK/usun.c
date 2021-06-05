#include "semafory.h"
#include "dzielona.h"

#define SEMAFOR_PRODUCENT "/sem_producent"
#define SEMAFOR_KONSUMENT "/sem_konsument"
#define NAZWA_PD "/prod_kons_pd"

int main () {

    usun_semafor (SEMAFOR_PRODUCENT);
    usun_semafor (SEMAFOR_KONSUMENT);
    usun_PD (NAZWA_PD);

    return 0;

}