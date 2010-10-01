Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports EnvDTE90a
Imports EnvDTE100
Imports System.Diagnostics

Public Module Documentador

    Public DTE As EnvDTE80.DTE2

    Sub Documentar()

        Dim textSelection As EnvDTE.TextSelection

        'Bajo la premisa de que haremos click derecho sobre el nombre del método
        textSelection = DTE.ActiveDocument.Selection
        textSelection.StartOfLine()

        'Busca un hueco vacío sobre la declaración del método
        'para escribir el comentario
        '----------------------------------------------------------
        Dim lineaDocumentacion As Integer
        Dim cadAux As String

        textSelection.SelectLine()
        cadAux = textSelection.Text

        If cadAux.IndexOf("}") > -1 Or cadAux.IndexOf(";") > -1 Then
            textSelection.LineUp(False)
            textSelection.SelectLine()
            cadAux = textSelection.Text
        End If

        While cadAux <> vbCrLf And _
              cadAux.IndexOf("}") = -1 And _
              cadAux.IndexOf(";") = -1

            textSelection.LineUp(False)
            textSelection.SelectLine()
            cadAux = textSelection.Text
        End While

        lineaDocumentacion = textSelection.TopLine

        'Busca la llave de apertura del método o el punto y coma
        '------------------------------------------------------------
        textSelection.EndOfLine()
        textSelection.SelectLine()
        cadAux = textSelection.Text

        While cadAux.IndexOf("{") = -1 And _
              cadAux.IndexOf(";") = -1
            textSelection.LineDown(True)
            cadAux = textSelection.Text
        End While

        Dim textoMetodo As String
        textoMetodo = textSelection.Text

        'Parsea parámetros
        '-----------------------
        Const AlgunParentesisAbierto As Integer = 1
        Const NingunAnguloAbierto As Integer = 0

        Dim posChar As Integer
        Dim parentesisAbiertos As Integer
        Dim angulosAbiertos As Integer
        Dim nombreParam As String
        Dim paramOpcional As Boolean

        Dim posPrimerParentesis As Integer = -1

        Dim arrayNombres As Collection
        Dim arrayOpcionales As Collection
        arrayNombres = New Collection
        arrayOpcionales = New Collection


        ' Busca por coma o paréntesis de cierre de lista de argumentos
        ' Se tiene en cuenta que pueden haber paréntesis en los parámetros
        ' Mientras no se supere la longitud de la cadena, y no se encuentre el paréntesis
        ' de cierre final (cuando sólo quede 1 por cerrar)
        While posChar < textoMetodo.Length And _
              Not (textoMetodo.Chars(posChar) = ")" And _
                    parentesisAbiertos = AlgunParentesisAbierto) And _
              Not (textoMetodo.Chars(posChar) = ";" Or _
                    textoMetodo.Chars(posChar) = "{")

            Dim currentChar As Char = textoMetodo.Chars(posChar)

            ' Cuenta de ángulos abiertos
            If currentChar = "<" Then
                angulosAbiertos = angulosAbiertos + 1
            ElseIf currentChar = ">" Then
                angulosAbiertos = angulosAbiertos - 1
            End If

            ' Cuenta paréntesis abiertos
            If currentChar = "(" Then
                parentesisAbiertos = parentesisAbiertos + 1
            ElseIf currentChar = ")" Then
                parentesisAbiertos = parentesisAbiertos - 1
            End If

            If textoMetodo.Chars(posChar) = "(" And posPrimerParentesis = -1 Then
                posPrimerParentesis = posChar
            End If

            ' Si se llega a una coma
            If (currentChar = "," And angulosAbiertos = NingunAnguloAbierto) Or (currentChar = "=" And posPrimerParentesis > -1) Then

                ' La condición evita que se tomen como nombre de parámetro a los valores
                ' por defecto de tales parámetros
                If (paramOpcional = False) Then

                    Dim posAtras As Integer
                    Dim posFinParam As Integer

                    posAtras = posChar - 1
                    While Not Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                          posAtras > 0
                        posAtras = posAtras - 1
                    End While

                    posFinParam = posAtras

                    While Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                          posAtras > 0
                        posAtras = posAtras - 1
                    End While

                    ' Nombre de parámetro encontrado
                    arrayNombres.Add(textoMetodo.Substring(posAtras + 1, posFinParam - posAtras).Trim())

                    paramOpcional = False
                End If

                ' Los parámetros opcionales contienen un =
                ' Debe saltarse el reconocimiento de antes de la coma para estos
                If (currentChar = "=") Then
                    paramOpcional = True
                    ' Guarda el índice del parámetro que es opcional
                    arrayOpcionales.Add(arrayNombres.Count, arrayNombres.Count)
                Else
                    paramOpcional = False
                End If

            End If

            posChar = posChar + 1

        End While

        Dim devuelveValor As Boolean = False
        Dim arrayExcepciones As Collection
        arrayExcepciones = New Collection

        ' Si se trata de un método, buscar el resto de información
        If posPrimerParentesis > -1 Then

            ' Último parámetro, si lo hay
            If textoMetodo.Chars(posChar) = ")" Then
                ' La condición evita que se tomen como nombre de parámetro a los valores
                ' por defecto de tales parámetros
                If (paramOpcional = False) Then

                    Dim posAtras As Integer
                    Dim posFinParam As Integer

                    posAtras = posChar - 1
                    While Not Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                          posAtras > 0
                        posAtras = posAtras - 1
                    End While

                    posFinParam = posAtras

                    While Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                          posAtras > 0
                        posAtras = posAtras - 1
                    End While

                    ' Nombre de parámetro encontrado
                    arrayNombres.Add(textoMetodo.Substring(posAtras + 1, posFinParam - posAtras).Trim())

                    paramOpcional = False
                End If
            End If

            ' Busca las excepciones que tira el método
            ' Actualmente, se supone que está en el paréntesis de cierre ")"
            posChar = posChar + 1

            If textoMetodo.IndexOf("throw", posChar) > -1 Then

                While posChar < textoMetodo.Length And _
                  Not (textoMetodo.Chars(posChar) = ")")

                    Dim currentChar As Char = textoMetodo.Chars(posChar)

                    ' Si se llega a una coma
                    If currentChar = "," Then

                        Dim posAtras As Integer
                        Dim posFinTipo As Integer

                        posAtras = posChar - 1
                        While Not Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                              posAtras > 0
                            posAtras = posAtras - 1
                        End While

                        posFinTipo = posAtras

                        While Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                              posAtras > 0
                            posAtras = posAtras - 1
                        End While

                        ' Nombre de tipo de excepción encontrado
                        arrayExcepciones.Add(textoMetodo.Substring(posAtras + 1, posFinTipo - posAtras).Trim())

                    End If

                    posChar = posChar + 1

                End While

            End If

            ' Último tipo de excepción, si lo hay
            If textoMetodo.Chars(posChar) = ")" Then
                Dim posAtras As Integer
                Dim posFinTipo As Integer

                posAtras = posChar - 1
                While Not Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                      posAtras > 0
                    posAtras = posAtras - 1
                End While

                posFinTipo = posAtras

                While Char.IsLetterOrDigit(textoMetodo.Chars(posAtras)) And _
                      posAtras > 0
                    posAtras = posAtras - 1
                End While

                ' Nombre de tipo de excepción encontrado
                arrayExcepciones.Add(textoMetodo.Substring(posAtras + 1, posFinTipo - posAtras).Trim())

            End If

            ' Verifica si la función devuelve un valor o no
            If textoMetodo.IndexOf("void", 1, posPrimerParentesis) = -1 Then
                devuelveValor = True
            End If
        End If

        textSelection.GotoLine(lineaDocumentacion, True)
        textSelection.Insert(GeneraDocumentacion(arrayNombres, arrayOpcionales, devuelveValor, arrayExcepciones), vsInsertFlags.vsInsertFlagsInsertAtEnd)

    End Sub


    Function GeneraDocumentacion(ByRef arrayNombres As Collection, ByRef arrayOpcionales As Collection, ByVal devuelveValor As Boolean, ByRef arrayExcepciones As Collection) As String

        Dim output As String

        ' Descripción
        output = output & vbCrLf & "/// <summary>" & vbCrLf & "/// [DOC]" & vbCrLf & "/// </summary>"

        ' Parámetros
        Dim indice As Integer = 1
        For Each nombre As String In arrayNombres
            output = output & vbCrLf & "/// <param name=" & Chr(34) & nombre & Chr(34) & ">"

            If (arrayOpcionales.Contains(indice)) Then
                output = output & "[Opcional]"
            End If

            output = output & "[DOC]</param>"

            indice = indice + 1
        Next

        ' Valor devuelto
        If devuelveValor Then
            output = output & vbCrLf & "/// <returns>" & vbCrLf & "/// [DOC]" & vbCrLf & "/// </returns>"
        End If

        ' Excepciones
        For Each nombre As String In arrayExcepciones
            output = output & vbCrLf & "/// <exception cref=" & Chr(34) & nombre & Chr(34) & "></exception>"
        Next

        Return output

    End Function
End Module
