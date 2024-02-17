#include "../include/find.h"
// this function finds an occurrence of needle in haystack
// needle must be matched with a whole word in haystack...
static char *strstr_fully_matched(char *haystack, char *needle)
{
  char *rv;
  char padded_needle[strlen(needle) + 3];
  padded_needle[0] = ' ';
  strcpy(padded_needle + 1, needle);
  padded_needle[strlen(needle) + 1] = ' ';
  padded_needle[strlen(needle) + 2] = '\0'; // pad the needle w/ spaces before and after
  if (!strcmp(needle, haystack))
    return haystack; // needle matches the whole haystack
  if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1))
  {
    return haystack; // needle is at the beginning of haystack
  }
  if ((rv = strstr(haystack, padded_needle)) != NULL)
  {
    return rv + 1; // needle is at the middle of haystack.
  }
  padded_needle[strlen(needle) + 1] = '\0'; // remove the last space
  if ((rv = strstr(haystack, padded_needle)) != NULL &&
      rv[strlen(padded_needle)] == '\0')
  {
    return rv + 1; // needle is at the end of haystack.
  }
  return NULL;
}
// lowers the case of each character in its input string
static void to_lower(char *input)
{
  for (int i = 0; i < strlen(input); i++)
    input[i] = tolower(input[i]);
}
// this function finds an occurrence of needle in haystack
// option specify case-sensitivity of search and whether needle should match a whole word
char *strstr_w_option(char *haystack, char *needle, flags option)
{
  if (option & CASE)
  {
    to_lower(haystack = strdup(haystack));
    to_lower(needle = strdup(needle));
    if (option & MATCHED)
      return strstr_fully_matched(haystack, needle);
    else
      return strstr(haystack, needle);
  }
  else if (option & MATCHED)
    return strstr_fully_matched(haystack, needle);
  else
    return strstr(haystack, needle);
}
// subroutine used in qsort
static void swap(void **v, int i, int j)
{
  void *temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
// quick sort on array of strings
void quicksort(char *str[], int left, int right)
{
  int i, last;
  if (left >= right)
    return;
  swap(str, left, left + (right - left) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(str[i], str[left]) < 0)
      swap(str, ++last, i);
  swap(str, left, last);
  quicksort(str, left, last - 1);
  quicksort(str, last + 1, right);
}

void reverse(char *str[])
{
  int length = 0;
  while (str[length] != NULL)
  {
    length++;
  }

  for (int i = 0; i < length / 2; i++)
  {
    swap((void **)str, i, length - 1 - i);
  }
}

char *printPartial(const char *input, const char *pattern, const char *found)
{

  if (!found)
  {
    return strdup(input);
  }

  int inputLen = strlen(input);
  int patternLen = strlen(pattern);
  int patternPos = found - input;
  char *newStr = NULL;

  if (inputLen <= patternLen + 15)
  {
    newStr = strdup(input);
  }
  else
  {
    
    int newStrLen = 0;
    int includeFirstEllipsis = patternPos > 10;
    int includeSecondEllipsis = (inputLen - (patternPos + patternLen)) > 5;


    newStrLen += includeFirstEllipsis ? 13 : patternPos;                         
    newStrLen += patternLen;                                                     
    newStrLen += includeSecondEllipsis ? 8 : inputLen - patternPos - patternLen; 

    newStr = malloc(newStrLen + 1); 
    if (newStr == NULL)
    {
      printf("Memory allocation failed\n");
      return NULL;
    }

    int idx = 0;
    if (includeFirstEllipsis)
    {
      strncpy(newStr, input, 10);
      strcpy(newStr + 10, "...");
      idx = 13;
    }
    else
    {
      strncpy(newStr, input, patternPos);
      idx = patternPos;
    }

    strncpy(newStr + idx, pattern, patternLen);
    idx += patternLen;

    if (includeSecondEllipsis)
    {
      strcpy(newStr + idx, "...");
      idx += 3;
      strncpy(newStr + idx, input + inputLen - 5, 5);
      idx += 5;
    }
    else
    {
      strncpy(newStr + idx, found + patternLen, inputLen - patternPos - patternLen);
      idx += inputLen - patternPos - patternLen;
    }
    newStr[idx] = '\0'; 
  }

  return newStr;
}