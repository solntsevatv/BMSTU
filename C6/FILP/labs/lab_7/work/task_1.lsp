(defun my-reverse_rec (lst new_lst)
  (if (not (eql (cdr lst) nil))
      (my_reverse_rec (cdr lst) (cons (car lst) new_lst))
      (cons (car lst) new_lst)))

(defun my-reverse (lst)
  (my_reverse_rec lst nil))
