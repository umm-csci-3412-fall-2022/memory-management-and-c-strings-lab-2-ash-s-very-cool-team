# Changes Made
## `palindrome.c`

There are a number of memory leaks within the `palindrome.c` file. The first change made to mitigate this is adding documentation comments to both functions noting that the return values need to be freed. Next, `char *palindrome(char const *str)` calls `char *str_reverse(char const *str)` but does not free the result. To correct this, simply freeing the result should correct this.

```c
...
  // Free the memory allocated by the call to `str_reverse`
  free(rev);
...
```

## `main.c`

The memory leak in `main.c` is made clearer by the changes made in adding documentation comments. The result is never freed, thus causing a memory leak. The solution here is to store the result and later free it.

```c
...
    const char* result = palindrome(line);
    printf("Is the string <%s> a palindrome? %s\n", line, result);
    free((void*)result);
...
```

## `palindrome_test.cpp`

The memory leaks present in `palindrome_test.cpp` are luckily restricted to the helper `is_palindrome` and `not_palindrome` functions. As such, those are the only functions which need to be changed. In this case, the result from `palindrome` needs to be freed.

```c
...
void is_palindrome(char const *str) {
  const char* result = palindrome(str);
  ASSERT_STREQ(result, "Yes");
  free((void*) result);
}

void not_palindrome(char const *str) {
  const char* result = palindrome(str);
  ASSERT_STREQ(result, "No");
  free((void*) result);
}
...
```

## Other Issues

There are some more architectural issues which I would like to address as well. First, in `char *palindrome(char const *str)` in `palindrome.c`, two strings are compared without using the builtin `strcmp` function. Thus, the while loop can be replaced with

```c
...
  // Compare `str` and `rev`, setting result to true if they are the same string
  result = strcmp(str, rev) == 0;
...
```

The next issue is more far reaching. I would recommend changing `palindrome` to return a statically allocated string since it only returns one of two possible strings. However, this defeats the purpose of the lab, so I will not commit that change, but will nonetheless propose it here.

However, there is another change I would like to make in this file. That is that strings are being populated manually instead of using `strcpy`.

```c
...
  if (result) {
    answer = (char*) calloc(4, sizeof(char));
    strcpy(answer, "Yes\0");
  } else {
    answer = (char*) calloc(3, sizeof(char));
    strcpy(answer, "No\0");
  }
...
```