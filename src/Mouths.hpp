/**
 * @file Mouths.hpp
 * @author botamochi (botamochi6277@gmail.com)
 * @brief Mouth components
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef M5AVATAR_MOUTHS_HPP_
#define M5AVATAR_MOUTHS_HPP_

#include <BoundingRect.h>
#include <DrawContext.h>
#include <Drawable.h>
#include <Face.h>

namespace m5avatar {

class BaseMouth : public Drawable {
   protected:
    uint16_t min_width_;
    uint16_t max_width_;
    uint16_t min_height_;
    uint16_t max_height_;

    // caches for drawing
    int16_t center_x_;
    int16_t center_y_;
    uint16_t primary_color_;
    uint16_t secondary_color_;
    uint16_t background_color_;
    float open_ratio_;
    float breath_;
    Expression expression_;

   public:
    BaseMouth();
    BaseMouth(uint16_t min_width, uint16_t max_width, uint16_t min_height,
              uint16_t max_height);

    void update(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class RectMouth : public BaseMouth {
   public:
    using BaseMouth::BaseMouth;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class OmegaMouth : public BaseMouth {
   public:
    using BaseMouth::BaseMouth;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class UShapeMouth : public BaseMouth {
   public:
    using BaseMouth::BaseMouth;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

class DoggyMouth : public BaseMouth {
   public:
    using BaseMouth::BaseMouth;
    void draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx);
};

}  // namespace m5avatar

#endif