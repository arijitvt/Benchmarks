#ifndef RLOCAL_H
#define RLOCAL_H

#include "../include/runtime.h"
#include "../include/tls.h"

void mem_init (void);

void rcu_thread_init (int thread_id);
void lwt_thread_init (int thread_id);

#endif//RLOCAL_H 
