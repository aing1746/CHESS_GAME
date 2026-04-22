// GameState.h
#pragma once

struct GameState {
    bool whiteTurn = true;
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookMoved[2] = {false, false};
    bool blackRookMoved[2] = {false, false};
    bool lastMoveWasDoublePawn = false;
    int  lastPawnRow = 0;
    int  lastPawnCol = 0;
};