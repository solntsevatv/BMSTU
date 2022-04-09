(defun my-last (lst)
  (if (eql (cdr lst) nil)
      lst
      (my-last (cdr lst))
      )
  )

(defun swap-to-left-rec (lst temp)
  (if (not (eql lst nil))
      (let ((temp-local (car lst)))
        (setf (car lst) temp)
        (swap-to-left-rec (cdr lst) temp-local)
        )
      )
  )

(defun swap-to-left (lst)
  (let ((temp (car lst)))
    (setf (car lst) (car (my-last lst)))
    (swap-to-left-rec (cdr lst) temp)
    lst
    )
  )



(defun my_reverse_rec (lst new_lst)
  (if (not (eql (cdr lst) nil))
      (my_reverse_rec (cdr lst) (cons (car lst) new_lst))
      (cons (car lst) new_lst)))

(defun my_reverse (lst)
  (my_reverse_rec lst nil))

(defun swap-to-right (lst)
  (let ((temp nil) (reverse-lst (my_reverse lst)))
    (setf temp (car reverse-lst))
    (setf (car reverse-lst) (car (my-last reverse-lst)))
    (swap-to-left-rec (cdr reverse-lst) temp)
    (my_reverse reverse-lst)
    )
  )

