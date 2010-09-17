Option Strict Off
Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports EnvDTE90a
Imports EnvDTE100
Imports System.Diagnostics

Public Module Comentar
	public Dim DTE as EnvDTE80.DTE2


    Sub IntroComment()

        Dim cad As String, cadfinal As String, cadnombre As String, cadparam As String
        Dim textSelection As EnvDTE.TextSelection
        Dim textPoint As TextPoint
        Dim pospar1 As Integer, pospar2 As Integer, posnombre As Integer

        textSelection = DTE.ActiveDocument.Selection

        cad = textSelection.Text
        If cad = "" Then
            MsgBox("No hay texto seleccionado")
            Exit Sub
        End If

        'Posición de los paréntesis
        pospar1 = cad.IndexOf("(")
        pospar2 = cad.IndexOf(")")

        If pospar1 = -1 Or pospar2 = -1 Then
            MsgBox("No has debido seleccionar bien, falta algún paréntesis")
            Exit Sub
        End If

        'Posición del primer espacio previo al paréntesis -> Nombre de la función
        posnombre = 0
        For i = pospar1 To 1 Step -1
            If Mid(cad, i, 1) = " " Then
                posnombre = i
                Exit For
            End If
        Next

        'Cadenas a insertar

        'sumary
        cadfinal = "///<sumary>Introduce aquí la descripción</sumary>" + Chr(13)

        'nombre
        cadnombre = "///<name>" + Mid(cad, posnombre + 1, pospar1 - posnombre) + "</name>" + Chr(13)

        'parametros
        cadparam = ""
        If pospar2 > pospar1 + 1 Then
            cadparam = parseaParams(Mid(cad, pospar1 + 2, pospar2 - pospar1 - 1))
        End If

        cadfinal = cadfinal + cadnombre + cadparam

        textSelection.LineUp()
        textSelection.NewLine()
        textSelection.Insert(cadfinal)

    End Sub

    Function parseaParams(ByVal cad As String) As String
        Dim i As Integer, j As Integer
        Dim cad1 As String, cadparam As String

        'Sólo hay un parámetro
        If cad.IndexOf(",") = -1 Then
            For i = Len(cad) To 1 Step -1
                If Mid(cad, i, 1) = " " Then
                    parseaParams = "///<param name=" + cad1 + "></param>"
                    Exit Function
                End If
                cad1 = Mid(cad, i, 1) + cad1
            Next
        End If

        'Hay más de un parámetro
        For i = 1 To Len(cad)
            If Mid(cad, i, 1) = "," Or i = Len(cad) Then
                cad1 = ""
                For j = i To 1 Step -1
                    If Mid(cad, j, 1) = " " Then
                        cadparam = cadparam + "///<param name=" + cad1 + "></param>" + Chr(13)
                        Exit For
                    End If
                    cad1 = Mid(cad, j, 1) + cad1
                Next
            End If
        Next

        parseaParams = cadparam
    End Function



End Module
