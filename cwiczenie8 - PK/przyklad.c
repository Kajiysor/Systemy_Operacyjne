//---------------------------------------------------------------------------------
// Producent / konsument  proces wysylajacy komunikaty do kolejki
// Odbiera program mq_rcv
// Kompilacja:   gcc mq_snd.c -o mq_snd -lrt
// Uruchomienie: ./mq_snd numer
// Gdy zamontujemy koleki komunikatow w kat /dev/mqueue to mozna nimi manipulowaÄ‡
// uzywajÄ…c poleceĹ„ ls,...
// mkdir /dev/mqueue
// mount -t mqueue none /dev/mqueue
// ----------------------------------------------------------------------------------
#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#define  SIZE     80
#define  MQ_NAME "/Kolejka"
#define  MQ_NAME2 "/Kolejka2"
 struct {
      int  nr;
      int pocz;
      int kon;
      int ile;
  } msg;

struct {
      int  sum;
  } suma;

 main(int argc, char *argv[]) {
   mq_unlink(MQ_NAME);
   mq_unlink(MQ_NAME2);
   int res, res2, poczatek, koniec, przedzialy;
   int start, stop, i;
   unsigned int prior;
   mqd_t  mq;
   mqd_t  mq2;
   struct mq_attr attr;
   struct mq_attr attr2;
   prior = 10;
   //if(argc < 2) { printf("Uzycie: mq_send numer\n"); exit(0); }
   //numer = atoi(argv[1]);


   poczatek = atoi(argv[1]);
   koniec = atoi(argv[2]);
   przedzialy = atoi(argv[3]);

   printf("Kolejka: %s\n", MQ_NAME);
   // Utworzenie kolejki komunikatow ----------------
   attr.mq_msgsize = sizeof(msg);
   attr.mq_maxmsg = 1;
   attr.mq_flags = 0;

   attr2.mq_msgsize = sizeof(suma);
   attr2.mq_maxmsg = 1;
   attr2.mq_flags = 0;

   mq=mq_open(MQ_NAME , O_RDWR | O_CREAT , 0660, &attr );
   mq2=mq_open(MQ_NAME2 , O_RDWR | O_CREAT , 0660, &attr2 );

   if( mq == -1 ) {  perror("Kolejka "); exit(0);  }
   printf("Kolejka: %s otwarta, mq: %d\n", MQ_NAME,mq);

   for(i=0; i < przedzialy ;i++) {
     mq_getattr(mq,&attr);
     printf("W kolejce %ld zadan\n",attr.mq_curmsgs);

     if(i == 0)
     {
			start = 1;
			stop = przedzialy;
     }
     else
     {
			start+=przedzialy;
			stop+=przedzialy;
     }

     msg.nr = i;
     msg.pocz = start;
     msg.kon = stop;
     msg.ile = 0;

     //sprintf(msg.nr,"Proces %d komunikat %d",num,i);
     //msg.typ = num;
     res = mq_send(mq,(char *)&msg,sizeof(msg),prior);
     if (res == -1 ) { perror("Blad zapisu do mq"); continue; }
     printf("Wysylanie. Zadanie %d (przedzial %d %d) wyslane\n",i, start, stop);
    mq_getattr(mq2,&attr2);
     res2 = mq_receive(mq2,(char*)&suma,sizeof(suma),&prior);
     if (res2 == -1 )
    {
        perror("Blad odczytu");
        break;
    }

     sleep(1);
  }

  printf("Suma %d: \n", suma.sum);
  mq_close(mq);
  //mq_unlink(MQ_NAME);
}