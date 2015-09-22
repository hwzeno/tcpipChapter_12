/*********************************
    > File Name: select.c
    > Author: Zeno
    > Mail:340562424@qq.com 
    > Created Time: 2015年09月22日 星期二 16时14分10秒
 ********************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;
	FD_ZERO(&reads);//初始化fd_set变量
	FD_SET(0, &reads);//0 is standard input(console)
//将文件描述符0对应的位设置为1,即要监视标准输入的变化。？
	/*
	 * timeout.tv_sec =5;
	 * timeout.tv_usec = 5000;
	 * */
	while(1)
	{
		temps = reads;//保存初始值.必须得有
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout);//调用select函数
		//如果有控制台输入数据，则返回大于0 的整数如果没有输入数据而引发超时，则返回0.
		if(result == -1)
		{
			puts("select() error!");
			break;
		}
		else if(result == 0)
		{
			
			puts("timeout!");

		}
		else
		{
			//select函数返回值大于0时运行。
			//验证发生变化的文件描述符是否为标准输入。
			//若是，则从标准输入读取数据并向控制台输出。

			if(FD_ISSET(0, &temps))
			{
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);

			}
		}
	}
	return 0;
}
