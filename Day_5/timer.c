#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define SIG SIGUSR1
#define CLOCKID CLOCK_REALTIME

static void handler(int sig, siginfo_t *si, void *uc) {
	printf("Caught signal %d\n", sig);
}

int main(int argc, char *argv[]) {
	struct sigaction sa;
	struct sigaction sa1;
	struct sigevent sev;
	timer_t timerid;
	sigset_t test;
	int nsleep;
	struct itimerspec its;
	
	printf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1) { //Регистрируем обработчик сигнала
		perror("sigaction");
		return 1;
	}
	
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;
	if (timer_create(CLOCKID, &sev, &timerid) == -1) {
		perror("timer_create");
		return 1;
	}
	
	printf("timer ID is %ld\n", (long) timerid);
	its.it_value.tv_sec = 3;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 1;
	its.it_interval.tv_nsec = 0;
	
	if (timer_settime(timerid, 0, &its, NULL) == -1) {
		perror("timer_settime");
		return 1;
	}
	nsleep = 20;
	sigemptyset(&test);
	sigaddset(&test, SIG);
	sleep(5);
	if (sigprocmask(SIG_SETMASK, &test, NULL) == -1) {
		perror("sigprocmask");
		return 1;
	}
	sleep(10);
	printf("unblocking\n");
	if (sigprocmask(SIG_UNBLOCK, &test, NULL) == -1) {
		perror("sigprocmask");
		return 1;
	}
	//nsleep = sleep(30);
	//sigemptyset(&sa.sa_mask)
	
	/*while (nsleep != 0) {
		nsleep = sleep(nsleep);
		
		printf("sleep return %d\n", nsleep);
	}*/
				
//	printf("Woke up\n");
	while(1);
	return 0;
}
