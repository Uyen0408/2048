#include"move.h"

void rushTop(int **&tab, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (tab[k - 1][j] == 0) {
						tab[k - 1][j] = tab[k][j];
						tab[k][j] = 0;
					}
				}
			}
		}
	}
}
void moveTop(int **&tab, int size, unsigned int &score) {
	rushTop(tab, size);
	
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] != 0) {
				if (tab[i - 1][j] == tab[i][j]) {
					tab[i - 1][j]+= tab[i][j];
					score += tab[i - 1][j];
					tab[i][j] = 0;
				
				}
			}
		}
	}

	rushTop(tab, size);
}

void rushBot(int **&tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[j][i] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[k + 1][i] == 0) {
						tab[k + 1][i] = tab[k][i];
						tab[k][i] = 0;
					}
				}
			}
		}
	}
}
void moveBot(int **&tab, int size, unsigned int &score) {
	rushBot(tab, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[j][i] != 0) {
				if (tab[j][i] == tab[j + 1][i]) {
					tab[j + 1][i] += tab[j][i];
					score += tab[j + 1][i];
					tab[j][i] = 0;
				}
			}
		}
	}

	rushBot(tab, size);
}

void rushRight(int **&tab, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[i][j] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[i][k + 1] == 0) {
						tab[i][k + 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}
void moveRight(int **&tab,int size, unsigned int &score) {
	rushRight(tab, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j + 1]) {
					tab[i][j + 1] += tab[i][j];
					score += tab[i][j + 1];
					tab[i][j] = 0;
				}
			}
		}
	}
	
	rushRight(tab, size);
}

void rushLeft(int **&tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (tab[i][j] != 0) {
				for (int k = j; k > 0; --k) {
					if (tab[i][k - 1] == 0) {
						tab[i][k - 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}
void moveLeft(int **&tab, int size, unsigned int &score) {

	rushLeft(tab, size);

	for(int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j - 1]) {
					tab[i][j - 1] += tab[i][j];
					score += tab[i][j - 1];
					tab[i][j] = 0;
				}
			}
		}
	}

	rushLeft(tab, size);
}


void move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore,Mix_Chunk *chuck) {
	int **checkTab = createtab(size);
	int checkScore = backScore;
	copyTab(checkTab, backtab, size);

	copyTab(backtab, tab, size);
	backScore = score;
	


	if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) moveTop(tab, size, score);
	else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) moveBot(tab, size, score);
	else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT) moveLeft(tab, size, score);
	else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) moveRight(tab, size, score);

	if (checkToRandom(tab, backtab, size)) {
		randomOnBoard(tab, size);
		Mix_PlayChannel(-1,chuck,0);
	}
	 else {
		copyTab(backtab, checkTab, size);
	 	backScore = checkScore;
	}

	for (int i = 0; i < size; ++i)
		delete[] checkTab[i];
	delete[] checkTab;
}
