(defun cmp-lst (lst_1 lst_2)
  (if (and
       (eql lst_1 nil)
       (eql lst_2 nil)
       )
      t
      (if
       (and
        (not (eql lst_1 nil))
        (not (eql lst_2 nil))
        )
       (if (eql (car lst_1) (car lst_2))
           (cmp-lst (cdr lst_1) (cdr lst_2))
           )
       )
      )
  )

(defun check-duosublist (lst sublst)
  (if (eql lst nil)
      nil
      (if (cmp-lst (car lst) sublst)
          t
          (check-duosublist (cdr lst) sublst)
          )
      )
  )

(defun append-if-not-in-lst (lst sublst)
  (if (not (check-duosublist lst sublst))
      (append lst (list sublst))
      )
  )
