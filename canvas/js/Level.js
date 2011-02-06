function Level() {
  /** STATE VARIABLES **/
  this.tiles = [];
  this.image = new Image();
  this.image.src = 'gfx/tiles.png';
  this.items = [];
  this.items.image = new Image();
  this.items.image.src = 'gfx/items.png';

  /** INITIALIZE **/
  //Create a random map for now
  for(var x=0; x<20; ++x) {
    this.tiles[x] = new Array(20);
    for(var y=0; y<20; ++y) {
      this.tiles[x][y] = Math.floor(Math.random() * 5);
      var r = Math.random();
      if(r < 0.1) {
        //Add a stabby
        this.items.push(new Item(1, x, y));
      } else if(r < 0.5) {
        //add a shiney
        this.items.push(new Item(0, x, y));
      }
    }
  }

  /** EXPORT MEMBER FUNCTIONS **/
  this.draw = draw;
  /** MEMBER FUNCTIONS **/
  function draw(context) {
    for(var x=0; x<20; ++x) {
      for(var y=0; y<20; ++y) {
        context.drawImage(this.image,
          1 + this.tiles[x][y] * 33, 1, 32, 32,
          x * 32, y * 32, 32, 32
        );
      }
    }
    //Now render items
    for(var i=0; i<this.items.length; ++i) {
      context.drawImage(this.items.image,
        this.items[i].type * 32, 0, 32, 32,
        this.items[i].x *32, this.items[i].y * 32, 32, 32
      );
    }
  }
}
