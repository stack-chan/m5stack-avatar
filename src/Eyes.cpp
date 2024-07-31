#include "Eyes.hpp"

namespace m5avatar {
BaseEye::BaseEye(bool is_left) : BaseEye(36, 70, is_left) {}

BaseEye::BaseEye(uint16_t width, uint16_t height, bool is_left) {
    this->width_ = width;
    this->height_ = height;
    this->is_left_ = is_left;
}

void BaseEye::update(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    // common process for all standard eyes
    // update drawing parameters
    center_x_ = rect.getCenterX();
    center_y_ = rect.getCenterY();
    gaze_ = this->is_left_ ? ctx->getLeftGaze() : ctx->getRightGaze();
    ColorPalette *cp = ctx->getColorPalette();
    primary_color_ = ctx->getColorDepth() == 1 ? 1 : cp->get(COLOR_PRIMARY);
    secondary_color_ = ctx->getColorDepth() == 1
                           ? 1
                           : ctx->getColorPalette()->get(COLOR_SECONDARY);
    background_color_ =
        ctx->getColorDepth() == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);

    // offset computed from gaze direction
    shifted_x_ = center_x_ + gaze_.getHorizontal() * 8;
    shifted_y_ = center_y_ + gaze_.getVertical() * 5;
    open_ratio_ = this->is_left_ ? ctx->getLeftEyeOpenRatio()
                                 : ctx->getRightEyeOpenRatio();
    expression_ = ctx->getExpression();
}

void EllipseEye::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);
    if (open_ratio_ == 0 || expression_ == Expression::Sleepy) {
        // eye closed
        // NOTE: the center of closed eye is lower than the center of bbox
        canvas->fillRect(shifted_x_ - (this->width_ / 2),
                         shifted_y_ - 2 + this->height_ / 4, this->width_, 4,
                         primary_color_);
        return;
    } else if (expression_ == Expression::Happy) {
        auto wink_base_y = shifted_y_ + this->height_ / 4;
        uint32_t thickness = 4;
        canvas->fillEllipse(shifted_x_, wink_base_y + (1 / 8) * this->height_,
                            this->width_ / 2, this->height_ / 4 + thickness,
                            primary_color_);
        // mask
        canvas->fillEllipse(shifted_x_,
                            wink_base_y + (1 / 8) * this->height_ + thickness,
                            this->width_ / 2 - thickness,
                            this->height_ / 4 + thickness, background_color_);
        canvas->fillRect(shifted_x_ - this->width_ / 2,
                         wink_base_y + thickness / 2, this->width_ + 1,
                         this->height_ / 4 + 1, background_color_);
        return;
    }

    canvas->fillEllipse(shifted_x_, shifted_y_, this->width_ / 2,
                        this->height_ / 2, primary_color_);

    // note: you cannot define variable in switch scope
    int x0, y0, x1, y1, x2, y2;
    switch (expression_) {
        case Expression::Angry:
            x0 = shifted_x_ - width_ / 2;
            y0 = shifted_y_ - height_ / 2;
            x1 = shifted_x_ + width_ / 2;
            y1 = y0;
            x2 = this->is_left_ ? x0 : x1;
            y2 = shifted_y_ - height_ / 4;
            canvas->fillTriangle(x0, y0, x1, y1, x2, y2, background_color_);
            break;
        case Expression::Sad:
            x0 = shifted_x_ - width_ / 2;
            y0 = shifted_y_ - height_ / 2;
            x1 = shifted_x_ + width_ / 2;
            y1 = y0;
            x2 = this->is_left_ ? x1 : x0;
            y2 = shifted_y_ - height_ / 4;
            canvas->fillTriangle(x0, y0, x1, y1, x2, y2, background_color_);
            break;
        case Expression::Doubt:
            // top left
            x0 = shifted_x_ - width_ / 2;
            y0 = shifted_y_ - height_ / 2;
            // bottom right
            x1 = shifted_x_ + width_ / 2;
            y1 = shifted_y_ - height_ / 4;

            canvas->fillRect(x0, y0, x1 - x0, y1 - y0, background_color_);
            break;
        case Expression::Sleepy:
            break;

        default:
            break;
    }
}

