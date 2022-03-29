(defun func_mult_x (n)
  #'(lambda (x) (* x n))
  )

(defun mult_numbers (lst x)
  (mapcar (func_mult_x x) lst)
  )

(defun func_mult_check_x (n)
  #'(lambda (x)
      (if (numberp x)
          (* x n)
          x
          )
      )
  )

(defun mult_check_numbers (lst x)
  (mapcar (func_mult_check_x x) lst)
  )
