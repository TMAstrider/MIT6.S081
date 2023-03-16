#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include "kernel/fs.h"

void action(char *filename, char **args) {
    if (fork() == 0) {
      for(int i=0;i<3;i++) {
		printf("argv[%d]:  %s\n", i, args[i]);
	}
      exec(filename, args);

    } else {
      wait(0);
    }
    return;
}


int
main(int argc, char *argv[])
{

  sleep(10);
  char buf[1024];
  char *cursor = buf, *begin = buf;
  char *argbuf[64];
  char **args = argbuf;



  // for(int i=1;i<argc;i++) {
	// 	printf("argv[%d]: %s\n", i, argv[i]);
	// }


  for(int i=1;i<argc;++i) {
		*args = argv[i];
		args++;
	}
    char **add_args = args;


  while (read(0, cursor, 1) != 0) {   // 0 stands for reading from stdin
    if ((*cursor == ' ') || (*cursor == '\n')) {
        *cursor = 0;
        *add_args = begin;
        add_args++;
        // int j = 2;
        // while (j--) {
        //   printf("argument: %s---> args%d\n", args[j], j);
        // }
        printf("argument: %s\n", begin);
        begin = cursor + 1;

        


        if ((*cursor = '\n')) {
            *add_args = 0;
            action(argv[1], argbuf);
            add_args = args;
        }
    }
    cursor++;
  }
  exit(0);
}