void GirlyEye::drawEyeLid(M5Canvas *canvas) {
    // eyelid
    auto upper_eyelid_y = shifted_y_ - 0.8f * height_ / 2 +
                          (1.0f - open_ratio_) * this->height_ * 0.6;

    float eyelash_x0, eyelash_y0, eyelash_x1, eyelash_y1, eyelash_x2,
        eyelash_y2;
    eyelash_x0 = this->is_left_ ? shifted_x_ + 22 : shifted_x_ - 22;
    eyelash_y0 = upper_eyelid_y - 27;
    eyelash_x1 = this->is_left_ ? shifted_x_ + 26 : shifted_x_ - 26;
    eyelash_y1 = upper_eyelid_y;
    eyelash_x2 = this->is_left_ ? shifted_x_ - 10 : shifted_x_ + 10;
    eyelash_y2 = upper_eyelid_y;

    float tilt = 0.0f;
    float ref_tilt = open_ratio_ * M_PI / 6.0f;
    float bias;
    if (expression_ == Expression::Angry) {
        tilt = this->is_left_ ? -ref_tilt : ref_tilt;
    } else if (expression_ == Expression::Sad) {
        tilt = this->is_left_ ? ref_tilt : -ref_tilt;
    }
    bias = 0.2f * width_ * tilt / (M_PI / 6.0f);

    if ((open_ratio_ < 0.99f) || (abs(tilt) > 0.1f)) {
        // mask
        // top:shifted_y_ - this->height_ / 2
        // bottom: upper_eyelid_y
        float mask_top_left_x = shifted_x_ - (this->width_ / 2);
        float mask_top_left_y = shifted_y_ - 0.75f * this->height_;
        float mask_bottom_right_x = shifted_x_ + (this->width_ / 2);
        float mask_bottom_right_y = upper_eyelid_y;

        fillRectRotatedAround(canvas, mask_top_left_x, mask_top_left_y,
                              mask_bottom_right_x, mask_bottom_right_y, tilt,
                              shifted_x_, upper_eyelid_y, background_color_);

        // eyelid
        float eyelid_top_left_x = shifted_x_ - (this->width_ / 2) + bias;
        float eyelid_top_left_y = upper_eyelid_y - 4;
        float eyelid_bottom_right_x = shifted_x_ + (this->width_ / 2) + bias;
        float eyelid_bottom_right_y = upper_eyelid_y;

        fillRectRotatedAround(canvas, eyelid_top_left_x, eyelid_top_left_y,
                              eyelid_bottom_right_x, eyelid_bottom_right_y,
                              tilt, shifted_x_, upper_eyelid_y, primary_color_);

        eyelash_x0 += bias;
        eyelash_x1 += bias;
        eyelash_x2 += bias;
    }

    // eyelash
    rotatePointAround(eyelash_x0, eyelash_y0, tilt, shifted_x_, upper_eyelid_y);
    rotatePointAround(eyelash_x1, eyelash_y1, tilt, shifted_x_, upper_eyelid_y);
    rotatePointAround(eyelash_x2, eyelash_y2, tilt, shifted_x_, upper_eyelid_y);
    canvas->fillTriangle(eyelash_x0, eyelash_y0, eyelash_x1, eyelash_y1,
                         eyelash_x2, eyelash_y2, primary_color_);
}

void GirlyEye::overwriteOpenRatio() {
    switch (expression_) {
        case Expression::Doubt:
            open_ratio_ = 0.6f;
            break;

        case Expression::Sleepy:
            open_ratio_ = 0.0f;
            break;
    }
}

void GirlyEye::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);
    this->overwriteOpenRatio();
    auto wink_base_y = shifted_y_ + (1.0f - open_ratio_) * this->height_ / 4;

    uint32_t thickness = 4;
    if (expression_ == Expression::Happy) {
        canvas->fillEllipse(shifted_x_, wink_base_y + (1 / 8) * this->height_,
                            this->width_ / 2, this->height_ / 4 + thickness,
                            primary_color_);
        // mask
        canvas->fillEllipse(shifted_x_,
                            wink_base_y + (1 / 8) * this->height_ + thickness,
                            this->width_ / 2 - thickness,
                            this->height_ / 4 + thickness, background_color_);
        canvas->fillRect(shifted_x_ - this->width_ / 2,
                         wink_base_y + thickness / 2, this->width_,
                         this->height_ / 4, background_color_);
        // this->drawEyeLid(canvas);
        return;
    }
    // main eye
    if (open_ratio_ > 0.1f) {
        // bg
        canvas->fillEllipse(shifted_x_, shifted_y_, this->width_ / 2,
                            this->height_ / 2, primary_color_);

        uint16_t accent_color = M5.Lcd.color24to16(0x019E73);
        canvas->fillEllipse(shifted_x_, shifted_y_,
                            this->width_ / 2 - thickness,
                            this->height_ / 2 - thickness, accent_color);
        // upper half moon
        canvas->fillArc(shifted_x_, shifted_y_, width_ / 2, 0, 180.0f, 360.0f,
                        primary_color_);

        canvas->fillEllipse(shifted_x_, shifted_y_, this->width_ / 4,
                            this->height_ / 4, primary_color_);
        // high light
        canvas->fillEllipse(shifted_x_ - width_ / 6, shifted_y_ - height_ / 6,
                            width_ / 8, height_ / 8, 0xffffff);
    }
    this->drawEyeLid(canvas);
}

