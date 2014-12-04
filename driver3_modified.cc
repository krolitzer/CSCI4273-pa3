#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>

#include <fcntl.h>

#ifdef IPP
#include <ipp.h>
#include <ippdefs.h>
#endif

typedef unsigned long long int UINT64;
using namespace std;

#include "Message_mishra.h"
#include <time.h>

UINT64 startTSC = 0;
UINT64 stopTSC = 0;
UINT64 cycleCnt = 0;

clock_t begin;
clock_t end;
double time_spent;

UINT64 readTSC(void)
{
   unsigned hi, lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


UINT64 cyclesElapsed(UINT64 stopTS, UINT64 startTS)
{
   return (stopTS - startTS);
}

main ( )
{
	UINT64 microsecs=0, clksPerMicro=0, millisecs=0;
    double temp, clkRate;
    
    char *b1 = new char[100];
    for (int i = 0; i < 100; i++) b1[i] = 'a';

    char *h1 = new char[5];
    for (int i = 0; i < 5; i++) h1[i] = 'h';

    char *h2 = new char[4];
    for (int i = 0; i < 4; i++) h2[i] = 'k';

    char *h3 = new char[24];
    for (int i = 0; i < 24; i++) h3[i] = 'm';

	struct timeval start, end;
	long mtime, seconds, useconds;
	
	startTSC = readTSC();
    Message *m = new Message(b1, 100);
    m->msgAddHdr(h1, 5);
    m->msgAddHdr(h2, 4);
    m->msgAddHdr(h3, 24);
    cout << "Message length = " << m->msgLen( ) << endl;
    
    char* buf = new char[140];
    m->msgFlat(buf);
    buf[m->msgLen ( )] = '\n';
    cout << "Message: " << buf << endl;

    Message m2;

    m->msgSplit(m2, 50);
    cout << "Message length of m = " << m->msgLen( ) << endl;
    char* bufx = new char[140];
    m->msgFlat(bufx);
    bufx[m->msgLen ( )] = '\n';
    cout << "Message: " << bufx << endl;


    cout << "Message length of m2 = " << m2.msgLen( ) << endl;
    char* bufy = new char[140];
    m2.msgFlat(bufy);
    bufy[m2.msgLen ( )] = '\n';
    cout << "Message: " << bufy << endl;



    Message *m1 = new Message(buf, 133);
    char *c1 = m1->msgStripHdr(24);
    char *c1b = new char[25];
    memcpy(c1b, c1, 24);
    c1b[24] = '\0';
    cout << "Stripped header: " << c1b << endl;

    char *c2 = m1->msgStripHdr(4);
    char *c2b = new char[5];
    memcpy(c2b, c2, 4);
    c2b[4] = '\0';
    cout << "Stripped header: " << c2b << endl;

    char *c3 = m1->msgStripHdr(5);
    char *c3b = new char[6];
    memcpy(c3b, c3, 5);
    c3b[5] = '\0';
    cout << "Stripped header: " << c3b << endl;

    char* buf1 = new char[140];
    m1->msgFlat(buf1);
    buf[m1->msgLen ( )] = '\n';
    cout << "Message: " << buf1 << endl;

    m1->msgJoin(m2);
    char* bufz = new char[400];
    m1->msgFlat(bufz);
    bufz[m1->msgLen ( )] = '\n';
    cout << "Message: " << bufz << endl;

    m->msgJoin(*m1);
    cout << "Message length of m = " << m->msgLen( ) << endl;
    
    char* bufa = new char[500];
    m->msgFlat(bufa);
    bufa[m->msgLen ( )] = '\n';
    cout << "Message: " << bufa << endl;
	
	stopTSC = readTSC();
    cycleCnt = cyclesElapsed(stopTSC, startTSC);
    clkRate = ((double)cycleCnt)/1000000.0;
    clksPerMicro = (UINT64)clkRate;
    microsecs = cycleCnt/clksPerMicro;
    millisecs = microsecs/1000;

	cout << "elapsed time: " << millisecs << "milliseconds\n" << endl;

}


