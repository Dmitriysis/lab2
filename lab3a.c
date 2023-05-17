
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

const char *menu[] = {"1. Show", "2. Add", "3. Find", "4. Delete Item", "5. Quit"};
const int N =5;

typedef struct Item {
  int key;
  char *info;
} Item;

typedef struct Table {
  int n; // Максимальный размер таблицы
  int curr; // Текущий размер таблицы
  Item *items;
} Table;

int getTableInfo(Table *ptable);
int getInt(int *);
int dialog(const char *msgs[], int);
int TShow(Table *);
int TAdd(Table *);
int insert(Table *ptable, int ind, int key, char *info);
int find(Table *ptable, int key);
char *getStr();
int TFind(Table *);
int delete(Table *ptable, int index);
int TDelete(Table *);
void AllTDelete(Table *);

int main() {
  Table table = {0, 0, NULL};
  getTableInfo(&table);
  int ch = 0;
  while (1) {
    ch = dialog(menu, N);
    if (ch == 5) break;
    // printf("you entered: %d\n", rc);
    switch (ch)
        {
        case 1:
            TShow(&table);
            break;
        case 2:
            TAdd(&table);
            break;
        case 3:
            TFind(&table);
            break;
        case 4:
            TDelete(&table);
            break;
        }

  }
  printf("End and delete Table.\n");
  AllTDelete(&table);
  return 0;
}

int getTableInfo(Table *ptable) {
  char *pr = "";
  int m;
  do {
    printf("%s\n", pr);
    printf("Enter the maximum size of the table: ");
    pr = "Wrong number, repeat.";
    if (getInt(&m) == 0)
      return 0;
  } while (m < 1);
  ptable->n = m;
  ptable->curr = 0;
  ptable->items = (Item *)calloc(m, sizeof(Item));
  return 1;
}

int getInt(int *a) {
  int n;
  do {
    n = scanf("%d", a);
    scanf("%*c");
    if (n < 0)
      return 0;
    if (n == 0) {
      printf("%s\n", "Error! Repeat input");
      scanf("%*c");
    }
  } while (n == 0);
  return 1;
}

int dialog(const char *menu[], int n) {
  char *error = "";
  int rc;
  int i, m;

  do {
    puts(error);
    error = "Wrong number, repeat.";
    for (i = 0; i < n; ++i)
    puts(menu[i]);
    printf("--> ");
    m = getInt(&rc);
    printf("\n");
    if (m == 0)
      rc = 4;
  } while(rc < 0 || rc > n);

  return rc;
}

int TShow(Table *ptable) {
  int i = 0;
  printf("Table items:\n");
  printf("\n");
  while (i < ptable->n) {
    printf("Item %d - key: %d, info: %s\n", i, ptable->items[i].key, ptable->items[i].info);
    i++;
  }
  printf("End Table\n");
  return 1;
}

int TAdd(Table *ptable) {
  int key, i;
  char *info;

  if (ptable->curr >= ptable->n) {
    printf("Table overflow.\n");
    return 1;
  }

  printf("Enter key: ");
  if (getInt(&key) == 0) return 0;

  if (find(ptable, key) > -1) {
    printf("Error.Key %d already exist.\n", key);
    return 1;
  }

  printf("Enter info: ");
  info = getStr();
  if (info == NULL) return 0;
  insert(ptable, ptable->curr, key, info);
  return 1;
}

int insert(Table *ptable, int ind, int key, char *info) {
  ptable->items[ind].key = key;
  ptable->items[ind].info = info;
  printf("Inserted: key: %d, info: %s\n", ptable->items[ind].key, ptable->items[ind].info);
  ptable->curr += 1;
  return 1;
}

int find(Table *ptable, int key) {
  int i = 0, curr;

  for (i = 0; i < ptable->curr; i++) {
    if (ptable->items[i].key == key)
      return i;
  }
  return -1;
}

char *getStr() {
  char buf[21];
  char *data = NULL;
  int num, len = 0;
  do {
    num = scanf("%20[^\n]", buf);
    if (num == -1) return NULL;
    if (num == 0) return data;
    len += strlen(buf) + 1;
    data = (char *)realloc(data, len * sizeof(char));
    if (data == NULL) return NULL;

    if (len <= 21) memcpy(data, buf, strlen(buf) + 1);
    else memcpy((data + strlen(data)), buf, strlen(buf) + 1);
  } while (num == 1);
  return data;
}

int TFind(Table *ptable) {
  int key, index;
  printf("Enter key: ");
  if (getInt(&key) == 0) return 0;
  index = find(ptable, key);
  if (index > -1) {
    printf("Item found - key: %d, info: %s\n", ptable->items[index].key, ptable->items[index].info);
  } else {
    printf("Item not found.\n");
  }
  return 1;
}

int TDelete(Table *ptable) {
  int key, index;
  printf("Enter key: ");
  if (getInt(&key) == 0) return 0;
  index = find(ptable, key);

  if (index > -1) {
    delete(ptable, index);
    printf("Item with key %d delete!\n", key);
  } else {
    printf("Item with key %d not found.\n", key);
  }
  return 1;
}

int delete(Table *ptable, int index) {
  int c = ptable->curr - 1;
  ptable->items[index].key = ptable->items[c].key;
  ptable->items[index].info = ptable->items[c].info;
  ptable->items[c].key = 0;
  ptable->items[c].info = NULL;
  ptable->curr -= 1;
  return 1;
}

void AllTDelete(Table *ptable) {
  int i = 0;
  while (i < ptable->n) {
    ptable->items[i].key = 0;
    ptable->items[i].info = NULL;
    i++;
  }
  free(ptable->items);
}
