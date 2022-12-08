#include <raylib.h>
#include <swsdm.h>


class Player {
    sws::vec2* pos;
    Texture2D img = LoadTexture("player.png");
public:
    Player() {
        pos = sws::DM::vtov2("PLAYER:POS");
    }
    ~Player() {
        UnloadTexture(img);
    }
    void move() {
        if (IsKeyDown(KEY_RIGHT)) {
            pos->x += 1.0f;
            sws::DM::update_data("PLAYER:POS", pos->to_string());
        }
        if (IsKeyDown(KEY_LEFT)) {
            pos->x -= 1.0f;
            sws::DM::update_data("PLAYER:POS", pos->to_string());
        }
        if (IsKeyDown(KEY_DOWN)) {
            pos->y += 1.0f;
            sws::DM::update_data("PLAYER:POS", pos->to_string());
        }
        if (IsKeyDown(KEY_UP)) {
            pos->y -= 1.0f;
            sws::DM::update_data("PLAYER:POS", pos->to_string());
        }
    }
    void draw() {
        DrawTexture(img, pos->x, pos->y, MAGENTA);
    }
    void setPos(sws::vec2* pos) {
        this->pos = pos;
    }
};

void Load(Player* p) {
    if (!IsKeyDown(KEY_LEFT_SHIFT)) {
        if (IsKeyPressed(KEY_F1)) {
            std::cout << "File 1 loaded" << std::endl;
            sws::DM::load_data("save1");
            p->setPos(sws::DM::vtov2("PLAYER:POS"));
        }
        if (IsKeyPressed(KEY_F2)) {
            std::cout << "File 2 loaded" << std::endl;
            sws::DM::load_data("save2");
            p->setPos(sws::DM::vtov2("PLAYER:POS"));
        }
        if (IsKeyPressed(KEY_F3)) {
            std::cout << "File 3 loaded" << std::endl;
            sws::DM::load_data("save3");
            p->setPos(sws::DM::vtov2("PLAYER:POS"));
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
    sws::DM();
    const sws::vec2* WIN_SIZE = sws::DM::vtov2("WIN:SIZE");
    InitWindow(WIN_SIZE->x, WIN_SIZE->y, "libswsdm example");
    SetTargetFPS(60);
    Player *p = new Player();
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
