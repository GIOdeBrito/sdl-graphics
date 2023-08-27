#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* argv[])
{
	printf("Inicializando\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return -2;
	}

	SDL_Window* window = NULL;
	window = SDL_CreateWindow("SDL Graficos Teste",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800, 600,SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		printf("NAO PODE CRIAR A JANELA SDL");
		return -6;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(renderer == NULL)
	{
		printf("NAO PODE CRIAR O RENDERIZADOR SDL");
		SDL_DestroyWindow(window);
		return -8;
	}

	char img_nome[] = "baal.png";
	int win_X = 0;
	int win_Y = 0;
	SDL_GetWindowSize(window, &win_X, &win_Y);

	SDL_Surface* img_surface = IMG_Load(img_nome);
	SDL_Texture* img = SDL_CreateTextureFromSurface(renderer, img_surface);

	SDL_Rect img_rect = { .x = win_X/3, .y = win_Y/3, .w = 300, .h = 300 };
	SDL_Point pivo = { img_rect.w / 3, img_rect.h / 3 };
	SDL_FreeSurface(img_surface);

	if(img == NULL)
	{
		printf("NAO PODE CARREGAR A IMAGEM: %s", img_nome);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		return -9;
	}

	double img_angulo = 45;

	while(1)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				break;
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

		if(img_angulo >= 360.0f)
		{
			img_angulo = 0;
		}

		img_angulo += .6 * 0.06;
		printf("ANGULO = %.2lf\n", img_angulo);

		// Limpa a tela
		SDL_RenderClear(renderer);
		// Copia a textura para o contexto de renderização
		//SDL_RenderCopy(renderer, img, NULL, &img_rect);
		SDL_RenderCopyEx(renderer, img, NULL, &img_rect, img_angulo, &pivo, SDL_FLIP_NONE);
		// Mostra tudo a ser renderizado
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(img);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("Programa encerrado\n");

	return 0;
}
