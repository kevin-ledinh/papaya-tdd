#ifndef _DEV__FIFO_H
#define _DEV__FIFO_H

#define MAX_FIFO_LEN 16

void dev__fifo_init( void );
void dev__fifo_put( int value );

#endif // _DEV__FIFO_H
