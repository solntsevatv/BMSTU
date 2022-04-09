(defun my_reverse_rec (lst new_lst)
  (if (not (eql (cdr lst) nil))
      (my_reverse_rec (cdr lst) (cons (car lst) new_lst))
      (cons (car lst) new_lst)))

(defun my_reverse (lst)
  (my_reverse_rec lst nil))

(defun cmp_list_rec (lst_1 lst_2)
  (if (eql (car lst_1) (car lst_2))
      (if (not (or (eql (cdr lst_1) nil) (eql (cdr lst_2) nil)))
          (cmp_list_rec (cdr lst_1) (cdr lst_2))
          (if (and (eql (cdr lst_1) nil) (eql (cdr lst_2) nil))
              t
              nil))
      nil))

(defun check_palindrom (lst)
  (cmp_list_rec lst (my_reverse lst)))
