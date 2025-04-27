#include <iostream>
#include <raylib.h>

typedef enum GAMESCREEN { LOGO = 0, TITLE, GAMEPLAY, GAMEOVER } GAMESCREEN;

Color sky = { 37, 150, 190, 255 };
const int screen_height = 800;
const int screen_width = 1200;
const int speed = 20;

class bird {
public:
    float bird_coord = screen_height / 2;
    Texture2D body[3];
    int dir = 0;

    bird() {
        Image bodyimg[3];
        bodyimg[0] = LoadImage("res/bird.png");
        body[0] = LoadTextureFromImage(bodyimg[0]);
        UnloadImage(bodyimg[0]);

        bodyimg[1] = LoadImage("res/birdup.png");
        body[1] = LoadTextureFromImage(bodyimg[1]);
        UnloadImage(bodyimg[1]);

        bodyimg[2] = LoadImage("res/birddown.png");
        body[2] = LoadTextureFromImage(bodyimg[2]);
        UnloadImage(bodyimg[2]);
    }

    ~bird() {
        UnloadTexture(body[0]);
        UnloadTexture(body[1]);
        UnloadTexture(body[2]);
    }

    void draw() {
        DrawTexture(body[dir], 50, bird_coord, WHITE);
    }

    void update() {
        if (((bird_coord) != 0 && (bird_coord) >= 0) && ((bird_coord + body[0].height) != screen_height && (bird_coord + body[0].height) <= screen_height)) {
            if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN)) {
                bird_coord += speed;
                dir = 2;
            }
            else {
                bird_coord += 3;
                dir = 0;
            }

            if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP) || IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) {
                bird_coord -= speed;
                dir = 1;
            }
        }
    }

    Rectangle getBoundingBox() {
        return (Rectangle{ 45, bird_coord, (float)body[dir].width, (float)body[dir].height });
    }
};

class pipes {
public:
    Texture2D pipetex;
    Texture2D piperevtex;
    int speed = 20;
    int upperPipeY;
    int lowerPipeY;
    Vector2 cord;

    pipes(float x) {
        Image pipeimg = LoadImage("res/pipes.png");
        pipetex = LoadTextureFromImage(pipeimg);
        UnloadImage(pipeimg);

        Image piperevimg = LoadImage("res/pipesrev.png");
        piperevtex = LoadTextureFromImage(piperevimg);
        UnloadImage(piperevimg);
        cord = { x, (screen_height / 2) };
        generatexy();
    }

    ~pipes() {
        UnloadTexture(pipetex);
        UnloadTexture(piperevtex);
    }

    void draw() {
        DrawTexture(pipetex, cord.x, lowerPipeY, WHITE);
        DrawTexture(piperevtex, cord.x, upperPipeY, WHITE);
    }

    void update() {
        cord.x -= speed;
        if (cord.x < -pipetex.width) {
            cord.x = screen_width;
            generatexy();
        }
    }

    void generatexy() {
        lowerPipeY = GetRandomValue(100, 700);
        upperPipeY = lowerPipeY - 900; // Adjusting the gap size as needed
    }

    Rectangle getBoundingBoxUpper() {
        return (Rectangle{ cord.x - 5, (float)upperPipeY - 10, (float)piperevtex.width, (float)piperevtex.height });
    }

    Rectangle getBoundingBoxLower() {
        return (Rectangle{ cord.x - 5, (float)lowerPipeY + 10, (float)pipetex.width, (float)pipetex.height });
    }
};

int main() {
    InitWindow(screen_width, screen_height, "Flappy-bird");
    SetTargetFPS(25);
    Texture2D background = LoadTexture("res/background.png");
    Texture2D logo = LoadTexture("res/logo.png");
    Texture2D title = LoadTexture("res/title.png");
    int score = 0;
    bird player;
    pipes pipe1(screen_width), pipe2(screen_width + 500), pipe3(screen_width + 1000);
    GAMESCREEN current = LOGO;
    bool gamerun = true;
    int framecounter = 0;

    while (!WindowShouldClose()) {
        framecounter++;

        switch (current) {
        case LOGO:
            BeginDrawing();
            ClearBackground(sky);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(logo, screen_width / 2 - logo.width / 2, screen_height / 2 - logo.height / 2, WHITE);
            EndDrawing();

            if (framecounter > 75) {
                current = TITLE;
                framecounter = 0;
            }
            break;

        case TITLE:
            BeginDrawing();
            ClearBackground(sky);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(title, screen_width / 2 - title.width / 2, screen_height / 2 - title.height / 2, WHITE);
            DrawText("Press ENTER to Start", screen_width / 2 - MeasureText("Press ENTER to Start", 20) / 2, screen_height / 2 + title.height, 20, WHITE);
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) {
                current = GAMEPLAY;
            }
            break;

        case GAMEPLAY:
            if (gamerun) {
                player.update();
                pipe1.update();
                pipe2.update();
                pipe3.update();

                if (CheckCollisionRecs(player.getBoundingBox(), pipe1.getBoundingBoxUpper()) ||
                    CheckCollisionRecs(player.getBoundingBox(), pipe1.getBoundingBoxLower()) ||
                    CheckCollisionRecs(player.getBoundingBox(), pipe2.getBoundingBoxUpper()) ||
                    CheckCollisionRecs(player.getBoundingBox(), pipe2.getBoundingBoxLower()) ||
                    CheckCollisionRecs(player.getBoundingBox(), pipe3.getBoundingBoxUpper()) ||
                    CheckCollisionRecs(player.getBoundingBox(), pipe3.getBoundingBoxLower())) {
                    gamerun = false;
                    current = GAMEOVER;
                }
                else {
                    score++;
                }

                BeginDrawing();
                ClearBackground(sky);
                DrawTexture(background, 0, 0, WHITE);
                DrawText(TextFormat("%i score", score), (screen_width - 50) - MeasureText(TextFormat("%iscore"), 50) / 2, 50, 50, DARKGREEN);
                player.draw();
                pipe1.draw();
                pipe2.draw();
                pipe3.draw();
                EndDrawing();
            }
            break;

        case GAMEOVER:
            BeginDrawing();
            ClearBackground(sky);
            DrawTexture(background, 0, 0, WHITE);
            DrawText("Game Over", screen_width / 2 - MeasureText("Game Over", 40) / 2, screen_height / 2 - 20, 40, RED);
            DrawText(TextFormat("%i score", score), (screen_width - 50) - MeasureText(TextFormat("%i score"), 50) / 2, 50, 50, DARKGREEN);
            EndDrawing();
            break;

        default:
            break;
        }
    }

    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(title);
    CloseWindow();

    return 0;
}
