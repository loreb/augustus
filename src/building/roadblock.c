#include "building/roadblock.h"

#include "building/building.h"
#include "building/type.h"





void building_roadblock_set_permission(roadblock_permission p, building* b) {
    if (building_type_is_roadblock(b->type)) {
        int permission_bit = 1 << p;
        b->subtype.roadblock_exceptions ^= permission_bit;
    }
}

int building_roadblock_get_permission(roadblock_permission p, building* b) {
    if (!building_type_is_roadblock(b->type)) {
        return 0;
    }
    int permission_bit = 1 << p;
    return (b->subtype.roadblock_exceptions & permission_bit);
}

int building_type_is_roadblock(building_type type)
{
    switch (type) {
        case BUILDING_ROADBLOCK:
        case BUILDING_GARDEN_WALL_GATE:
            return 1;
        default:
            return 0;
    }
}
