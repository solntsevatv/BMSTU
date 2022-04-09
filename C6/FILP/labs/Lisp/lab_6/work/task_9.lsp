(defun lst-sub-len (lst)
  (reduce #'+ (mapcar 'length lst))
  )
