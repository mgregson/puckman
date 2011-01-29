(* Basic OCAML PUCKMAN client *)
(* In Ubuntu/Debian you will want the ocaml-core package *)
open ExtLib;;

(* Fetch a board tile. No particular checking is done of the input *)
let rec fetch_board_tile a = let tile = input_char stdin in
                         if tile == '\n' then fetch_board_tile a else tile;;

(* Read an int and discard everything that doesn't match *)
let rec hobo_read_int () = try read_int()  with _ -> hobo_read_int();;

(* Read in a board *)
let read_board () =  let width = hobo_read_int() in
                  let tile_count = width*width in 
                  let board = Array.init tile_count fetch_board_tile in 
                  board;;

let board_width board =  (int_of_float (sqrt (float_of_int (Array.length board))));;

(* Find puckman on the board *)
let find_raw_self board = Array.findi (fun a -> a == 'C' || a == '@') board;;
let find_self board = let width = board_width board in
                      let raw_pos = find_raw_self board in
                      (raw_pos/width,raw_pos mod width);;
let left (a,b) = (a,b-1) ;;
let right (a,b) = (a,b+1) ;;
let up (a,b) = (a-1,b) ;;
let down (a,b) = (a+1,b) ;;

let rec at(a,b) board = let width = board_width board in
                        if (a < 0 || b < 0 || b> width-1 || a > width-1) then
                        '!'
                        else
                        Array.get  board (a*width+b)
                        ;;

(* Try to eat a dot, otherwise go down *)
let try_to_eat_dot board pos = let self = find_self board in
                               if (at (left self) board) == '.' then 'L' else
                               if (at (right self) board) == '.' then 'R' else
                               if (at (up self) board) == '.' then 'U' else
                               'D';;

(* Perform a PUCKMAN move, one of L,R,U,D *)
let do_move m = print_char m;;

let rec main () = while true do 
let board = read_board() in
let self = find_self board in
do_move (try_to_eat_dot board self) (* Not a valid move *)
done;;

main();;