#include<stdio.h>
#include<signal.h>
#include<inttypes.h>
#include<unistd.h>
#include<stdlib.h>
#include<immintrin.h>
#include<sys/time.h>
#include<fcntl.h>
#include<stdbool.h>
#include<time.h>

void alrm_handler(int j, siginfo_t *m, void *o)
{
    sleep(1);

    uint64_t z=__rdtsc();

    z/=2e9;
    z+=1637790420;

    time_t x=z;
    struct tm* y = localtime(&x);

    char* s=asctime(y);

    sleep(2);

    printf("%s", s);

    uint64_t i=__rdtsc();

    printf("Random number from ST: %llu\n", i);

    union sigval v_st;

    v_st.sival_ptr=(void(*)(int))i;

    if(sigqueue(m->si_value.sival_int, 15, v_st)!=0)
    {
        printf("sigqueue failed for ST\n");

        return;
    }

    kill(m->si_value.sival_int, 15);
}

int main(int argc, char* argv[])
{
    int pid_st=atoi(argv[0]);

    struct sigaction action_alrm;
    sigemptyset(&action_alrm.sa_mask);
    action_alrm.sa_flags=SA_SIGINFO;
    action_alrm.sa_sigaction=&alrm_handler;

    union sigval value;

    value.sival_int = pid_st;

    struct itimerval t;
    t.it_value.tv_sec=1;
    t.it_value.tv_usec=1000000;
    t.it_interval=t.it_value;
    setitimer(ITIMER_REAL, &t, NULL);

    while(true)
    {
        if(sigaction(SIGALRM, &action_alrm, 0)==-1)
        {
            perror("sigaction failed for SR\n");

            return 6;
        }

        sigqueue(getpid(), SIGALRM, value);
    }

    return 3;
}