// Template for your puckman bot

var puckman = require('./puckman.js');

/*
 * Return one element of the array a at random.
 */

function randomChoice(a) {
    return a[Math.floor(Math.random() * a.length)];
}

function which_move(board) {

    // Choose a legal move randomly.
    // Note that board.moves will produce [NORTH] if there are no
    // legal moves available.

    return randomChoice(board.moves());
}

// you do not need to modify this part
puckman.play(which_move);
