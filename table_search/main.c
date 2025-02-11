#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 指针表的长度
#define HASHSIZE 101

// 链表项
struct nlist {
  struct nlist *next; // 链表的下一表项
  char *name;         // 定义的名字
  char *defn;         // 替换文本
};

// 指针表
static struct nlist *hashtable[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }

  return hashval % HASHSIZE;
}

// 在hashtable中查找s
struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtable[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }

  return NULL;
}

// 将(name, defn)加入到hashtable中
struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof *np);
    if (np == NULL || (np->name = strdup(name)) == NULL) {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtable[hashval];
    hashtable[hashval] = np;
  } else { // 已存在
    // 释放内存
    free((void *)np->defn);
  }

  if ((np->defn = strdup(defn)) == NULL) {
    return NULL;
  }

  return np;
}

int main() {
  install("a", "1");
  install("b", "2");

  struct nlist *t1 = lookup("c");
  printf("t1: %d\n", t1 == NULL);

  //  printf("t1: name: %s, defn: %s", t1->name, t1->defn); // 这样会core

  struct nlist *t2 = lookup("b");
  printf("t2: name: %s, defn: %s\n", t2->name, t2->defn);
}