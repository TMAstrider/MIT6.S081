#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

//   printf("p = %s++++\n", p);
  return p;

  
}

void
find(char *path, char* target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

//   printf("path= %s  target=%s\n", path, target);

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    
    // printf("fmtname:%s type:%d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("ls: cannot stat %s\n", buf);
            continue;
        }
        // printf("%s\n", buf);
        if (strcmp(target, fmtname(buf)) == 0) {
            printf("%s\n", buf);
        
        }
        char *dot = ".";
        char *ddot = "..";
        if(strcmp(fmtname(buf), dot) != 0 && strcmp(fmtname(buf), ddot) != 0) {
            find(buf, target);
        }

    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  char target[512];
  strcpy(target , argv[2]);  
  if (argc == 3) {
    
    find(argv[1], target);
  }
  
  
  exit(0);
}
