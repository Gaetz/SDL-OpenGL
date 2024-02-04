#ifndef GAMESTATE_MAIN_H
#define GAMESTATE_MAIN_H

#include "../engine/gamestate.h"
#include "piece.h"
#include "pieces.h"
#include "board.h"
#include "game.h"

#define SPEED 500

// Main scene of the game, contains all the game's logic
class GameStateMain : public GameState {
public:
    GameStateMain(
            std::shared_ptr<SpriteRenderer>,
            std::shared_ptr<GeometryRenderer>
    );

    ~GameStateMain() override;

    GameStateMain() = delete;

    void load() override;

    void clean() override;

    void pause() override;

    void resume() override;

    void handleEvent(const InputState&) override;

    void update(unsigned int dt) override;

    void draw() override;

    void setGame(IGame*) override;

    void createNewPiece();

    Piece currentPiece {};

private:
    static int getRand(int a, int b);

    int moveLeftKey { 0 };
    int moveRightKey { 0 };
    int rotateKey { 0 };
    int fallKey { 0 };

    std::shared_ptr<SpriteRenderer> sRenderer;
    std::shared_ptr<GeometryRenderer> gRenderer;

    Game* game { nullptr };
    Pieces* pieces { nullptr };
    Board* board { nullptr };
    unsigned int counter { 0 };
    int screenHeight { 0 };

    Piece nextPiece {};

    void drawPiece(Piece piece);

    void drawBoard();
};

#endif
