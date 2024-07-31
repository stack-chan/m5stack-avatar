/**
 * @file DrawingUtils.hpp
 * @author botamochi (botamochi6277@gmail.com)
 * @brief drawing utils including geometry handling
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef M5AVATAR_DRAWING_UTILS_HPP_
#define M5AVATAR_DRAWING_UTILS_HPP_

#include <BoundingRect.h>
#include <DrawContext.h>
#include <Drawable.h>

namespace m5avatar {
void rotatePoint(float &x, float &y, float angle);

void rotatePointAround(float &x, float &y, float angle, float cx, float cy);

void fillRotatedRect(M5Canvas *canvas, uint16_t cx, uint16_t cy, uint16_t w,
                     uint16_t h, float angle, uint16_t color);

void fillRectRotatedAround(M5Canvas *canvas, float top_left_x, float top_left_y,
                           float bottom_right_x, float bottom_right_y,
                           float angle, uint16_t cx, uint16_t cy,
                           uint16_t color);

}  // namespace m5avatar

#endif