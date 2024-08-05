/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char* new_string(char* str) {
  char* new_str = (char*)malloc(strlen(str) + 1);
  if (new_str == NULL) {
    return NULL;
  }
  return strcpy(new_str, str);
}

int init_words(WordCount** wclist) {
  /* Initialize word count.
     Returns 0 if no errors are encountered
     in the body of this function; 1 otherwise.
  */
  if (wclist == NULL) {
    return 1;
  } else {
    *wclist = NULL;
    return 0;
  }
}

ssize_t len_words(WordCount* wchead) {
  /* Return -1 if any errors are
     encountered in the body of
     this function.
  */
  if (wchead == NULL) {
    return -1;
  } else {
    size_t len = 0;
    while (wchead != NULL) {
      len++;
      wchead = wchead->next;
    }
    return len;
  }
}

WordCount* find_word(WordCount* wchead, char* word) {
  /* Return count for word, if it exists */
  WordCount* wc = NULL;
  if (word == NULL || wchead == NULL) {
    return wc;
  }
  while (wchead != NULL) {
    if (strcmp(wchead->word, word) == 0) {
      wc = wchead;
      return wc;
    } else {
      wchead = wchead->next;
    }
  }
  return NULL;
}

int add_word(WordCount** wclist, char* word) {
  /* If word is present in word_counts list, increment the count.
     Otherwise insert with count 1.
     Returns 0 if no errors are encountered in the body of this function; 1 otherwise.
  */
  if (wclist == NULL) {
    return 1;
  }

  WordCount* current = *wclist;
  WordCount* prev = NULL;
  while (current != NULL) {
    if (strcmp(current->word, word) == 0) {
      current->count++;
      return 0;
    }
    prev = current;
    current = current->next;
  }
  WordCount* newWord = (WordCount*)malloc(sizeof(WordCount)); //must allocate memory for new node
  if (newWord ==
      NULL) { //malloc could return a null pointer and when we try to dereference it, it will cause errors
    return 1;
  }
  newWord->word = strdup(word); // creates a copy of the word
  if (newWord->word == NULL) {
    free(newWord);
    return 1; // memory allocation failed
  }
  newWord->count = 1;
  newWord->next = NULL;

  if (prev == NULL) { //list was empty
    *wclist = newWord;
  } else {
    prev->next = newWord;
  }

  return 0;
}

void fprint_words(WordCount* wchead, FILE* ofile) {
  /* print word counts to a file */
  WordCount* wc;
  for (wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
