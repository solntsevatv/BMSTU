(defun get-interval-rec (lst new-lst a b)
  (if (not (eql lst nil))
      (if (and (< a (car lst)) (> b (car lst)))
          (get-interval-rec (cdr lst) `(,@new-lst ,(car lst)) a b)
          (get-interval-rec (cdr lst) new-lst a b)
          )
      new-lst
      )
  )

(defun get-interval (lst a b)
  (get-interval-rec lst nil a b)
  )
