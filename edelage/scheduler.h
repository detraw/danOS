#ifndef SCHEDULER_H_
#define SCHEDULER_H_

volatile unsigned int system_ticks;

void init_scheduler(void);
int ms_to_ticks(int ms);
void schedule(void);

#endif
