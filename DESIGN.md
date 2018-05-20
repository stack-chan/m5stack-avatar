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
