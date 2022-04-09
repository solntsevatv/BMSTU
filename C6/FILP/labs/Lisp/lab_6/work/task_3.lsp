(defun check_palindrom (lst)
  (reduce #'(lambda (x y) (and x y)) (mapcar #'(lambda (x y) (eql x y)) lst (reverse lst)))
  )
