#include <stdio.h>
#include <string.h> // to work with strings
#include <stdlib.h> // for rand()
#include <time.h> // for time()
#include <stdlib.h>
#include <unistd.h>

void play_track(char * track) {
  // Play the track using afplay on macOS or mpg123 on Linux
  #ifdef __APPLE__
  char command[128];
  sprintf(command, "afplay %s", track);
  system(command);
  #else
  char command[128];
  sprintf(command, "mpg123 %s", track);
  system(command);
  #endif
}

// Reference: https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
// Used for ASCII part of a Hangman game
const char * hangmanAscii[] = {
  "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
  "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
  "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
  "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
  "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
  "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
  "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
};

const char * array_of_words[6] = {
  "depression",
  "stress",
  "schizophrenia",
  "paranoia",
  "bipolar",
};

int main(void) {

  // Seed the random number generator
  srand(time(NULL));

  // Pick a random number between 0 and 6 (the number of elements in the array)
  int index = rand() % 5;

  printf("\nGuess the word get reward!\n");

  // Continuously ask for user's input while condition is meet
  char guess[1];

  int len = strlen(array_of_words[index]);
  const char * word = array_of_words[index];
  char letters[len + 1];
  memset(letters, '\0', len + 1);
  int count = 0;
  int lives = 6;

  for (int i = 0; i < len; i++) {
    printf("_ ");
  }
  printf("\n");

  while (lives > 0) {
    int wordComplete = 1;

    // read a single character into guess
    scanf(" %c", guess);
    
    // Check if the character is present in the word
    if (strchr(word, * guess) != NULL) {
      if (strchr(letters, * guess) == NULL) {
        letters[count] = * guess;
        count++;
      }
      printf("\n");
      for (int i = 0; i < len; i++) {
        if (strchr(letters, word[i])) {
          printf("%c", word[i]);
        } else {
          printf(" _ ");
          wordComplete++;
        }
      }

      if (wordComplete == 1) {
        printf("\n\nYou won! congratulations!\n");
        printf("\nNow close your eyes! You are about to hear like angels sing...\n");

        printf("\n3\n");
        sleep(2);
        printf("\n2\n");
        sleep(2);
        printf("\n1\n");
        sleep(2);

        printf("\nPlaying track...\n");
        play_track("reward.mp3");
        return 0;
      }
      printf("\n");
    } else {
      printf("\n");
      for (int i = 0; i < len; i++) {
        if (strchr(letters, word[i])) {
          printf("%c ", word[i]);
        } else {
          printf("_ ");
        }
      }
      printf("\n");

      lives = lives - 1;

      printf("\n");
      printf("Lives left: %d\n", lives);
      printf("%s\n", hangmanAscii[lives]);
    }
  }
  printf("\n\nYou are very-very dead :(\n");
  printf("Random word: %s\n\n", word);
  play_track("loss.wav");
  return 0;
}