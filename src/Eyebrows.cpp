#include "Eyebrows.hpp"

namespace m5avatar {

BaseEyebrow::BaseEyebrow(bool is_left) : BaseEyebrow(30, 20, is_left) {}

BaseEyebrow::BaseEyebrow(uint16_t width, uint16_t height, bool is_left) {
    this->width_ = width;
    this->height_ = height;
    this->is_left_ = is_left;
}

void BaseEyebrow::update(M5Canvas *canvas, BoundingRect rect,
                         DrawContext *ctx) {
    // common process for all standard eyebrows
    // update drawing parameters
    ColorPalette *cp = ctx->getColorPalette();
    primary_color_ = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
    secondary_color_ = ctx->getColorDepth() == 1
                           ? 1
                           : ctx->getColorPalette()->get(COLOR_SECONDARY);
    background_color_ =
        ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);
    center_x_ = rect.getCenterX();
    center_y_ = rect.getCenterY();
    expression_ = ctx->getExpression();
}

void EllipseEyebrow::draw(M5Canvas *canvas, BoundingRect rect,
                          DrawContext *ctx) {
    this->update(canvas, rect, ctx);
    if (width_ == 0 || height_ == 0) {
        return;  // draw nothing
    }

    canvas->fillEllipse(center_x_, center_y_, this->width_ / 2,
                        this->height_ / 2, primary_color_);
}

void BowEyebrow::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);
    uint8_t thickness = 4;

    float angle0 = is_left_ ? 180.0f + 35.0f : 180.0f + 45.0f;
    float stroke_angle = 100.0f;
    canvas->fillArc(center_x_, center_y_, width_ / 2, width_ / 2 - thickness,
                    angle0, angle0 + stroke_angle, primary_color_);
}

void RectEyebrow::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);

    if (width_ == 0 || height_ == 0) {
        return;
    }
    float angle = 0.0f;
    if (expression_ == Expression::Angry) {
        angle = is_left_ ? -M_PI / 6.0f : M_PI / 6.0f;
    }
    if (expression_ == Expression::Sad) {
        angle = is_left_ ? M_PI / 6.0f : -M_PI / 6.0f;
    }

    fillRotatedRect(canvas, center_x_, center_y_, width_, height_, angle,
                    primary_color_);
}

}  // namespace m5avatar
