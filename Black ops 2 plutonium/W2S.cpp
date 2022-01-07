#include "W2S.h"

int VecDistance(Vec3 from, Vec3 to){
    return (int)sqrt(((to.x - from.x) * (to.x - from.x)) +((to.y - from.y) * (to.y - from.y)) +((to.z - from.z) * (to.z - from.z)));
}

bool WorldToScreen(Vec3 pos, ImVec2& screen) {
    float matrix[16];
    memcpy(matrix, (void*)0x01065F40, sizeof(matrix));
    Vec4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
    clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
    clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
    clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

    if (clipCoords.w < 0.1f)
        return false;


    Vec3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (RefDef->Screen.x / 2 * NDC.x) + (NDC.x + RefDef->Screen.x / 2);
    screen.y = -(RefDef->Screen.y / 2 * NDC.y) + (NDC.y + RefDef->Screen.y / 2);
    return true;
}