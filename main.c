#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define NES_WIDTH		256
#define NES_HEIGHT		240

#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{    
	FILE *rom_file;
	uint8_t header[16];
	uint8_t prg_rom[0x4000];
	uint8_t chr_rom[0x2000];
	
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    int quit = 0;
    SDL_Event event;
    int *pixels;
    SDL_Rect dest;

    SDL_Init(SDL_INIT_VIDEO);
    
    window = SDL_CreateWindow("fishyNES", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    pixels = (int *)malloc(NES_WIDTH * NES_HEIGHT * sizeof(int));
    memset(pixels, 100, NES_WIDTH * NES_HEIGHT * sizeof(int));

	dest.x = 192;
	dest.y = 120;
	dest.w = NES_WIDTH;
	dest.h = NES_HEIGHT;

	rom_file = fopen("donkey.nes", "rb");
	fread(&header, 16, 1, rom_file);
	fread(prg_rom, 0x4000, 1, rom_file);
	fread(chr_rom, 0x2000, 1, rom_file);
	fclose(rom_file);

    while(!quit)
    {
        SDL_UpdateTexture(texture, &dest, pixels, NES_WIDTH * sizeof(int));
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
         
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				break;
		}
		
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
