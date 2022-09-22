# Disemvowel
## Writing `disemvowel`

After looking over the project files, I notice that I will introduce a memory leak if I attempt to return a string allocated on the heap from `disemvowel` for the tests. As such, the first change I will make is to free the returned data in the tests and allocate the memory. All of these changes are similar to the first in `disemvowel_test.cpp`, so I will just show the first:

```c
...
TEST(Disemvowel, HandleEmptyString) {
  const char* result = disemvowel((char*) "");
  ASSERT_STREQ("", result);
  free((void*)result);
}
...
```

Meanwhile, over in `disemvowel.c`, I need to allocate the string.

```c
...
char *disemvowel(char *str) {
  // Allocate space for the result with the same length as the input string plus one for the null terminator
  char* result = calloc(strlen(str) + 1, 1);

  // Populate the result string with an empty string
  strcpy(result, "");

  return result;
}
...
```

At this point, there is a fun problem where there are memory leaks caused by the tests because they fail.

However, to make sure this works, over in `main.c` we have to do the same thing and deallocate the memory returned by `disemvowel`.

```c
...
  while (getline(&line, &size, stdin) > 0) {
    const char* result = disemvowel(line);
    printf("%s\n", disemvowel(line));
    free((void*) result);
  }
...
```

Nest, I need to add the logic to `disemvowel`. To do this, I started with a loop to go over each character in the string, copying it to the output, which is just `strcpy`:

```c
...
  // Index into the result string
  unsigned int i = 0;

  // Iterate over each character of the input string
  do {
      result[i++] = *str;
  }
  while (*(str++));
...
```

Next, is just adding the logic to not step to the next character if the current character is a vowel. I had the though to convert the character to lowercase by masking off bits, however decided that is a bit too obtuse, even if commented. As such, I use a switch statement.

```c
...
  // Iterate over each character of the input string
  do {
    // If it is a vowel, go to the next character
    switch (*str) {
      case 'a': case 'A':
      case 'e': case 'E':
      case 'i': case 'I':
      case 'o': case 'O':
      case 'u': case 'U':
        break;
      // Otherwise, copy the character to the output
      default:
        result[i++] = *str;
        break;
    }
  }
  while (*(str++));
...
```

At this point, a manual test reveals it is working, valgrind on that manual test shows there aren't any memory leaks, and valgrind on the automated tests works.

Some final thoughts, to note that the string passed to `disemvowel` is not to be changed, and thus the signature should be `char *disemvowel(const char *str)` to reflect this.