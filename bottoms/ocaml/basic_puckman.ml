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

let find_self board = Array.findi (fun a -> a == 'C' || a == '@') board;;

(* Perform a PUCKMAN move, one of L,R,U,D *)
let do_move m = print_char m;;

let rec main () = while true do 
let board = read_board() in
let self = find_self board in
do_move 'M' (* Not a valid move *)
done;;

main();;