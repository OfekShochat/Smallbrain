#pragma once
#include "tests.h"

namespace Tests
{
inline bool testAllZobristHash()
{
    Board b;

    b.applyFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    expect(b.zobristHash(), 0x463b96181691fc9c, "Startpos");

    b.makeMove<false>(convertUciToMove(b, "e2e4"));
    expect(b.zobristHash(), 0x823c9b50fd114196, "Startpos e2e4");

    b.makeMove<false>(convertUciToMove(b, "d7d5"));
    expect(b.zobristHash(), 0x0756b94461c50fb0, "Startpos e2e4 d7d5");

    b.makeMove<false>(convertUciToMove(b, "e4e5"));
    expect(b.zobristHash(), 0x662fafb965db29d4, "Startpos e2e4 d7d5 e4e5");

    b.makeMove<false>(convertUciToMove(b, "f7f5"));
    expect(b.zobristHash(), 0x22a48b5a8e47ff78, "Startpos e2e4 d7d5 e4e5 f7f5");

    b.makeMove<false>(convertUciToMove(b, "e1e2"));
    expect(b.zobristHash(), 0x652a607ca3f242c1, "Startpos e2e4 d7d5 e4e5 f7f5 e1e2");

    b.makeMove<false>(convertUciToMove(b, "e8f7"));
    expect(b.zobristHash(), 0x00fdd303c946bdd9, "Startpos e2e4 d7d5 e4e5 f7f5 e1e2 e8f7");

    b.applyFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    b.makeMove<false>(convertUciToMove(b, "a2a4"));
    b.makeMove<false>(convertUciToMove(b, "b7b5"));
    b.makeMove<false>(convertUciToMove(b, "h2h4"));
    b.makeMove<false>(convertUciToMove(b, "b5b4"));
    b.makeMove<false>(convertUciToMove(b, "c2c4"));
    expect(b.zobristHash(), 0x3c8123ea7b067637, "a2a4 b7b5 h2h4 b5b4 c2c4");

    b.makeMove<false>(convertUciToMove(b, "b4c3"));
    b.makeMove<false>(convertUciToMove(b, "a1a3"));
    expect(b.zobristHash(), 0x5c3f9b829b279560, "a2a4 b7b5 h2h4 b5b4 c2c4 b4c3 a1a3");

    return true;
}
} // namespace Tests