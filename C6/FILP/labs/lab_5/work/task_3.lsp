(setf  table (list (cons 'russia 'moscow) (cons 'germany 'berlin) (cons 'france 'paris) (cons 'spain 'madrid)))

(defun find-cntry-rec (table capital)
  (if (eql (cdar table) capital)
      (caar table)
      (if (not (eql (cdr table) nil))
          (find-cntry-rec (cdr table) capital)
          nil
          )
      )
  )

(defun find-capital-rec (table country)
  (if (eql (caar table) country)
      (cdar table)
      (if (not (eql (cdr table) nil))
          (find-cntry-rec (cdr table) country)
          nil
          )
      )
  )
