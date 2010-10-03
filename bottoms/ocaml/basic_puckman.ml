(* Basic OCAML PUCKMAN client *)

(* Fetch a board tile. No particular checking is done of the input *)
let rec fetch_board_tile a = let tile = input_char stdin in
                         if tile == '\n' then fetch_board_tile a else tile;;

(* Read an int and discard everything that doesn't match *)
let rec hobo_read_int () = try read_int()  with _ -> hobo_read_int();;

(* Read in a board *)
let read_board () =  let width = hobo_read_int() in
                  let board = Array.make_matrix width width '!' in 
                  Array.map (fun a -> Array.map fetch_board_tile a) board;;

(* Perform a PUCKMAN move, one of L,R,U,D *)
let do_move m = print_char m;;

let rec main () = while true do 
let board = read_board() in
do_move 'M'
done;;

main();;