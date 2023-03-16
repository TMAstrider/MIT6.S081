#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pP2C[2];
    int pC2P[2];    // Double end File Descriptor p[0] for 0 'read', and p[1] for 1 'write'
    
    char buf[1];
    pipe(pP2C);

    
    
    pipe(pC2P);
    int pid = fork();   // If we call fork after creating a pipe, 
                        // then the parent and child can communicate via the pipe.
    if(pid == 0) {  // child process
        // close(pC2P[0]);
        // close(pP2C[1]);
        read(pP2C[0], buf, 1);
        printf("%d: received ping\n", getpid());
        // close(pC2P[1]);
        write(pC2P[1], "!", 1);
        // close(pC2P[1]);
        // close(pP2C[0]);
    } else {        // parent process
    //     close(pC2P[1]);
    //     close(pP2C[0]);

        write(pP2C[1], "!", 1);
        read(pC2P[0], buf, 1);
        // close(pP2C[0]);
        printf("%d: received pong\n", getpid());
        // close(pC2P[0]);
        // close(pP2C[1]);
        wait(0);
    }
    exit(0);
    // char buf;
    // int pp2c[2], pc2p[2];
	// pipe(pp2c); // 创建用于 父进程 -> 子进程 的管道
	// pipe(pc2p); // 创建用于 子进程 -> 父进程 的管道
	
	// if(fork() == 0) { // parent process
	// 	read(pp2c[0], &buf, 1);
    //     printf("%d: received ping\n", getpid());
    //     write(pc2p[1], "!", 1);


    //     // char buf;
	// 	// read(pp2c[0], &buf, 1); // 3. 子进程读取管道，收到父进程发送的字节数据
	// 	// printf("%d: received ping\n", getpid());
	// 	// write(pc2p[1], &buf, 1); // 4. 子进程通过 子->父 管道，将字节送回父进程
	// } else { // child process
    //     write(pp2c[1], "!", 1);
    //     read(pc2p[0], &buf, 1);
    //     printf("%d: recieved pong\n", getpid());

	// 	// write(pp2c[1], "!", 1); // 1. 父进程首先向发出该字节
	// 	// // char buf;
	// 	// read(pc2p[0], &buf, 1); // 2. 父进程发送完成后，开始等待子进程的回复
	// 	// printf("%d: received pong\n", getpid()); // 5. 子进程收到数据，read 返回，输出 pong
	// 	// wait(0);
	// }
	// exit(0);
}