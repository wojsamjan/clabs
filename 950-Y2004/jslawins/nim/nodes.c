/* Jakub S³awiñski 13.12.2003 r.
 * plik implementuj±cy obs³ugê listy podwójnie dowi±zanej
 * nodes.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dramm.h"

void
insertnode(nodeT** headRef, moveT move) {
        nodeT* newmove;
        newmove = malloc(sizeof(nodeT));
        newmove->next = *headRef;
        newmove->prev = NULL;
	newmove->move.lmoves = move.lmoves;
        memcpy(newmove->move.board, move.board, 64);
        memcpy(newmove->move.moves, move.moves, 48);
        if (*headRef) {
                (*headRef)->prev = newmove;
        }
        *headRef = newmove;
}

void
freelist(nodeT** headRef) {
        nodeT *iterator, *previous;
        iterator = *headRef;
        while (iterator) {
                previous = iterator;
                iterator = iterator->next;
                free(previous);
        }
        *headRef = NULL;
}

void
sortlist(nodeT** headRef)
{
        nodeT* iterator;
        nodeT* pointer;
        nodeT* temporary;
        pointer = *headRef;
        while (pointer) {
                iterator = *headRef;
                while (iterator->move.lmoves > pointer->move.lmoves) {
                        iterator = iterator->next;
                }
                if (iterator != pointer) { 
                        temporary = pointer->next;
                        pointer->prev->next = pointer->next;
                        if (pointer->next) {
                                pointer->next->prev = pointer->prev;
			}
                        if (iterator->prev) {
                                iterator->prev->next = pointer;
                        }
                        else {
                                *headRef = pointer;
                        } 
                        pointer->prev = iterator->prev;
                        pointer->next = iterator;
                        iterator->prev = pointer;
                        pointer = temporary;
                        continue;
                }
                pointer = pointer->next;
        }
}

void
cutlist(nodeT* head)
{
	char amount;
	nodeT* iterator;
	iterator = head;
	amount = 0;
	while (iterator) {
		if ((iterator->move.lmoves == 0) && (amount == 0))
			return;
		if (iterator->move.lmoves < amount) {
			iterator->prev->next = NULL;
			freelist(&iterator);
			return;
		}
		amount = iterator->move.lmoves;
		iterator = iterator->next;
	}
}
