# Design drafts

## face drawing

* Face has its size and position
* Face manages color palette
* drawing are cascaded
 * Avatar
  * EyeR
  * EyeL
  * Mouth
* drawing has context: common parameters of the face
 * transforms
  * position
  * rotation 
  * scale
 * colors
  * color palette (array of 8bit color)
 * statuses
  * breath
  * focus point
  * expression

```cpp
ColorPalette cp = this->colorPalette;
uint32_t primary = cp.get(PRIMARY_COLOR);
uint32_t secondary = cp.get(SECONDARY_COLOR);
```

### Colors

context contains color palette for the face drawing.
it's internally an array of 8bit color.
It should contain at least two colors(primary, secondary)
User can add other colors to the array.
User can use colors from their draw function but not necessary.
  
### discussion

* Should parents know its children?
* Should renderers be separated from face parts themselves? 
 * Eye
  * setOpenRatio
  * setGaze
 * Renderer
  * draw

### tasks

* removeTask(task)
* addTask(task)
* getTasks()

task...FreeRTOS like I/F

task is managed by avatar using its name.
all taskname are unique so that avatar cannot have tasks with the same name.

Task {
  members:
  name
  run
}

