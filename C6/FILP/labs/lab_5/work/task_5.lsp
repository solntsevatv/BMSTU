(defun get-by-index (lst index cntr)
  (if (not (eql lst nil))
      (if (eql cntr index)
          lst
          (get-by-index (cdr lst) index (+ cntr 1))
          )
      nil
   )
  )

(defun swap-two-ellement (lst first second)
  (let ((first_elem (get-by-index lst first 0)) (second_elem (get-by-index lst second 0)))
    (let ((temp (car first_elem)))
      (setf (car first_elem) (car second_elem))
      (setf (car second_elem) temp)
      lst
      )
    )
  )
