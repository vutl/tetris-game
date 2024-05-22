#include "colors.h"

const Color yellow = {253, 249, 0, 255};
const Color green = {0, 228, 48, 255};
const Color skyBlue = {102, 191, 255, 255};
const Color violet = {135, 60, 190, 255};
const Color beige = {211, 176, 131, 255};
const Color maroon = {190, 33, 55, 255};
const Color pink = {255, 109, 194, 255};
const Color orange = {255, 161, 0, 255};
extern const Color lightBlue = {55, 85, 162, 255};
extern const Color darkBlue = {44, 44, 127, 255};

std::vector<Color> GetCellColors()
{
    return {yellow, green, skyBlue, violet, beige, maroon, pink, orange, lightBlue, yellow};
}