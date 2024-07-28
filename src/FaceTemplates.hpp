#ifndef M5AVATAR_FACES_HPP_
#define M5AVATAR_FACES_HPP_

#include "Eyebrows.hpp"
#include "Eyes.hpp"
#include "Face.h"
#include "Mouths.hpp"

namespace m5avatar {

/**
 * @brief face template for "OωO" face
 *
 */
class OmegaFace : public Face {
   public:
    OmegaFace()
        : Face(new OmegaMouth(), new BoundingRect(225, 160),
               // right eye, second eye arg is center position of eye in (y,x)
               new EllipseEye(false), new BoundingRect(165, 84),
               //  left eye
               new EllipseEye(true), new BoundingRect(165, 84 + 154),
               //  hide eye brows with setting these height zero
               new EllipseEyebrow(15, 0, false), new BoundingRect(67, 96),
               new EllipseEyebrow(15, 0, true), new BoundingRect(72, 230)) {}
};

class GirlyFace : public Face {
   public:
    GirlyFace()
        : Face(new UShapeMouth(44, 44, 0, 16), new BoundingRect(222, 160),
               // right eye, second eye arg is center position of eye
               new GirlyEye(84, 84, false), new BoundingRect(163, 64),
               //  left eye
               new GirlyEye(84, 84, true), new BoundingRect(163, 256),

               // right eyebrow
               new EllipseEyebrow(36, 20, false),
               new BoundingRect(97 + 10, 84 + 18),  // (y,x)
                                                    //  left eyebrow
               new EllipseEyebrow(36, 20, true),
               new BoundingRect(107, 200 + 18)) {}
};

class GirlyFace2 : public Face {
   public:
    GirlyFace2()
        : Face(new UShapeMouth(44, 44, 0, 16), new BoundingRect(222, 160),
               // right eye, second eye arg is center position of eye
               new GirlyEye(84, 84, false), new BoundingRect(163, 64),
               //  left eye
               new GirlyEye(84, 84, true), new BoundingRect(163, 256),

               // right eyebrow
               new BowEyebrow(160, 160, false),
               new BoundingRect(163, 64),  // (y,x)
                                           //  left eyebrow
               new BowEyebrow(160, 160, true), new BoundingRect(163, 256)) {}
};

class PinkDemonFace : public Face {
   public:
    PinkDemonFace()
        : Face(new UShapeMouth(64, 64, 0, 16), new BoundingRect(214, 160),
               // right eye, second eye arg is center position of eye
               new PinkDemonEye(52, 134, false), new BoundingRect(134, 106),
               //  left eye
               new PinkDemonEye(52, 134, true), new BoundingRect(134, 218),

               //  hide eye brows with setting these height zero
               new Eyeblow(15, 0, false), new BoundingRect(67, 96),
               new Eyeblow(15, 0, true), new BoundingRect(72, 230)) {}
};

}  // namespace m5avatar

#endif  // M5AVATAR_FACES_HPP_
