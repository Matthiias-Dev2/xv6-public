#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
  int fd;
  char buf[16];

  printf(1, "symlink test start\n");

  fd = open("target.txt", O_CREATE | O_RDWR);
  if(fd < 0){
    printf(1, "FAILED: could not create target.txt\n");
    exit();
  }

  write(fd, "hello", 5);
  close(fd);

  if(symlink("target.txt", "link.txt") < 0){
    printf(1, "FAILED: symlink creation failed\n");
    exit();
  }

  fd = open("link.txt", O_RDONLY);
  if(fd < 0){
    printf(1, "FAILED: open(link.txt) failed\n");
    exit();
  }

  memset(buf, 0, sizeof(buf));
  if(read(fd, buf, 5) != 5){
    printf(1, "FAILED: read through symlink failed\n");
    close(fd);
    exit();
  }
  close(fd);

  if(strcmp(buf, "hello") != 0){
    printf(1, "FAILED: wrong contents: %s\n", buf);
    exit();
  }

  printf(1, "PASS: symlink read works\n");

  if(symlink("b", "a") < 0){
    printf(1, "FAILED: could not create a -> b\n");
    exit();
  }

  if(symlink("a", "b") < 0){
    printf(1, "FAILED: could not create b -> a\n");
    exit();
  }

  fd = open("a", O_RDONLY);
  if(fd >= 0){
    printf(1, "FAILED: cycle was not detected\n");
    close(fd);
    exit();
  }

  printf(1, "PASS: cycle detection works\n");
  printf(1, "all symlink tests passed\n");
  exit();
}