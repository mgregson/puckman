;;A basic PUCKMAN client
(require (lib "43.ss" "srfi"))
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
 (get-from-board board (make-point (-  (point-x p) 1) (point-y p) ))
)
;;Determine whats right of a point
(define (right-of-p board p)
 (get-from-board board (make-point (point-x p) (+ (point-y p) 1)))
)
;;Determine whats left of a point
(define (left-of-p board p)
 (get-from-board board (make-point (point-x p) (- (point-y p) 1)))
)
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
 (let ((pos (vector-index (lambda (n) (eq? #\C n)) (puckman-board-vec board))))
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
)
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
;;(main)
(define (chose-move board self)
 (cond
  ((eq? #\. (above-p board self)) #\U)
  ((eq? #\. (bellow-p board self)) #\D)
  ((eq? #\. (left-of-p board self)) #\L)
  ((eq? #\. (right-of-p board self)) #\R)
  (else #\L);;Default is left
  ))

