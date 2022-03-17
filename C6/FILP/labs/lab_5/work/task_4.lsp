(defun swap-first-last-rec (lst first)
  (if (eql (cddr lst) nil)
      (let ((new-first (cdr lst)))
        (if (and
                (or (setf new-first (cons (cadr lst) (cdr first))) t)
                (or (setf (cdr first) nil) t)
                (or (setf (cdr lst) first) t)
                )
                new-first
                nil
            )
      )
      (swap-first-last-rec (cdr lst) first)
      )
  )

(defun swap-first-last (lst)
  (swap-first-last-rec lst lst))
