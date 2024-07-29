/**
 * @file Eyebrows.hpp
 * @author botamochi (botamochi6277@gmail.com)
 * @brief Eyebrow components
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef M5AVATAR_EYEBROWS_HPP_
#define M5AVATAR_EYEBROWS_HPP_

#include <BoundingRect.h>
#include <DrawContext.h>
#include <Drawable.h>

#include "DrawingUtils.hpp"
namespace m5avatar {
class BaseEyebrow : public Drawable {
   protected:
    uint16_t height_;
    uint16_t width_;
    bool is_left_;

    // caches
    uint16_t primary_color_;
    uint16_t secondary_color_;
    uint16_t background_color_;
    int16_t center_x_;
    int16_t center_y_;
    Expression expression_;

   public:
    BaseEyebrow(bool is_left);
    BaseEyebrow(uint16_t width, uint16_t height, bool is_left);
    void update(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

// Maro Mayu
class EllipseEyebrow : public BaseEyebrow {
   public:
    using BaseEyebrow::BaseEyebrow;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class BowEyebrow : public BaseEyebrow {
   public:
    using BaseEyebrow::BaseEyebrow;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class RectEyebrow : public BaseEyebrow {
   public:
    using BaseEyebrow::BaseEyebrow;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

}  // namespace m5avatar

#endif