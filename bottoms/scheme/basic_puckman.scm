;;A basic PUCKMAN client
(require (lib "43.ss" "srfi"))
;;Chose a move
(define (chose-move board self)
  (if (have-power board) 
      ;;If we have the power pil go for gold
      (try-to-eat-competitor board self try-to-eat-dot rand-eat-space) 
      ;;If we don't try and find a dot
      (try-to-eat-dot board self rand-eat-space) )
  )
;;If it can eat the competitor in one move it does it
;;Otherwise call alternate strategy
(define (try-to-eat-competitor board self alt alt2)
  (cond
  ((eq? #\P (above-p board self)) #\U)
  ((eq? #\P (bellow-p board self)) #\D)
  ((eq? #\P (left-of-p board self)) #\L)
  ((eq? #\P (right-of-p board self)) #\R)
  (else (alt board self al2) );;Default is left
  ))
(define (try-to-eat-dot board self alt)
 (cond
  ((eq? #\. (above-p board self)) #\U)
  ((eq? #\. (bellow-p board self)) #\D)
  ((eq? #\. (left-of-p board self)) #\L)
  ((eq? #\. (right-of-p board self)) #\R)
  (else (alt board self));;Default is left
  ))
(define (rand-eat-space board self)
 (letrec ((validmoves (find-valid-moves board self))
	  (movechosen (random (abs (- (length validmoves) 1)))))
   (if (> (length validmoves) 0) (car (drop validmoves movechosen)) #\L);;Fucked
  )
)

;;Main loop
;;Sample main loop
;;Attempts to eat a dot. If it can't, it goes left
(define (main)
 (letrec
   ((board (read-board-state))
    (self (find-self board))
    (move (chose-move board self))
    )
  (do-move move)
  (main)
  )
)
;;Find the valid moves
(define (find-valid-moves board self)
 (map cdr (filter (lambda (n) (is-valid board (car n))) (find-relative board self)))
)
;;Check if a move is valid for us
(define (is-valid board move)
  (cond
    ((eq? #\. move) #t)
    ((eq? #\  move) #t)
    ((eq? #\S move) #f);;We say never go for self destruct
    ((eq? #\O move) #t)
    ((eq? #\+ move) #f)
    ((have-power board) #t);;Other posibilites are valid if we have power pill
    (else #f);;no power pill, we would die
  ))
;;Zip two lists together
(define (zip a b)
 (if (or (empty? a) (empty? b)) '() (cons (cons a b) (zip (cdr a) (cdr b))))
)
(define (find-relative board self)
 (zip (map (lambda (n) (n board self) ) moves) movenames)
)

;;Board structure
(define-struct puckman-board (width vec))
(define-struct point (x y))
;;All return ! if out of bounds

;;Determine whats bellow a point
(define (bellow-p board p)
 (get-from-board board (make-point (+ 1 (point-x p)) (point-y p)))
)
;;Determine whats above a point
(define (above-p board p)
 (get-from-board board (make-point (-  (point-x p) 1) (point-y p) )))

;;Determine whats right of a point
(define (right-of-p board p)
 (get-from-board board (make-point (point-x p) (+ (point-y p) 1)))
)
;;Determine whats left of a point
(define (left-of-p board p)
 (get-from-board board (make-point (point-x p) (- (point-y p) 1)))
)
;;Moves and names
(define moves (list bellow-p above-p right-of-p left-of-p))
(define movenames (list #\D #\U #\R #\L))
;;Determine whats at a point, or if given an invalid point give back !
(define (get-from-board board p)
 (let ((position-in-vector (+ (* 
		 (point-x p) (puckman-board-width board)) 
		(point-y p)))
       (width (puckman-board-width board))
       )
  (if (is-ok-point board p)
      (vector-ref
       (puckman-board-vec board) position-in-vector) '!)
))
;;Check if a point is valid
(define (is-ok-point board p)
  (let
     ((position-in-vector (+ (* 
		 (point-x p) (puckman-board-width board)) 
		(point-y p)))
      (width (puckman-board-width board)))
  (and (< position-in-vector  (* width width)) (>= position-in-vector  0)
	   (< (point-x p)  width) (>= (point-x p) 0) (< (point-y p) width) (>= (point-y p) 0))))
;;Helper functions
(define (find-self board)
 (let ((pos (vector-index (lambda (n) (or (eq? #\C n) (eq? #\@ n))) (puckman-board-vec board))))
  (make-point (quotient pos (puckman-board-width board))
	      (modulo pos (puckman-board-width board)) )
))
(define (have-power board)
 (if (eq? (vector-index (lambda (n) (eq? #\@ n)) (puckman-board-vec board)) #f) #f #t)
)
(define (find-enemy board)
 (let ((pos (vector-index (lambda (n) (or (eq? #\P n) (eq? #\S n))) (puckman-board-vec board))))
  (make-point (quotient pos (puckman-board-width board))
	      (modulo pos (puckman-board-width board)) )
))
;;Reads the board
(define (read-board-state)
 (letrec ((width (read)) 
	  (readminiboard (lambda (n)
			  (let ((mychar (read-char)))
			   (if (= 0 n) '() 
			       (if (eq? #\newline mychar)
				   (readminiboard n)
				   (cons mychar (readminiboard (- n 1)))
			       )
			   )
	  ))))
  (make-puckman-board width (list->vector (readminiboard (* width width) )))
))
;;Does a move, can be one of L R U or D
(define (do-move M)
 (write-char M)
 (flush-output)
)
(main)

