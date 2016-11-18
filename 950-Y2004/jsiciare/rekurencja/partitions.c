/*  
 *    File: partitions.c 
 *    Author: Jacek Siciarek
 *    Date: 2003/10/30
 */

#include <stdio.h>
#define SETTXT "1, 3, 4, 5"
#define SET     1, 3, 4, 5
#define SETSIZE 4
#define TARGET  5  /* warto¶æ liczby podzia³u   */

static int NumberOfPartitions(int sSet[], int size, int target);
static void CountPartitions(int subsetSize, int Set[]);

int sampleSet[] = {SET};
int rSize = 0, record_subsetSize = 1;
int pTarget = 0, checkSum = 0;
int partitions = 0;
char binary[64] = "";

int main()
{
    printf("Liczba podzia³ów zbioru {%s} sumuj±cych siê do %d to %d\n",
            SETTXT,
            TARGET,
            NumberOfPartitions(sampleSet,SETSIZE,TARGET));
    return 0;
}

static int NumberOfPartitions(int sSet[], int size, int target)
{
    pTarget=target;
    CountPartitions(size,sSet);

    return partitions;
}

static void CountPartitions(int subsetSize, int Set[])
{
    int a;

    if (record_subsetSize) {rSize = subsetSize;record_subsetSize = 0;}

    if (subsetSize) {
        binary[rSize - subsetSize] = '0'; CountPartitions(subsetSize - 1, Set);
        binary[rSize - subsetSize] = '1'; CountPartitions(subsetSize - 1, Set);
    } else {
        for (a = 0; a < rSize; a++) {
        checkSum+=(binary[a]=='1')?Set[a]:0;
        }
        if(checkSum==pTarget){partitions++;}
        checkSum=0;
    }
}
