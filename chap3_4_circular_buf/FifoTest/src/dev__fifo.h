#ifndef _DEV__FIFO_H
#define _DEV__FIFO_H

#define MAX_FIFO_LEN 16

void dev__fifo_init( void );
void dev__fifo_put( int value );
int dev__fifo_get( void );
int dev__fifo_get_available_entries();

#endif // _DEV__FIFO_H
