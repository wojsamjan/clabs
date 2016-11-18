#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "direction_stack.h"

/* Stos jest reprezentowany za pomoc± pojedynczej listy */

struct Stack {
      directionT dir;
      pointT pt;
      bool last_d;
      struct Stack* prev;
};

typedef struct Stack Stack;

static Stack* First = NULL;
static Stack* Top = NULL;

void ds_push(directionT dir, pointT pt, bool ld)
{
      Stack* temp;

      if (First == NULL) {
            First = malloc(sizeof(Stack));
            First->dir = dir;
            First->pt = pt;
            First->last_d = ld;
            First->prev = NULL;
            Top = First;
      }
      else {
            temp = malloc(sizeof(Stack));
            temp->prev = Top;
            temp->dir = dir;
            temp->pt = pt;
            temp->last_d = ld;
            Top = temp;
      }
}

void ds_pop(void)
{
      if (Top == First) {
            free(Top);
            Top = First = NULL;
      }
      else {
            Stack* temp = Top->prev;
            free(Top);
            Top = temp;
      }
}

void ds_top(directionT* dir, pointT* pt, bool* ld)
{
      *dir = Top->dir;
      *pt = Top->pt;
      *ld = Top->last_d;
}

bool ds_empty(void)
{
      return First == NULL;
}

void ds_clear(void)
{
      while (!ds_empty)
            ds_pop();
}

void ds_set_dir_at_top(directionT dir)
{
      Top->dir = dir;
}

void ds_set_last_d_at_top(bool ld)
{
      Top->last_d = ld;
}

static const char* strdir(directionT dir)
{
      switch (dir) {
            case North: return "North";
            case East: return "East";
            case South: return "South";
            case West: return "West";
      }
      return "";
}

void ds_print(void)
{
      Stack* temp = Top;
      
      while (temp) {
            printf("(%d, %d), %s\n", temp->pt.x, temp->pt.y, strdir(temp->dir));
            temp = temp->prev;
      }
}
