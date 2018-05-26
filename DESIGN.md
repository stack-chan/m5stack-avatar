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
 * statuses
  * breath
  * focus point
  * expression
  
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
