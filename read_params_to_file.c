#include <stdio.h>
#include <string.h>

#define PAMIEC_PROGRAMU 500
int main (int argc, char* argv[])
{
  printf("Program wypisuje dane wejściowe umieszczając każde słowo\n");
  printf("w osobnym wierszu pliku podanego w argumencie wywołania programu.\n");

  if (argc < 2)
    {
      printf("Nie podano pliku z danymi!!\n");
      printf("Prosze podaj plik z danymi wejsciowymi jako pierwszy parametr programu\n");
      printf("Pierwszy parametr to rowniez nazwa pliku gdzie wypisane dane wyjsciowe\n");

      return -1;
    }

  char FileString[PAMIEC_PROGRAMU] = { 0 };
  char  currentChar = 0;
  char *charPointer = FileString;
  int counter = 0;
  FILE *f=fopen(argv[1], "r+");

  char error[256] = { 0 };
  if (f == NULL)
    {
      /* File descriptor returned NULL so fopen failed */
      printf("Unable to open file %s\n", argv[1]);
      perror(error); //prosty komunikat o bledzie
      printf("Error: %s\n", error);
      return -1;
    }
  printf("Successfully opened file %s\n", argv[1]);


  while (!feof(f)) {
    if ((currentChar = (char)getc(f)) == EOF) // read char into int variable
      {
	break;
      }

    if (!strncmp(&currentChar, " ", 1)) {
      strncpy(charPointer++, "\n", 1);
    }
    else {
      strncpy(charPointer++, &currentChar, 1);
    }
    counter++;
    /* This fragment protects from buffer overruns */
    if (counter >= PAMIEC_PROGRAMU)
      {
	break;
      }
  }
  /* Now we have to write buffer to a file */
  for (int i = 0; i < counter; i++) {

    putc(FileString[i], f);
  }

  fclose(f);

  printf("Successfully reached the end of the program\n");
  return 0;
}
