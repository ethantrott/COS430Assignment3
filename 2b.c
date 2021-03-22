/*  Ethan Trott
*   COS 430
*   Assignment 3
*/

#include <stdio.h>
#include <string.h>

#define SIZE_TO 20

int copy_buf(char *to, int pos, char *from, int len)
{
    int i;
    for (i=0; i<len; i++) {     //for each byte of data..

        //prevent buffer overflow attacks
        if (pos >= SIZE_TO-1 || i >= strlen(from)){
            printf("Warning:: Breaking to prevent buffer overflow..\n");
            break;
        }

        to[pos] = from[i];          //copy source data to destination at position pos
        pos++;                      //increment position tracker
    }
    return pos;                 //return new position
}

// reads data from "fil", stores in "to". Returns the length of data.
short read_chunk(FILE *fil, char *to)
{
    short len;

    fread(&len, 2, 1, fil);             /* read len (a 2-byte short) */

    // if the length is greater than our "to" string can hold (including /0)..
    if (len > SIZE_TO-1){
        printf("Warning:: Limiting length to prevent buffer overflow..\n");
        fread(to, 1, SIZE_TO-1, fil);   /* read SIZE_TO-1 bytes of binary data */
    }

    //otherwise, add entire length of text
    else   
        fread(to, 1, len, fil);         /* read len bytes of binary data */

    return len; // return the length
}

void test_copy_buf(){
    char to[SIZE_TO] = "test ";
    int pos = 5;
    char from[23] = "new content is too long";
    int len = strlen(from);

    printf("Before:: to: '%s' | pos: %d | from: '%s' | len: %d | SIZE_TO: %d\n", to, pos, from, len, SIZE_TO);

    pos = copy_buf(to, pos, from, len);

    printf("After:: to: '%s' pos: %d \n\n", to, pos);
    return;
}

void test_read_chunk(){
    FILE *fp;
    fp = fopen("badtestdata.raw", "r");

    char to[SIZE_TO] = "";

    printf("Before:: to: '%s' | SIZE_TO: %d\n", to, SIZE_TO);

    short len = read_chunk(fp, to);

    printf("After:: to: '%s' | SIZE_TO: %d | attempted len: %hi\n", to, SIZE_TO, len);
}

int main(){
    printf("Problem 2B, Ethan Trott\n");

    printf("--------------------------\n\n");

    printf("Testing copy_buf..\n\n");
    test_copy_buf();

    printf("--------------------------\n\n");

    printf("Testing read_chunk..\n\n");
    test_read_chunk();

    return 0;
}
