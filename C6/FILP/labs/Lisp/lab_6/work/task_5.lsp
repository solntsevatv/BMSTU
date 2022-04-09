(defun square_lst (&rest lst)
  (mapcar (lambda (x) (* x x)) lst)
  )
