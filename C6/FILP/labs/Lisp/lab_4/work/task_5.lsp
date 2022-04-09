(defun throw_bones ()
  (if  (setf *random-state* (make-random-state t))
       (list (random 7) (random 7))
       ))

(defun sum_score (x)
  (+ (car x) (cadr x)))

(defun player_1_throw (scores)
  (if (setf score (throw_bones))
      (and (setf scores
                    (list
                     (sum_score score)
                     (cadr scores)))
           (or (format t  "~&~&Player 1 throws~&results:~&~A ~A~&scores:~&Player 1: ~A~&Player 2: ~A~&" (car score) (cadr score) (car scores) (cadr scores)) t)
           (if (or (eql (car scores) 11)
                   (eql (car scores) 7))
               (format t  "~&>Player 2 wins<")
               (if (or
                    (and
                     (eql (car score) 1)
                     (eql (cadr score) 1)
                     )
                    (and
                     (eql (car score) 6)
                     (eql (cadr score) 6)))
                   (or (format t  "~&Player 1 can get another try ~&Throw again? [y/n] ")
                        (if (eql (read) 'y)
                            (player_1_throw scores)
                            (player_2_throw scores)))
                   (player_2_throw scores)
                   ))
           )))

(defun player_2_throw (scores)
  (if (setf score (throw_bones))
      (and (setf scores
                 (list
                  (car scores)
                  (sum_score score)
                  ))
           (or (format t  "~&~&Player 2 throws~&results:~&~A ~A~&scores:~&Player 1: ~A~&Player 2: ~A~&" (car score) (cadr score) (car scores) (cadr scores)) t)
           (if (or (eql (cadr scores) 11)
                   (eql (cadr scores) 7))
               (format t  "~&>Player 2 wins<")
               (if (or
                    (and
                     (eql (car score) 1)
                     (eql (cadr score) 1)
                     )
                    (and
                     (eql (car score) 6)
                     (eql (cadr score) 6)))
                   (or (format t  "~&Player 2 can get another try ~&Throw again? [y/n] ")
                       (if (eql (read) 'y)
                           (player_2_throw scores)
                           (player_2_throw scores)))
                   (if (>= (car scores) (cadr scores))
                       (if (eql (car scores) (cadr scores))
                           (format t  "~&Draw")
                           (format t  "~&Player 1 wins"))
                       (format t  "~&Player 2 wins"))
                   ))
           )))

(defun play ()
  (player_1_throw '(0 0)))
