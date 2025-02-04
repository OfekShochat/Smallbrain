#pragma once
#include "tests.h"

namespace Tests
{
inline void testAllDraw()
{
    Board b;

    // KBvkb same colour
    b.applyFen("8/2k1b3/8/8/8/4B3/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "KBvkb same colour");

    // KBvkb different colour
    b.applyFen("8/2k1b3/8/8/8/5B2/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::NONE,
           "KBvkb different colour");

    // Kvkb
    b.applyFen("8/2k1b3/8/8/8/8/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "Kvkb");

    // KBvk
    b.applyFen("8/2k1B3/8/8/8/8/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "KBvk");

    // KNvk
    b.applyFen("8/2k1N3/8/8/8/8/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "KNvk");

    // Kvkn
    b.applyFen("8/2k1n3/8/8/8/8/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "Kvkn");

    // Kvk
    b.applyFen("8/2k5/8/8/8/8/2K5/8 w - - 0 1");
    expect(b.isDrawn(b.isSquareAttacked(~b.sideToMove, b.KingSQ(b.sideToMove))), Result::DRAWN, "Kvk");
}
} // namespace Tests
