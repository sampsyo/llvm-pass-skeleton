#include <stdio.h>

void f(char *s) {
  // Parse the format string and translate the snprintf call to a strncpy call,
  // based on the '%s' format verb.
  char buf[1024];
  snprintf(buf, sizeof(buf), "%s", s);
  puts(buf);
}

void g(char *s, char *t, char *u) {
  // Parse the format string and translate the snprintf call to strncat calls,
  // based on the format verbs.
  char buf[1024];
  snprintf(buf, sizeof(buf), "%s + %s = %s", s, t, u);
  puts(buf);
}

int main(int argc, char **argv) {
  f("foo");
  g("two", "three", "five");
  return 0;
}
