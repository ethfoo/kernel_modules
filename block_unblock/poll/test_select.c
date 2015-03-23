#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_LEN 20

int main()
{
	int fd, num;
	fd_set rfds, wfds;
	char buf[BUFFER_LEN];
	memset(buf, 0, BUFFER_LEN);

	fd = open("/dev/poll_select", O_RDWR | O_NONBLOCK);
	if(fd != -1)
	{
		while(1)
		{
			//清除用于读的文件描述符
			FD_ZERO(&rfds);

			//清除用于写的文件描述符
			FD_ZERO(&wfds);

			//将fd加入到文件描述符集rfds
			FD_SET(fd, &rfds);

			//将fd加入到文件描述符集wfds
			FD_SET(fd, &wfds);

			//轮询监视Linux设备的读写状态
			select(fd+1, &rfds, &wfds, NULL, NULL);

			//根据poll函数设置的掩码判断Linux设备文件是否可读
			if(FD_ISSET(fd, &rfds))
			{
				printf("Data can be read!\n");
				read(fd, buf, BUFFER_LEN);
				memset(buf, 0, BUFFER_LEN);
			}

			//根据poll函数设置的掩码判断Linux设备文件是否可写
			if(FD_ISSET(fd, &wfds))
			{
				printf("Data can be written!\n");
			}
			sleep(1);
		}
	}
	else
	{
		printf("cannot open the device\n");
	}
}
