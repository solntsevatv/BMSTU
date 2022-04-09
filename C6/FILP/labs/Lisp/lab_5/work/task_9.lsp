(defun count-size-rec (lst cnt)
  (if (eql (cdr lst) nil)
      cnt
      (count-size-rec (cdr lst) (+ cnt 1)))
  )

(defun count-size (lst)
  (count-size-rec lst 1)
  )

(defun check-nums (lst)
  (if (eql (cdr lst) nil)
      t
      (if (numberp (car lst))
          (check-nums (cdr lst))
          nil
       )
   )
  )

;; 0 -- start -- num -- end -->

(defun select-between-rec (lst new-lst start end)
  (if (not (eql lst nil))
      (if (and
           (>= (car lst) start)
           (<= (car lst) end)
           )
          (if (eql new-lst nil)
              (select-between-rec (cdr lst) (list (car lst)) start end)
              (select-between-rec (cdr lst) (append new-lst (list (car lst))) start end)
              )
          (select-between-rec (cdr lst) new-lst start end)
          )
      new-lst
      )
  )


(defun select-between (lst start end)
  (if (and
       (eql (count-size lst) 5)
       (check-nums lst)
       )
      (select-between-rec lst nil start end)
      )
  )