void PinkDemonEye::drawEyeLid(M5Canvas *canvas) {
    // eyelid
    auto upper_eyelid_y = shifted_y_ - 0.8f * height_ / 2 +
                          (1.0f - open_ratio_) * this->height_ * 0.6;

    float eyelash_x0, eyelash_y0, eyelash_x1, eyelash_y1, eyelash_x2,
        eyelash_y2;
    eyelash_x0 = this->is_left_ ? shifted_x_ + 22 : shifted_x_ - 22;
    eyelash_y0 = upper_eyelid_y - 27;
    eyelash_x1 = this->is_left_ ? shifted_x_ + 26 : shifted_x_ - 26;
    eyelash_y1 = upper_eyelid_y;
    eyelash_x2 = this->is_left_ ? shifted_x_ - 10 : shifted_x_ + 10;
    eyelash_y2 = upper_eyelid_y;

    float tilt = 0.0f;
    float ref_tilt = open_ratio_ * M_PI / 6.0f;
    if (expression_ == Expression::Angry) {
        tilt = this->is_left_ ? -ref_tilt : ref_tilt;
    } else if (expression_ == Expression::Sad) {
        tilt = this->is_left_ ? ref_tilt : -ref_tilt;
    }

    if ((open_ratio_ < 0.99f) || (abs(tilt) > 0.1f)) {
        // mask
        // top:shifted_y_ - this->height_ / 2
        // bottom: upper_eyelid_y
        float mask_top_left_x = shifted_x_ - (this->width_ / 2);
        float mask_top_left_y = shifted_y_ - 0.75f * this->height_;
        float mask_bottom_right_x = shifted_x_ + (this->width_ / 2);
        float mask_bottom_right_y = upper_eyelid_y;

        fillRectRotatedAround(canvas, mask_top_left_x, mask_top_left_y,
                              mask_bottom_right_x, mask_bottom_right_y, tilt,
                              shifted_x_, upper_eyelid_y, background_color_);

        // eyelid
        float eyelid_top_left_x = shifted_x_ - (this->width_ / 2);
        float eyelid_top_left_y = upper_eyelid_y - 4;
        float eyelid_bottom_right_x = shifted_x_ + (this->width_ / 2);
        float eyelid_bottom_right_y = upper_eyelid_y;

        fillRectRotatedAround(canvas, eyelid_top_left_x, eyelid_top_left_y,
                              eyelid_bottom_right_x, eyelid_bottom_right_y,
                              tilt, shifted_x_, upper_eyelid_y, primary_color_);
    }

    // eyelash
    rotatePointAround(eyelash_x0, eyelash_y0, tilt, shifted_x_, upper_eyelid_y);
    rotatePointAround(eyelash_x1, eyelash_y1, tilt, shifted_x_, upper_eyelid_y);
    rotatePointAround(eyelash_x2, eyelash_y2, tilt, shifted_x_, upper_eyelid_y);
}

void PinkDemonEye::overwriteOpenRatio() {
    switch (expression_) {
        case Expression::Doubt:
            open_ratio_ = 0.6f;
            break;

        case Expression::Sleepy:
            open_ratio_ = 0.0f;
            break;
    }
}

void PinkDemonEye::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);
    this->overwriteOpenRatio();
    uint32_t thickness = 8;

    // main eye
    if (open_ratio_ > 0.1f) {
        // bg
        canvas->fillEllipse(shifted_x_, shifted_y_, this->width_ / 2,
                            this->height_ / 2, primary_color_);
        uint16_t accent_color = M5.Lcd.color24to16(0x00A1FF);
        canvas->fillEllipse(shifted_x_, shifted_y_,
                            this->width_ / 2 - thickness,
                            this->height_ / 2 - thickness, accent_color);
        // upper
        uint16_t w1 = width_ * 0.92f;
        uint16_t h1 = this->height_ * 0.69f;
        uint16_t y1 = shifted_y_ - this->height_ / 2 + h1 / 2;
        canvas->fillEllipse(shifted_x_, y1, w1 / 2, h1 / 2, primary_color_);
        // high light
        uint16_t w2 = width_ * 0.577f;
        uint16_t h2 = this->height_ * 0.4f;
        uint16_t y2 = shifted_y_ - this->height_ / 2 + thickness + h2 / 2;

        canvas->fillEllipse(shifted_x_, y2, w2 / 2, h2 / 2, 0xffffff);
    }
    this->drawEyeLid(canvas);
}

void DoggyEye::draw(M5Canvas *canvas, BoundingRect rect, DrawContext *ctx) {
    this->update(canvas, rect, ctx);

    if (this->open_ratio_ == 0) {
        // eye closed
        canvas->fillRect(center_x_ - 15, center_y_ - 2, 30, 4, primary_color_);
        return;
    }
    canvas->fillEllipse(center_x_, center_y_, 30, 25, primary_color_);
    canvas->fillEllipse(center_x_, center_y_, 28, 23, background_color_);

    canvas->fillEllipse(shifted_x_, shifted_y_, 18, 18, primary_color_);
    canvas->fillEllipse(shifted_x_ - 3, shifted_y_ - 3, 3, 3,
                        background_color_);
}

}  // namespace m5avatar
