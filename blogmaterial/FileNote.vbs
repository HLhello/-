Dim wsh,fso
Set wsh = CreateObject("Wscript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set target = Wscript.arguments

If target.Count Then
	path = target(0) & ":FileNote.txt"
	If Not (fso.FileExists(path)) Then Note()
	wsh.Run "cmd /c notepad " & path,0
	Wscript.Quit
Else
	folder = fso.getfolder(".")
	vbs = Replace(Wscript.ScriptFullName, "\", "\\")
	cmd = "wscript.exe \""" & vbs & "\"" \""%1\"""
	If Installed() Then
		a = MsgBox("�Ѵ����ļ��Ҽ��˵����Ƿ�����Unreg.reg���Ƴ���",36,"ȷ��")
		If a = vbYes Then UnReg()
	Else
		a = MsgBox("δ��ӵ��ļ��Ҽ��˵����Ƿ�����reg.reg����ӣ�",36,"ȷ��")
		If a = vbYes Then Reg()
	End If
End If

Function Reg()
	Set f = fso.CreateTextFile(folder & "\Reg.reg")
	f.WriteLine "Windows Registry Editor Version 5.00"
	f.WriteLine
	f.WriteLine "[HKEY_CLASSES_ROOT\*\shell\File Note]"
	f.WriteLine "@=" & Chr(34) & "File Note" & Chr(34)
	f.WriteLine
	f.WriteLine "[HKEY_CLASSES_ROOT\*\shell\File Note\command]"
	f.WriteLine "@=" & Chr(34) & cmd & Chr(34)
	f.close
	Wscript.echo "reg.reg�����ɣ�����reg.reg����Ҽ��˵���"
	Wscript.Quit
End Function

Function UnReg()
	Set f = fso.CreateTextFile(folder & "\UnReg.reg")
	f.WriteLine "Windows Registry Editor Version 5.00"
	f.WriteLine
	f.WriteLine "[-HKEY_CLASSES_ROOT\*\shell\File Note]"
	f.WriteLine "@=" & Chr(34) & "File Note" & Chr(34)
	f.close
	Wscript.echo "Unreg.reg�����ɣ�����Unreg.reg�Ƴ��Ҽ��˵���"
	Wscript.Quit
End Function

Function Note()
	Set f = fso.CreateTextFile(path)
	Set s = fso.GetFile(target(0))
'���Ƴ��������׵�ע�ͷ���ÿ�β鿴/�༭��עʱ���Զ���ӱ༭���ڵ���ע��ĩ��
'	f.WriteLine ".LOG"
	f.WriteLine "[File Note]"
	f.WriteLine "ԭ�ļ�����:" & s.Name
	f.WriteLine "ԭ�ļ���С:" & s.Size
	f.Close
End Function

Function Installed()
	On Error Resume Next
	k=wsh.RegRead("HKCR\*\shell\File Note\")
	If err.Number = -2147024894 Then Installed = 0 Else Installed = 1
End Function