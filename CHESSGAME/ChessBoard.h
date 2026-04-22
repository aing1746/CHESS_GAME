// ChessBoard.h — 보드 상태와 기본 조작만 담당
#pragma once

#include <array>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Color {
    const string reset    = "\033[0m";
    const string bold     = "\033[1m";
    const string white_pc = "\033[97m";        // 백 기물 (밝은 흰색)
    const string black_pc = "\033[33m";        // 흑 기물 (노란색)
    const string light_sq = "\033[48;5;229m";  // 밝은 칸 (크림)
    const string dark_sq  = "\033[48;5;94m";  // 어두운 칸 (갈색)
    const string border   = "\033[90m";        // 테두리 (회색)
    const string label    = "\033[93m";        // 좌표 레이블 (노란색)
}


class ChessBoard {
public:
    array<array<string, 8>, 8> board;
    const array<string, 10> teamW = {"R","N","B","Q","K","P"};
    const array<string, 10> teamB = {"r","n","b","q","k","p"};

    ChessBoard() {
        string firstRowW[] = {"R","N","B","Q","K","B","N","R"};
        string firstRowB[] = {"r","n","b","q","k","b","n","r"};
        for (int i = 0; i < 8; i++) board[0][i] = firstRowW[i];
        for (int i = 0; i < 8; i++) board[1][i] = "P";
        for (int r = 2; r < 6; r++) for (int c = 0; c < 8; c++) board[r][c] = ".";
        for (int i = 0; i < 8; i++) board[6][i] = "p";
        for (int i = 0; i < 8; i++) board[7][i] = firstRowB[i];
    }



    void printBoard() const {
        cout << "\n";
        // cout << Color::BORDER << "    +--+--+--+--+--+--+--+--+" << Color::RESET << "\n";

        for (int r = 7; r >= 0; r--) {
            cout << Color::label << " " << (r+1) << " " << Color::reset;
            // cout << Color::BORDER << "|" << Color::RESET;

            for (int c = 0; c < 8; c++) {
                bool isLight = (r + c) % 2 == 1;
                string sq = isLight ? Color::light_sq : Color::dark_sq;
                string p  = board[r][c];

                bool isWhitePiece = (p != "." && isupper(p[0]));
                string pc = isWhitePiece ? Color::white_pc : Color::black_pc;

                cout << sq;
                if (p == ".") {
                    cout << "   ";
                } else {
                    cout << pc << Color::bold << " " << p << " " << Color::reset;
                }
                cout << Color::reset;

                // cout << Color::BORDER << "|" << Color::RESET;
            }
            cout << "\n";
            // cout << Color::BORDER << "    +--+--+--+--+--+--+--+--+" << Color::RESET << "\n";
        }

        // cout << Color::LABEL << "      a  b  c  d  e  f  g  h" << Color::RESET << "\n\n";
        cout << Color::label << "    a  b  c  d  e  f  g  h" << Color::reset << "\n\n";
    }
    

    void makeMove(int fr, int fc, int tr, int tc) {
        board[tr][tc] = board[fr][fc];
        board[fr][fc] = ".";
    }

    pair<int,int> findKing(bool white) const {
        string king = white ? "K" : "k";
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (board[r][c] == king) return {r, c};
        return {-1, -1};
    }

    bool isSameTeam(const string& piece, const string& target) const {
        if (target == ".") return false;
        auto& team = isupper(piece[0]) ? teamW : teamB;
        return find(team.begin(), team.end(), target) != team.end();
    }

    bool isOpponent(const string& piece, const string& target) const {
        if (target == ".") return false;
        auto& enemy = isupper(piece[0]) ? teamB : teamW;
        return find(enemy.begin(), enemy.end(), target) != enemy.end();
    }
};