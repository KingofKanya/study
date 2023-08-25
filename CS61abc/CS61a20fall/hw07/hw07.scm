(define (filter-lst fn lst)
  (if (null? lst)
      nil
      (let ((first (car lst))
            (rest (cdr lst))
           )
        (if (fn first)
            (cons first (filter-lst fn rest))
            (filter-lst fn rest)
        )
      )
  )
)

; ;; Tests
(define (even? x) (= (modulo x 2) 0))

(filter-lst even? '(0 1 1 2 3 5 8))

; expect (0 2 8)
(define (interleave first second)
  (define (my_interleave n first second)
    (cond 
      ((null? first)
       second
      )
      ((null? second)
       first
      )
      ((= n 1)
       (cons (car first)
             (my_interleave 0 (cdr first) second)
       )
      )
      (else
       (cons (car second)
             (my_interleave 1 first (cdr second))
       )
      )
    )
  )
  (my_interleave 1 first second)
)

(interleave (list 1 3 5) (list 2 4 6))

; expect (1 2 3 4 5 6)
(interleave (list 1 3 5) nil)

; expect (1 3 5)
(interleave (list 1 3 5) (list 2 4))

; expect (1 2 3 4 5)
(define (accumulate combiner start n term)
  (if (= n 1)
      (combiner (term n) start)
      (combiner (term n)
                (accumulate combiner start (- n 1) term)
      )
  )
)

(define (no-repeats lst)
  (if (null? lst)
      nil
      (let ((first (car lst))
            (rest (cdr lst))
           )
        (cons first
              (no-repeats
               (filter-lst (lambda (x) (not (= x first))) lst)
              )
        )
      )
  )
)
