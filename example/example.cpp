#include <raylib.h>
#include <swsdm.h>

class Player {
    float x;
    float y;
    Texture2D img = LoadTexture("player.png");
public:
    Player(float x, float y) {
        this->x = x;
        this->y = y;
    }
    ~Player() {
        UnloadTexture(img);
    }
    void move() {
        if (IsKeyDown(KEY_RIGHT)) {
            x += 1.0f;
            sws::DM::update_data(0, std::to_string(x));
        }
        if (IsKeyDown(KEY_LEFT)) {
            x -= 1.0f;
            sws::DM::update_data(0, std::to_string(x));
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += 1.0f;
            sws::DM::update_data(1, std::to_string(y));
        }
        if (IsKeyDown(KEY_UP)) {
            y -= 1.0f;
            sws::DM::update_data(1, std::to_string(y));
        }
    }
    void draw() {
        DrawTexture(img, x, y, MAGENTA);
    }
    void setPos(int x, int y) {
        this->x = x; this->y = y;
    }
};

void Load(Player* p) {
    if (!IsKeyDown(KEY_LEFT_SHIFT)) {
        if (IsKeyPressed(KEY_F1)) {
            std::cout << "File 1 loaded" << std::endl;
            sws::DM::load_data("save1");
            p->setPos(sws::DM::vtoi(0x00), sws::DM::vtoi(0x01));
        }
        if (IsKeyPressed(KEY_F2)) {
            std::cout << "File 2 loaded" << std::endl;
            sws::DM::load_data("save2");
            p->setPos(sws::DM::vtoi(0x00), sws::DM::vtoi(0x01));
        }
        if (IsKeyPressed(KEY_F3)) {
            std::cout << "File 3 loaded" << std::endl;
            sws::DM::load_data("save3");
            p->setPos(sws::DM::vtoi(0x00), sws::DM::vtoi(0x01));
        }
    }
}

void Save(void) {
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        if (IsKeyPressed(KEY_F1) ) {
            std::cout << "File 1 saved" << std::endl;
            sws::DM::save_data("save1");
        }
        if (IsKeyPressed(KEY_F2) ) {
            std::cout << "File 2 saved" << std::endl;
            sws::DM::save_data("save2");
        }
        if (IsKeyPressed(KEY_F3) ) {
            std::cout << "File 3 saved" << std::endl;
            sws::DM::save_data("save3");
        }
    }
}

int main(void) {
    InitWindow(640, 480, "libswsdm example");
    SetTargetFPS(60);
    sws::DM();
    Player *p = new Player(sws::DM::vtof(0), sws::DM::vtof(1));
    while(!WindowShouldClose()) {
        p->move();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("libswsdm example", 320, 240, 32, GREEN);
            DrawText("by spencer w. smith", 320, 280, 32, GREEN);
            Save();
            Load(p);
            p->draw();
        EndDrawing();
    }
    delete p;
    return EXIT_SUCCESS;
}
