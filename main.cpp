#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <deque>
#include <string>

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *backgroud_img = NULL;
SDL_Texture *endgame_img = NULL;
const string TITLE = "Snake";
const int WIDTH = 500;
const int HEIGHT = 500;
const int jump = 25;

SDL_Texture *loadTexture(string path);
bool init(); //hàm khởi tạo màn hình và bút vẽ
bool loadImage(); // hàm load ảnh
void close(); // hàm giải phóng bộ nhớ
void mainGame(); // màn hình chơi game
void startGame(); // màn hình bắt đầu
bool clickMenu(); // bắt sự kiện click ở màn hình bắt đầu
void renderTexture(SDL_Texture *img, int startX, int startY, int width, int height); //hàm render ảnh
void endGame();
bool clickEndMenu();

class food{
public:

    int randomX(){
        return (rand() % (WIDTH/25))*25;
    }

    int randomY(){
        return (rand() % (HEIGHT/25))*25;
    }

    void newPoint(){
        x = randomX();
        y = randomY();
    }

    int x = randomX();
    int y = randomY();

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }
};

class snake{
public:
    int x = 250;
    int y = 250;
    int speed = 10;
    int x_before = x;
    int y_before = y;
    int sizeSnake = 2;
    deque<int> bodyX;
    deque<int> bodyY;

    snake(){

        bodyX.push_front(200);
        bodyX.push_front(175);

        bodyY.push_front(250);
        bodyY.push_front(250);
    }

    int bodyUpdate(int type){
        bodyX.push_front(x_before);
        bodyY.push_front(y_before);
        if (type == 0){
            bodyX.pop_back();
            bodyY.pop_back();
        }

    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void getKey(char key){
        x_before = x;
        y_before = y;
        if (key == 'u'){
            y -= jump;
        }else if (key == 'd'){
            y += jump;
        }else if (key == 'l'){
            x -= jump;
        }else if (key == 'r'){
            x += jump;
        }
    }

    bool checkDie(){
        if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0){
            return false;
        }
        for (int i = 0 ; i < sizeSnake ; i++){
            if ( x == bodyX.at(i) && y == bodyY.at(i) ){
                return false;
            }
        }
        return true;
    }

    bool eatFood(food f){
        if (x == f.getX() && y == f.getY()){
            sizeSnake++;
            speed ++;
            bodyUpdate(1);
            return true;
        }
        bodyUpdate(0);
        return false;
    }

};

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Init error\n";
		return 0;
	} else {
		window = SDL_CreateWindow(TITLE.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
		if(window == NULL) {
			cout << "Create window error\n";
			return 0;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL) {
				cout << "Render create error\n";
				return 0;
			}
			SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
		}
	}
	if(!loadImage()) {
		cout << "Can't load image, there's something missing\n";
		return 0;
	}
	return 1;
}

bool loadImage(){
    bool success = 1;
    backgroud_img = loadTexture("C:/Users/dell/Downloads/menuGame.bmp");
    endgame_img = loadTexture("C:/Users/dell/Downloads/restart.jpg");
    if (backgroud_img == NULL || endgame_img == NULL) {
        cout << "Load fail\n";
        success = 0;
    }

    return success;
}

void close() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(backgroud_img);
	SDL_DestroyTexture(endgame_img);
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *loadTexture(string path) {
	SDL_Surface *image = IMG_Load(path.c_str());
	SDL_Texture *tmp = NULL;
	if(image == NULL) {
		cout << "Load image error\n";
	} else {
		tmp = SDL_CreateTextureFromSurface(renderer,image);
		SDL_FreeSurface(image);
		if(tmp == NULL) {
			cout << "Create texture error\n";
		}
	}
	return tmp;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
    //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void startGame(){
    SDL_RenderClear(renderer);
    renderTexture(backgroud_img, renderer, 0, 0, 500, 500);
    SDL_RenderPresent(renderer);
}

bool clickEndMenu(){
    SDL_Event e;
    while (true){
        while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				close();
				exit(0);
			} else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.x >= 203 && e.button.x <= 298 && e.button.y >= 264 && e.button.y <= 284) {
                    return true;
                }
			}
		}
    }
}

void endGame(){
    SDL_RenderClear(renderer);
    renderTexture(endgame_img, renderer, 125, 187, 250, 125);
    SDL_RenderPresent(renderer);
    if (clickEndMenu() == true){
        mainGame();
    }
}

void mainGame() {
	SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Event e;
    snake mySnake;
    food myFood;
    char key = 'r';

    // đầu rắn
    SDL_Rect headSnake;
    headSnake.h = 25;
    headSnake.w = 25;

    // thức ăn
    SDL_Rect foodofSnake;
    foodofSnake.h = 25;
    foodofSnake.w = 25;


    bool checkEventKey = true;
    while (checkEventKey) {
        // bắt sự kiện bàn phím
        while ( SDL_PollEvent(&e)){
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP && key != 'd') {key = 'u';}
                if (e.key.keysym.sym == SDLK_DOWN && key != 'u') {key = 'd';}
                if (e.key.keysym.sym == SDLK_LEFT && key != 'r') {key = 'l';}
                if (e.key.keysym.sym == SDLK_RIGHT && key != 'l') {key = 'r';}
            }
            if(e.type == SDL_QUIT) checkEventKey = false;
        }
        mySnake.getKey(key);


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // vẽ đầu rắn
        SDL_SetRenderDrawColor(renderer, 123, 123, 0, 255);
        headSnake.x = mySnake.getX();
        headSnake.y = mySnake.getY();
        SDL_RenderFillRect(renderer, &headSnake);

        // kiểm tra chết
        if (mySnake.checkDie() == false){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            endGame();

        }




        // ăn thức ăn
        if (mySnake.eatFood(myFood) == true) {
            myFood.newPoint();
        }

        // random thức ăn
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        foodofSnake.x = myFood.getX();
        foodofSnake.y = myFood.getY();
        SDL_RenderFillRect(renderer, &foodofSnake);

        // tăng kích cỡ
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0 ; i < mySnake.sizeSnake ; i++){
            headSnake.x = mySnake.bodyX.at(i);
            headSnake.y = mySnake.bodyY.at(i);
            SDL_RenderFillRect(renderer, &headSnake);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1250/mySnake.speed);
    }

    close();
}



bool clickStartMenu(){
    SDL_Event e;
    while (true){
        while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				close();
				exit(0);
			} else if(e.type == SDL_MOUSEBUTTONDOWN) {
				//cout << e.button.x << " " << e.button.y << "\n";
                if (e.button.x >= 189 && e.button.x <= 305 && e.button.y >= 267 && e.button.y <= 319) {
                    return true;
                }
                if (e.button.x >= 194 && e.button.x <= 299 && e.button.y >= 331 && e.button.y <= 372)  {
                    close();
                    exit(0);
                }
			}
		}
    }

}


int main(int argc, char *argv[]) {
    if (init())
    {
        startGame();

        if (clickStartMenu() == true){
            mainGame();
        }

        close();
    }
	return 0;
}
