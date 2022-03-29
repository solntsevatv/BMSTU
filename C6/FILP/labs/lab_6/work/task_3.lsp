(defun check_palindrom (lst)
  (eval `(and ,@(mapcar #'(lambda (x y) (eql x y)) lst (reverse lst))))
  )
