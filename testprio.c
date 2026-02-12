#include "types.h"
#include "stat.h"
#include "user.h"

static void
expect_ok(int rc, char *msg)
{
  if(rc < 0){
    printf(1, "FAIL: %s\n", msg);
    exit();
  }
  printf(1, "OK: %s\n", msg);
}

static void
expect_fail(int rc, char *msg)
{
  if(rc == 0){
    printf(1, "FAIL (expected -1): %s\n", msg);
    exit();
  }
  printf(1, "OK (failed as expected): %s\n", msg);
}

int
main(void)
{
  int me = getpid();
  int rc;

  printf(1, "testprio: my pid = %d\n", me);

  // valid priorities
  rc = setpriority(me, 1);
  expect_ok(rc, "setpriority(self, 1)");

  rc = setpriority(me, 0);
  expect_ok(rc, "setpriority(self, 0)");

  rc = setpriority(me, 2);
  expect_ok(rc, "setpriority(self, 2)");

  // invalid priorities
  rc = setpriority(me, -1);
  expect_fail(rc, "setpriority(self, -1)");

  rc = setpriority(me, 3);
  expect_fail(rc, "setpriority(self, 3)");

  // invalid pid
  rc = setpriority(99999, 1);
  expect_fail(rc, "setpriority(99999, 1)");

  printf(1, "testprio: done\n");
  exit();
}
