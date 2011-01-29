#ifndef __DEFINES_H__
#define __DEFINES_H__

/* These describe the world.
 */
#define EMPTY  ' '
#define WALL   '+'
#define PILL   'O'
#define DOT    '.'
#define GHOST  '&'
#define SELF   'C'
#define SSELF  '@'
#define PUCK   'P'
#define SPUCK  'S'

/* These define scoring.
 */
#define SCORE_DOT       1
#define SCORE_PILL      2
#define SCORE_PUCK      4
#define SCORE_SPUCK     6
#define SCORE_LASTMAN   5

/* Super pills last for this many turns.
 */
#define PILL_DURATION   6

/* World construction probabilities.
 */
#define P_HOLLOW        0.85
#define P_PILL          0.025

/* Maximum number of turns, and other
 * game constraints.
 */
#define ROUND_LIMIT     300

#endif //__DEFINES_H__
