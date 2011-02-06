eval ('ActorEntity.js');

/** State variables for the ghost **/
var DOWN  = 0;
var LEFT  = 1;
var RIGHT = 2;
var UP    = 3;
var FRAMETIME = 20;

var level = new Level();
var ghost = new ActorEntity('Larry', 'gfx/ghost.png');
var ARGS = {};

/*** Main game functions ***/
function init() {
  setInterval(draw, FRAMETIME);
  var url = window.location.toString();
  url.match(/\?(.+)$/);
  url = RegExp.$1;

  var params = url.split('&');
  for(var i=0; i<params.length; ++i) {
    var t = params[i].split('=');
    ARGS[t[0]] = t[1];
  }
  loadContest();
}

function loadContest() {
  alert('Loading contest ' + ARGS['contest_id']);
}

function draw() {
  var canvas = document.getElementById("canvas");
  var context = canvas.getContext("2d");
  context.clearRect(0,0,800,600);
  ghost.update(FRAMETIME);
  level.draw(context);
  ghost.draw(context);
}
