#include <Avatar.h>
#include <M5Unified.h>

#include <faces/FaceTemplates.hpp>

using namespace m5avatar;

Avatar avatar;

Face* faces[6];
const int num_faces = sizeof(faces) / sizeof(Face*);
int face_idx = 0;  // face index

const Expression expressions[] = {Expression::Angry, Expression::Sleepy,
                                  Expression::Happy, Expression::Sad,
                                  Expression::Doubt, Expression::Neutral};
const int num_expressions = sizeof(expressions) / sizeof(Expression);
int idx = 0;

ColorPalette* color_palettes[5];
const int num_palettes = sizeof(color_palettes) / sizeof(ColorPalette*);
int palette_idx = 0;

bool isShowingQR = false;

// an example of customizing
class MyCustomFace : public Face {
   public:
    MyCustomFace()
        : Face(new UShapeMouth(44, 44, 0, 16), new BoundingRect(222, 160),
               // right eye, second eye arg is center position of eye
               new EllipseEye(32, 32, false), new BoundingRect(163, 64),
               //  left eye
               new EllipseEye(32, 32, true), new BoundingRect(163, 256),
               // right eyebrow
               // BowEyebrow's origin is the center of bow (arc)
               new BowEyebrow(64, 20, false),
               new BoundingRect(163, 64),  // (y,x)
                                           //  left eyebrow
               new BowEyebrow(64, 20, true), new BoundingRect(163, 256)) {}
};

void setup() {
    M5.begin();
    M5.Lcd.setBrightness(30);
    M5.Lcd.clear();

    faces[0] = avatar.getFace();  // native face
    faces[1] = new DoggyFace();
    faces[2] = new OmegaFace();
    faces[3] = new GirlyFace();
    faces[4] = new PinkDemonFace();
    faces[5] = new MyCustomFace();

    color_palettes[0] = new ColorPalette();
    color_palettes[1] = new ColorPalette();
    color_palettes[2] = new ColorPalette();
    color_palettes[3] = new ColorPalette();
    color_palettes[4] = new ColorPalette();
    color_palettes[1]->set(COLOR_PRIMARY,
                           M5.Lcd.color24to16(0x383838));  // eye
    color_palettes[1]->set(COLOR_BACKGROUND,
                           M5.Lcd.color24to16(0xfac2a8));  // skin
    color_palettes[1]->set(COLOR_SECONDARY,
                           TFT_PINK);  // cheek
    color_palettes[2]->set(COLOR_PRIMARY, TFT_YELLOW);
    color_palettes[2]->set(COLOR_BACKGROUND, TFT_DARKCYAN);
    color_palettes[3]->set(COLOR_PRIMARY, TFT_DARKGREY);
    color_palettes[3]->set(COLOR_BACKGROUND, TFT_WHITE);
    color_palettes[4]->set(COLOR_PRIMARY, TFT_RED);
    color_palettes[4]->set(COLOR_BACKGROUND, TFT_PINK);

    avatar.init(8);  // start drawing w/ 8bit color mode
    avatar.setColorPalette(*color_palettes[0]);
}

void loop() {
    M5.update();
    // M5Stack Core's button layout:
    // -----------
    // |         |
    // |         |
    // -----------
    // [A] [B] [C]
    if (M5.BtnA.wasPressed()) {
        avatar.setFace(faces[face_idx]);
        face_idx = (face_idx + 1) % num_faces;  // loop index
    }
    if (M5.BtnB.wasPressed()) {
        avatar.setColorPalette(*color_palettes[palette_idx]);
        palette_idx = (palette_idx + 1) % num_palettes;
    }
    if (M5.BtnC.wasPressed()) {
        avatar.setExpression(expressions[idx]);
        idx = (idx + 1) % num_expressions;
    }
}
