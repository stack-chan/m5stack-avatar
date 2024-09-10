#include "DrawingUtils.hpp"

namespace m5avatar {
void rotatePoint(float &x, float &y, float angle) {
    float tmp;
    tmp = x * cosf(angle) - y * sinf(angle);
    x = tmp;
    tmp = x * sinf(angle) + y * cosf(angle);
    y = tmp;
}

void rotatePointAround(float &x, float &y, float angle, float cx, float cy) {
    float tmp_x = x - cx;
    float tmp_y = y - cy;
    rotatePoint(tmp_x, tmp_y, angle);  // rotate around origin
    x = tmp_x + cx;
    y = tmp_y + cy;
}

void fillRotatedRect(M5Canvas *canvas, uint16_t cx, uint16_t cy, uint16_t w,
                     uint16_t h, float angle, uint16_t color) {
    float top_left_x = cx - w / 2;
    float top_left_y = cy - h / 2;

    float top_right_x = cx + w / 2;
    float top_right_y = cy - h / 2;

    float bottom_left_x = cx - w / 2;
    float bottom_left_y = cy + h / 2;

    float bottom_right_x = cx + w / 2;
    float bottom_right_y = cy + h / 2;

    // rotate vertex
    rotatePointAround(top_left_x, top_left_y, angle, cx, cy);
    rotatePointAround(top_right_x, top_right_y, angle, cx, cy);
    rotatePointAround(bottom_left_x, bottom_left_y, angle, cx, cy);
    rotatePointAround(bottom_right_x, bottom_right_y, angle, cx, cy);

    canvas->fillTriangle(top_left_x, top_left_y, top_right_x, top_right_y,
                         bottom_right_x, bottom_right_y, color);
    canvas->fillTriangle(top_left_x, top_left_y, bottom_right_x, bottom_right_y,
                         bottom_left_x, bottom_left_y, color);
}

void fillRectRotatedAround(M5Canvas *canvas, float top_left_x, float top_left_y,
                           float bottom_right_x, float bottom_right_y,
                           float angle, uint16_t cx, uint16_t cy,
                           uint16_t color) {
    float top_right_x = bottom_right_x;
    float top_right_y = top_left_y;

    float bottom_left_x = top_left_x;
    float bottom_left_y = bottom_right_y;

    rotatePointAround(top_left_x, top_left_y, angle, cx, cy);
    rotatePointAround(top_right_x, top_right_y, angle, cx, cy);
    rotatePointAround(bottom_left_x, bottom_left_y, angle, cx, cy);
    rotatePointAround(bottom_right_x, bottom_right_y, angle, cx, cy);

    canvas->fillTriangle(top_left_x, top_left_y, top_right_x, top_right_y,
                         bottom_right_x, bottom_right_y, color);
    canvas->fillTriangle(top_left_x, top_left_y, bottom_right_x, bottom_right_y,
                         bottom_left_x, bottom_left_y, color);
}

}  // namespace m5avatar