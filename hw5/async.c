#include <aio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


ssize_t read_wrap(int fd, void* buf, size_t count){

	struct aiocb* my_aiocb = malloc(sizeof(struct aiocb));
	memset(my_aiocb, 0, sizeof(struct aiocb));

	// set up aiocb vars
	my_aiocb->aio_fildes = fd;
	if(my_aiocb->aio_fildes == -1)
		return -1;
	else if(my_aiocb->aio_fildes == 0)
		my_aiocb->aio_offset = 0;
	else 
		my_aiocb->aio_offset = lseek(fd, 0, SEEK_CUR);

	my_aiocb->aio_buf = buf;
	my_aiocb->aio_nbytes = count;
	my_aiocb->aio_sigevent.sigev_notify = SIGEV_NONE;

	// start to read 
	int read_return = aio_read(my_aiocb);

	while(aio_error(my_aiocb) == EINPROGRESS){
		
		yield();

	}

	int value_return = aio_return(my_aiocb);

	if(value_return >= 0)
		my_aiocb->aio_offset = lseek(fd, my_aiocb->aio_offset + value_return
			, SEEK_SET);

	return value_return;
}
