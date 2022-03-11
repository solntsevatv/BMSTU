; ��������������������������������������������������������������������������������������������������
;                                Build this dialog with MAKEIT.BAT
; ��������������������������������������������������������������������������������������������������

    ; __UNICODE__ equ 1    ; uncomment to build as UNICODE

    include \masm32\include\masm32rt.inc
    include \masm32\include\debug.inc
    includelib \masm32\lib\debug.lib
    .686
    .MMX
    .XMM

; ��������������������������������������������������������������������������������������������������

    include project.inc

  ; --------------------
  ; GLOBAL scope handles
  ; --------------------
    .data?
      hInstance  dd ?
      hWnd       dd ?

      resultText dd ?
      firstEdit  dd ?
      secondEdit dd ?

      str_1      db 64 dup (0),0
      str_2      db 64 dup (0),0

    .code

start:
    mov hInstance, FUNC(GetModuleHandle, NULL)

  ; -------------------------------------------
  ; Call the dialog box from the resource file
  ; -------------------------------------------
    invoke DialogBoxParam,hInstance,100,0,ADDR DlgProc,0

    invoke ExitProcess,eax

; ��������������������������������������������������������������������������������������������������

DlgProc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD

    LOCAL icce:INITCOMMONCONTROLSEX

    STRING dlgTitle, "Summator"

      switch uMsg
        case WM_INITDIALOG
          m2m hWnd, hWin    ; Copy hWin to GLOBAL variable
          invoke SendMessage,hWin,WM_SETTEXT,0,ADDR dlgTitle
          invoke SendMessage,hWin,WM_SETICON,1,FUNC(LoadIcon,hInstance,500)

          mov icce.dwSize, SIZEOF INITCOMMONCONTROLSEX            ; set the structure size
          xor eax, eax                                            ; set EAX to zero
          or eax, ICC_WIN95_CLASSES

          mov icce.dwICC, eax
          invoke InitCommonControlsEx,ADDR icce                   ; initialise the common control library

          mov resultText, rv(GetDlgItem,hWin,105)
          mov firstEdit,  rv(GetDlgItem,hWin,101)
          mov secondEdit, rv(GetDlgItem,hWin,103)

          xor eax, eax
          ret

      case WM_COMMAND
        switch wParam
          case 106

            invoke GetWindowText,firstEdit,addr str_1,64
            invoke GetWindowText,secondEdit,addr str_2,64

            mov ebx, uval(addr str_1)
            mov eax, uval(addr str_2)
            add eax, ebx
            fn SetWindowText,resultText,str$(eax)
        endsw

      case WM_CLOSE
        exit_dialog:                ; jump to this label to close program
        invoke EndDialog,hWin,0

      endsw
    xor eax, eax    ; this must be here in NT4 and later
    ret

DlgProc endp

end start

