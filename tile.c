

#include <stdio.h>

#include <stdint.h>

 

uint16_t vaddr;

uint8_t chr_rom[0x2000];

 

int _main(int argc, char *argv[])

{

                int row, i;

                uint8_t tile[8];

                uint8_t tile_lo, tile_hi;

               

                vaddr = 0x0000;

               

                /* draw tile */  

                for(row = 0; row < 8; row++)

                {

                                tile_lo = vaddr; /* read from 0x1000 */

                                tile_hi = vaddr + 8; /* read from 0x1008 */

               

                                for(i = 0; i < 8; i++)

                                                tile[i] = ((tile_lo >> i) & 1) | (((tile_hi >> i) & 1) << 1);

                                               

                                vaddr += 8;

                }

                               

                for(i = 7; i >= 0; i--)

                                printf("%d ", tile[i]);

               

                printf("\n");

                return 0;

}

 

/*

strncmp("NES\x1a", header, 4);

*/

 
