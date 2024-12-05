#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int width = 0;
int height = 0;
typedef int arr2d[200][200];

// M..
// .A.
// ..S
bool is_down_and_right(arr2d arr, int row, int col) {
  return arr[row-1][col-1] == 'M' && arr[row+1][col+1] == 'S';
}

// S..
// .A.
// ..M
bool is_up_and_left(arr2d arr, int row, int col) {
  return arr[row-1][col-1] == 'S' && arr[row+1][col+1] == 'M';
}

// ..S
// .A.
// M..
bool is_up_and_right(arr2d arr, int row, int col) {
  return arr[row-1][col+1] == 'S' && arr[row+1][col-1] == 'M';
}

// ..M
// .A.
// S..
bool is_down_and_left(arr2d arr, int row, int col) {
  return arr[row-1][col+1] == 'M' && arr[row+1][col-1] == 'S';
}

int count_x_shaped_mas(arr2d arr, int row, int col) {
  // Since we're matching on the A in the middle,
  // we can skip checking the first and last columns.
  if (col == 0 || col == width) return 0;

  // We can also skip the first and last rows.
  if (row == 0 || row == height) return 0;

  if (arr[row][col] != 'A') return 0;

  if ((
    is_down_and_right(arr, row, col) ||
    is_up_and_left(arr, row, col)
  ) && (
    is_up_and_right(arr, row, col) ||
    is_down_and_left(arr, row, col)
  )) {
    return 1;
  }

  return 0;
}

// SAMX
int count_left(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row][col-1] == 'M' &&
    arr[row][col-2] == 'A' &&
    arr[row][col-3] == 'S'
  ) ? 1 : 0;
}

// XMAS
int count_right(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row][col+1] == 'M' &&
    arr[row][col+2] == 'A' &&
    arr[row][col+3] == 'S'
  ) ? 1 : 0;
}

// S
// A
// M
// X
int count_up(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row-1][col] == 'M' &&
    arr[row-2][col] == 'A' &&
    arr[row-3][col] == 'S'
  ) ? 1 : 0;
}

// X
// M
// A
// S
int count_down(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row+1][col] == 'M' &&
    arr[row+2][col] == 'A' &&
    arr[row+3][col] == 'S'
  ) ? 1 : 0;
}

// X...
// .M..
// ..A.
// ...S
int count_down_right_diag(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row+1][col+1] == 'M' &&
    arr[row+2][col+2] == 'A' &&
    arr[row+3][col+3] == 'S'
  ) ? 1 : 0;
}

// ...X
// ..M.
// .A..
// S...
int count_down_left_diag(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row+1][col-1] == 'M' &&
    arr[row+2][col-2] == 'A' &&
    arr[row+3][col-3] == 'S'
  ) ? 1 : 0;
}

// ...S
// ..A.
// .M..
// X...
int count_up_right_diag(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row-1][col+1] == 'M' &&
    arr[row-2][col+2] == 'A' &&
    arr[row-3][col+3] == 'S'
  ) ? 1 : 0;
}

// S...
// .A..
// ..M.
// ...X
int count_up_left_diag(arr2d arr, int row, int col) {
  return (
    arr[row][col] == 'X' &&
    arr[row-1][col-1] == 'M' &&
    arr[row-2][col-2] == 'A' &&
    arr[row-3][col-3] == 'S'
  ) ? 1 : 0;
}

int count_xmas(arr2d arr, int row, int col) {
  return
    count_left(arr, row, col) +
    count_right(arr, row, col) +
    count_up(arr, row, col) +
    count_down(arr, row, col) +
    count_down_right_diag(arr, row, col) +
    count_down_left_diag(arr, row, col) +
    count_up_right_diag(arr, row, col) +
    count_up_left_diag(arr, row, col);
}

int word_search(char* file, bool x_shape) {
  FILE *fp = fopen(file, "r");
  assert(fp != NULL);

  int total = 0;
  int col = 0;
  int row = 0;
  arr2d arr;
  width = 0;
  height = 0;

  int c;
  while((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      row++;
      col = 0;
      continue;
    }

    if (col > width) width = col;
    if (row > height) height = row;

    arr[row][col++] = c;
  }

  for (int i = 0; i <= height; i++) {
    for (int j = 0; j <= width; j++) {
      if (x_shape) {
        total += count_x_shaped_mas(arr, i, j);
      } else {
        total += count_xmas(arr, i, j);
      }
    }
  }

  fclose(fp);

  return total;
}

int main() {
  int result;

  result = word_search("example.txt", false);
  assert(result == 18);

  result = word_search("input.txt", false);
  assert(result == 2536);

  result = word_search("example.txt", true);
  assert(result == 9);

  result = word_search("input.txt", true);
  assert(result == 1875);

  printf("Result: %u\n", result);

  return EXIT_SUCCESS;
}
