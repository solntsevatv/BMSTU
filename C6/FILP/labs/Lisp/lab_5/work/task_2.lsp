(defun in-list (lst elem)
  (if (eql (car lst) elem)
      t
      (if (eql (cdr lst) nil)
          nil
          (in-list (cdr lst) elem)
          )
      )
  )

(defun set-equal-rec (set_1 set_2)
  (if (in-list set_1 (car set_2))
      (if (not (eql (cdr set_2) nil))
          (set-equal-rec set_1 (cdr set_2))
          t
          )
      nil
      )
  )

(defun set-equal (set_1 set_2)
  (let (set-equal-rec set_1 set_2) (set-equal-rec set_2 set_1))
  )
