# Customization Guideline

## Anatomy of Face

<img src="https://github.com/user-attachments/assets/0f9da4df-f5f6-48ce-adc6-ac0405041b6f" width=50% alt="anatomy">

`m5avatar::Face` consists of five components: 

- left eye
- right eye
- mouth
- left eyebrow
- right eyebrow

You can customize a face with replacing the components.
[examples/face-and-color/face-and-color.ino](../examples/face-and-color/face-and-color.ino) is an example of using and customizing faces.

## Face templates
Pre-assembled faces are available and defined in [src/faces/FaceTemplates.hpp](../src/faces/FaceTemplates.hpp)

|preview|face|eye|mouth|eyebrow|notes|
|:-:|:-|:-|:-|:-|:-|
|<img src="https://github.com/user-attachments/assets/5908e69f-9674-43df-a933-9f8d24fa488c/" width=20% alt="SimpleFace">|`SimpleFace`| `EllipseEye` | `RectMouth` | -- | Alternative  implementation of (Native) `Face`
|<img src="https://github.com/user-attachments/assets/5457eaec-a774-46f5-90dd-7ee1a3e13c03" width=20% alt="DoggyFace">|`DoggyFace`|`DoggyEye`|`DoggyMouth`|`RectEyebrow`|Alternative  implementation of `DogFace`|
|<img src="https://github.com/user-attachments/assets/0ddd047a-76bf-450f-8a32-d245fdc40380" width=20% alt="OmegaFace">|`OmegaFace`|`EllipseEye`|`OmegaMouth`|--||
|<img src="https://github.com/user-attachments/assets/fc0a5d3f-bf0d-4563-aa19-1e2d565e83aa" width=20% alt="GirlyFace">|`GirlyFace`|`GirlyEye`|`UShapeMouth`|`EllipseEyebrow`||





## Eyes

Predefined eye components are in [src/Eyes.hpp](../src/Eyes.hpp) and [src/Eyes.cpp](../src/Eyes.cpp)

- `EllipseEye` (Extended implement of `Eye`)
- `GirlyEye`
- `PinkDemonEye`
- `DoggyEye` (Alternative implement of `DogEye`)



## Mouth

Predefined mouth components are in [src/Mouths.hpp](../src/Mouths.hpp) and [src/Mouths.cpp](../src/Mouths.cpp)

- `RectMouth` (Alternative implement of `Mouth`)
- `OmegaMouth`
- `UShapeMouth`
- `DoggyMouth` (Alternative implement of `DogMouth`)

## Eyebrows

Predefined mouth components are in [src/EyeBrow.hpp](../src/EyeBrow.hpp) and [src/EyeBrow.cpp](../src/EyeBrow.cpp)

- `RectEyebrow`
- `EllipseEyebrow`
- `BowEyebrow`


## Notes

### Native files
- [src/Eye.h](../src/Eye.h) and [src/Eye.cpp](../src/Eye.cpp) : Native `Eye` code
- [src/Mouth.h](../src/Mouth.h) and [src/Mouth.cpp](../src/Mouth.cpp) : Native `Mouth` code
- [src/Eyeblow.h](../src/Eyeblow.h) and [src/Eyeblow.cpp](../src/Eyeblow.cpp) : Native `Eyeblow` code for Eyebrow
- [src/faces/DogFace.h](../src/faces/DogFace.h) : Native `DogFace` code
