
#pragma once
#include "MoveDirections.hpp"
#include <string>
#include "../global.hpp"

/**
 *           5
 *
 *   4       1        3
 *
 *           2
 *
 *           6
*/

enum class DiceSide{
    NORTH, SOUTH, WEST, EAST, TOP, BOTTOM
};

enum class DiceFaceDirection{
    UP, DOWN, LEFT, RIGHT
};

class DiceData{
public:
    /// default cube is 1up, 5north, 3west
    DiceData();
    int rotate(DiceRollDirection direction, int side = 0);

    /// get dice side facing direction
    [[nodiscard]] int getSide(DiceSide side) const;

    /// get facing direction of side
    [[nodiscard]] DiceSide getSideFacing(int side) const;

    [[nodiscard]] std::string toString() const;

    /**
     * get the side of the cube where the top left corner is relative to
     * example: the anchor of side 1 is 5, because rotating the cube like above, you can see what is meant with top left corner of side 1
     * @param side side to which you want to get the anchor from
     * @return
     */
    static int getAnchorSideOfTopLeftCorner(int side);

    /**
     * get global orientation of side when looking straight on side
     * @param side
     * @return get rotation of side on global space (no result for top and bottom of dice)
     */
    DiceFaceDirection getDiceSideRotation(int side);

    int getSideWhenMovingInDirX(int side, DiceFaceDirection direction);

private:
    int up, north, west;

    static int getOpposite(int side);
};


