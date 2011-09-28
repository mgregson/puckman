/** An ActorEntity are the characters that are animated **/

function ActorEntity(name, image) {
  this.name = name;
  this.image = new Image();
  this.image.src = image;
  this.dir = DOWN;          //Which direction the entity is facing
  this.frame = 0;           //Which frame in the current animation we're on
  this.numFrames = 3;       //How many frames in each animation
  this.frameTime = 0;       //How long on the current frame
  this.frameDuration = 200; //How long each frame should last
  this.x = 0;
  this.y = 0;

  /** EXPORT METHODS **/
  this.update = update;
  this.draw = draw;


  /** CLASS FUNCTIONS **/
  function update(delta) {
    var r = Math.random();
    if(r < 0.01) {
       this.dir = Math.floor(Math.random()*4);
    }
    //update animation
    this.frameTime += delta;
    while(this.frameTime > this.frameDuration) {
      this.frame = (this.frame + 1) % this.numFrames;
      this.frameTime -= this.frameDuration;
    }
  }

  function draw(context) {
    //Draw the entity at the current frame and direction.
    context.drawImage(this.image,
      this.frame * 32, this.dir * 32, 32, 32,
      this.x * 32, this.y * 32, 32, 32
    );
  }
}
