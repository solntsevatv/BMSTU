(defun select-between (lst a b)
  (mapcan #'(lambda (x) (if (and (> x a) (< x b)) (list x))) lst)
  )
