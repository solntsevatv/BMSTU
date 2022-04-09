(defun mult-first-num (lst num)
  (if (not (eql lst nil))
      (and
       (setf (car lst) (* (car lst) num))
       lst
       )
      )
  )

(defun mult-first-maybe-num-rec (lst num first)
  (if (not (eql lst nil))
      (if (numberp (car lst))
          (and
           (setf (car lst) (* (car lst) num))
           first
           )
          (mult-first-maybe-num-rec (cdr lst) num first)
          )
      )
  )

(defun mult-first-maybe-num (lst num)
  (mult-first-maybe-num-rec lst num lst)
  )
