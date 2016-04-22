#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mystring.h"

int main()
{
  int i;

  String *s1 = make_string();
  print_string(s1);
  /*
  char c = string_charAt(s1, 3);
  printf("%c\n", c);

  String *s2 = make_string(); 

  int x = string_compare(s1, s2);
  printf("%d\n", x);

  String *name = string_concat(s1, s2);
  print_string(name);

  String *sub = make_string("le");
  int y = string_indexOf(s1, sub, 0);
  printf("%d\n", y);

  String *ss = string_substring(s2, 2, 4);
  print_string(ss);

  String *list = make_string("zebra, rhino, hippo, elephant");
  String *delim = make_string(", ");

  String *array[MAX];
  int n = string_split(list, delim, array, n);
  for (i=0; i<n; i++) {
    print_string(array[i]);
  }

  string_sort(array, n);
  for (i=0; i<n; i++) {
    print_string(array[i]);
  }
*/
  return 0;
}

