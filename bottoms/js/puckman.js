// If you want to use this file, make sure to include it in your
// submission. You may modify it and submit the modified copy, or you
// may discard it and roll your own.

/**
 * Provided code for the JavaScript starter package
 *
 * See the example bots randbot.js to get started
 */

var sys = require('sys');

exports.EMPTY = ' ';
exports.DOT = '.';
exports.POWERPIL = 'O';
exports.IMPASSIBLE = '+';
exports.WALL = exports.IMPASSIBLE;
exports.GHOST = '#';
exports.ME = 'C';
exports.ME_POWER = '@';
exports.THEM = 'P';
exports.THEM_POWER = 'S'; 
exports.UP = 'U';
exports.DOWN = 'D';
exports.LEFT = 'L';
exports.RIGHT = 'R';

exports.DIRECTIONS = [exports.UP, exports.DOWN, exports.LEFT, exports.RIGHT];

/* Report an error and exit. */

function invalid_input(message) {
    sys.error("Invalid input: " + message);
    process.exit(1);
}

/* Read stdin, and call the supplied callback function
 * for each complete line of input that is read.
 */

function forEachLineOfInput(callback) {
  var buf = "";
  var stdin = process.openStdin();
  stdin.setEncoding('ascii')
  stdin.on("data",
      function (input) {
          var index, line;
          buf = buf + input;
          while ((index = buf.indexOf('\n')) >= 0) {
              line = buf.substring(0, index+1);
              buf = buf.substring(index+1);
              callback(line);
          }
      }
  );
}

/*
 * play the game. Repeatedly read a board from stdin and then
 * call the moveFn callback function with a "board" object.
 */

exports.play = function(moveFn) {
  var lineNumber = 0;
  var width = 0;
  var height = 0;
  var data = "";
  forEachLineOfInput(
      function (line) {
          var dim;
          line = line.replace(/[\r\n]*$/g,''); // Remove end-of-line chars if present
          if (lineNumber === 0) {
              width = parseInt(line,10);
              height = width;
              if (width <= 0 || isNaN(width) || height <= 0 || isNaN(height)) {
                  invalid_input("expected width, height on first line, got \"" + line + "\"");
              }
          } else {
	      /* Check to make sure the line length is correct. Either require one line of width or line of width*width [i.e. all data at once] */
              if (line.length != width && line.length != width*width) {
                  invalid_input("malformed board, line wrong length:" + line.length);
              }
              data = data + line;
              if (lineNumber == height || line.length == width*width) {
                  process.stdout.write(moveFn(
                  /* The Board object */
                  {
                    /* width of the board */
                    "width": width,
                    /* height of the board */
                    "height": height,
                    /* the raw data of the board as one long string */
                    "data": data,
                    /* Convert a (y, x) coordinate into an index into the data string. */
                    "YXtoCoord": function (y, x) {
                            if (x < 0 || x >= this.width || y < 0 || y >= this.height ) {
                                return -1;
                            }
                            return y * this.width + x;
                        },
                    /* Extract the x value of a coordinate */
                    "coordX": function(coord) {
                            var y = Math.floor(coord / this.width);
                            return coord - y * this.width;
                        },
                    /* Extract the y value of a coordinate */
                    "coordY": function(coord) {
                            return Math.floor(coord / this.width);
                        },
                    /* Look up the given (y, x) coord in the data string. */
                    "atYX": function (y, x) {
                            return this.data.charAt(this.YXToCoord(y, x));
                        },
                    /* Look up the given index in the data string. */
                    "at": function (coord) {
                            if (this.isOutOfBounds(coord)) {
                                return exports.IMPASSIBLE;
                            }
                            return this.data.charAt(coord);
                        },
                    /* Is a given coordinate out of bounds? */
                    "isOutOfBounds": function (coord) {
                            return coord < 0 || coord >= this.data.length;
                        },
                    /* Find the index of a given element. Throws an exception if missing. */
                    "find": function (item) {
                            var index = this.data.indexOf(item);
                            if (index < 0) {
                                throw "Not found";
                            }
                            return index;
                        },
		    "findOneOf" : function (item1,item2) {
			var index = this.data.indexOf(item1);
			if (index < 0) {
			    index = this.data.indexOf(item2);
			}
			if (index < 0) {
			    throw "Not found";
			}
			return index;
		    },
                    /* Return the index of player 1, also known as "me". */
                    "me": function () {
			return this.findOneOf(exports.ME,exports.ME_POWER);
                        },
                    /* Return the index of player 2, also known as "them". */
                    "them": function () {
			return this.find(exports.THEM,export.THEM_POWER);
                        },
		    "havePower" : function () {
			var index = this.data.indexOf(exports.ME_POWER);
			return !(index < 0);
		    },
                    /* Return true if the given index is passable.
                     * out-of-bounds coordinates are not passible.
                     */
                    "passable": function (index) {
                            if (this.isOutOfBounds(index)) {
                                return false;
                            }
                            return (this.data[index] == exports.EMPTY || 
				    this.data[index] == exports.DOT ||
				    this.data[index] == exports.POWERPILL ||
				    (this.havePower() && (this.data[index] == exports.THEM)));
                        },
                    /* Compute a new index that is in a relative offset from a given origin.
                     * If you don't pass in an origin, it defaults to "me".
                     * If the new index would cross a boundary of the map
                     * the return index is -1.
                     */
                    "rel": function (direction, origin) {
                            if (origin === undefined) {
                                origin = this.me();
                            }
                            if (direction == exports.UP) {
                                if (origin < this.width) {
                                    return -1;
                                }
                                return origin - this.width;
                            } else if (direction == exports.DOWN) {
                                if (origin >= this.data.length - this.width) {
                                    return -1;
                                }
                                return origin + this.width;
                            } else if (direction == exports.RIGHT) {
                                if (this.coordX(origin) == this.width - 1) {
                                    return -1;
                                }
                                return origin + 1;
                            } else if (direction == exports.LEFT) {
                                if (this.coordX(origin) === 0) {
                                    return -1;
                                }
                                return origin - 1;
                            } else {
                                throw "Invalid direction";
                            }
                         },
                     /* Compute all four adjacent locations to a given origin.
                        If the given location is at an edge, some of the adjacent
                        data will become -1.
                      */
                     "adjacent": function (origin) {
                             return [this.rel(exports.UP, origin),
                                 this.rel(exports.DOWN, origin),
                                 this.rel(exports.LEFT, origin),
                                 this.rel(exports.RIGHT, origin)];
                          },
                      /* Return all the possible legal moves from the player's current
                         location. If there are no legal moves, return [puckman.UP], just
                         to make it easier for simple algorithms.
                       */
                      "moves": function() {
                              var meCoord = this.me();
                              var adjacents = this.adjacent(meCoord);
                              var moves = [];
                              var i;
                              var coord;
                              var dir;
                              for (i = 0; i < adjacents.length; i++) {
                                  dir = exports.DIRECTIONS[i];
                                  coord = adjacents[i];
                                  if (this.passable(coord)) {
                                      moves.push(dir);
                                  }
                              }
                              if (moves.length === 0) {
                                  // it seems we have already lost
                                  return [exports.UP];
                              }
                              return moves;
                          }
                  }));
                  // Reset our accumulators.
                  lineNumber = -1;
                  data = "";
              }
          }
          lineNumber += 1;
      });
};
