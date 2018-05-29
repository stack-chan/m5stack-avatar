# Design drafts

## face drawing

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

### Colors

context contains color palette for the face drawing.
it's internally an array of 8bit color.
It should contain at least two colors(primary, secondary)
User can add other colors to the array.
  
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

task...FreeRTOS like I/F
