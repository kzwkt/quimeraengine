Imports System
Imports Microsoft.VisualStudio.CommandBars
Imports Extensibility
Imports EnvDTE
Imports EnvDTE80

Public Class Connect

    Implements IDTExtensibility2
    Implements IDTCommandTarget

    Private _applicationObject As DTE2
    Private _addInInstance As AddIn

    '''<summary>Implementa el constructor del objeto Add-in. Ponga el código de inicialización en este método.</summary>
    Public Sub New()

    End Sub

    '''<summary>Implementa el método OnConnection de la interfaz IDTExtensibility2. Recibe notificación de que se va a cargar el objeto Add-in.</summary>
    '''<param name='application'>Objeto raíz de la aplicación host.</param>
    '''<param name='connectMode'>Describe cómo se va a cargar el objeto Add-in.</param>
    '''<param name='addInInst'>Objeto que representa este complemento.</param>
    '''<remarks></remarks>
    Public Sub OnConnection(ByVal application As Object, ByVal connectMode As ext_ConnectMode, ByVal addInInst As Object, ByRef custom As System.Array) Implements IDTExtensibility2.OnConnection
        _applicationObject = CType(application, EnvDTE80.DTE2)
        _addInInstance = CType(addInInst, EnvDTE.AddIn)
        If connectMode = ext_ConnectMode.ext_cm_UISetup Then
            Dim objAddIn As AddIn = CType(addInInst, AddIn)
            Dim CommandObj As Command
            Dim objCommandBar As CommandBar

            'If your command no longer appears on the appropriate command bar, or if you would like to re-create the command,
            ' close all instances of Visual Studio .NET, open a command prompt (MS-DOS window), and run the command 'devenv /setup'.
            objCommandBar = CType(_applicationObject.Commands.AddCommandBar("Comentar", vsCommandBarType.vsCommandBarTypeMenu, _applicationObject.CommandBars.Item("Tools")), Microsoft.VisualStudio.CommandBars.CommandBar)

            CommandObj = _applicationObject.Commands.AddNamedCommand(objAddIn, "IntroComment", "IntroComment", "TODO: Enter your command description", True, 59, Nothing, 1 + 2)  '1+2 == vsCommandStatusSupported+vsCommandStatusEnabled
            CommandObj.AddControl(objCommandBar)
        Else
            'If you are not using events, you may wish to remove some of these to increase performance.
            EnvironmentEvents.DTEEvents = CType(_applicationObject.Events.DTEEvents, EnvDTE.DTEEvents)
            EnvironmentEvents.DocumentEvents = CType(_applicationObject.Events.DocumentEvents(Nothing), EnvDTE.DocumentEvents)
            EnvironmentEvents.WindowEvents = CType(_applicationObject.Events.WindowEvents(Nothing), EnvDTE.WindowEvents)
            EnvironmentEvents.TaskListEvents = CType(_applicationObject.Events.TaskListEvents(""), EnvDTE.TaskListEvents)
            EnvironmentEvents.FindEvents = CType(_applicationObject.Events.FindEvents, EnvDTE.FindEvents)
            EnvironmentEvents.OutputWindowEvents = CType(_applicationObject.Events.OutputWindowEvents(""), EnvDTE.OutputWindowEvents)
            EnvironmentEvents.SelectionEvents = CType(_applicationObject.Events.SelectionEvents, EnvDTE.SelectionEvents)
            EnvironmentEvents.SolutionItemsEvents = CType(_applicationObject.Events.SolutionItemsEvents, EnvDTE.ProjectItemsEvents)
            EnvironmentEvents.MiscFilesEvents = CType(_applicationObject.Events.MiscFilesEvents, EnvDTE.ProjectItemsEvents)
            EnvironmentEvents.DebuggerEvents = CType(_applicationObject.Events.DebuggerEvents, EnvDTE.DebuggerEvents)
        End If
    End Sub

    '''<summary>Implementa el método OnDisconnection de la interfaz IDTExtensibility2. Recibe notificación de que se va a descargar el objeto Add-in.</summary>
    '''<param name='disconnectMode'>Describe cómo se va a cargar el objeto Add-in.</param>
    '''<param name='custom'>Matriz de parámetros que son específicos de la aplicación host.</param>
    '''<remarks></remarks>
    Public Sub OnDisconnection(ByVal disconnectMode As ext_DisconnectMode, ByRef custom As Array) Implements IDTExtensibility2.OnDisconnection
    End Sub

    '''<summary>Implementa el método OnAddInsUpdate de la interfaz IDTExtensibility2. Recibe notificación de que ha cambiado la colección de complementos.</summary>
    '''<param name='custom'>Matriz de parámetros que son específicos de la aplicación host.</param>
    '''<remarks></remarks>
    Public Sub OnAddInsUpdate(ByRef custom As Array) Implements IDTExtensibility2.OnAddInsUpdate
    End Sub

    '''<summary>Implementa el método OnStartupComplete de la interfaz IDTExtensibility2. Recibe notificación de que se completó la carga de la aplicación host.</summary>
    '''<param name='custom'>Matriz de parámetros que son específicos de la aplicación host.</param>
    '''<remarks></remarks>
    Public Sub OnStartupComplete(ByRef custom As Array) Implements IDTExtensibility2.OnStartupComplete
    End Sub

    '''<summary>Implementa el método OnBeginShutdown de la interfaz IDTExtensibility2. Recibe notificación de que se va a descargar la aplicación host.</summary>
    '''<param name='custom'>Matriz de parámetros que son específicos de la aplicación host.</param>
    '''<remarks></remarks>
    Public Sub OnBeginShutdown(ByRef custom As Array) Implements IDTExtensibility2.OnBeginShutdown
    End Sub

    '''<summary>Implementa el método QueryStatus de la interfaz IDTCommandTarget. Se le llama cuando se actualiza la disponibilidad del comando</summary>
    '''<param name='commandName'>Nombre del comando del que se va a determinar el estado.</param>
    '''<param name='neededText'>Texto necesario para el comando.</param>
    '''<param name='status'>Estado del comando de la interfaz de usuario.</param>
    '''<param name='commandText'>Texto solicitado por el parámetro neededText.</param>
    '''<remarks></remarks>
    Public Sub QueryStatus(ByVal commandName As String, ByVal neededText As vsCommandStatusTextWanted, ByRef status As vsCommandStatus, ByRef commandText As Object) Implements IDTCommandTarget.QueryStatus
        status = vsCommandStatus.vsCommandStatusUnsupported
        If neededText = EnvDTE.vsCommandStatusTextWanted.vsCommandStatusTextWantedNone Then
            If commandName = "MyAddin4.Connect.IntroComment" Then
                status = CType(vsCommandStatus.vsCommandStatusEnabled + vsCommandStatus.vsCommandStatusSupported, vsCommandStatus)
            End If

        End If
    End Sub

    '''<summary>Implementa el método Exec de la interfaz IDTCommandTarget. Se le llama cuando se invoca el comando.</summary>
    '''<param name='commandName'>Nombre del comando que se va a ejecutar.</param>
    '''<param name='executeOption'>Describe cómo se debe ejecutar el comando.</param>
    '''<param name='varIn'>Parámetros pasados desde el llamador al controlador de comandos.</param>
    '''<param name='varOut'>Parámetros pasados desde el controlador de comandos al llamador.</param>
    '''<param name='handled'>Comunica al llamador si se controló el comando o no.</param>
    '''<remarks></remarks>
    Public Sub Exec(ByVal commandName As String, ByVal executeOption As vsCommandExecOption, ByRef varIn As Object, ByRef varOut As Object, ByRef handled As Boolean) Implements IDTCommandTarget.Exec
        handled = False
        If (executeOption = vsCommandExecOption.vsCommandExecOptionDoDefault) Then
            If commandName = "MyAddin4.Connect.IntroComment" Then
                handled = True
                Comentar.DTE = _applicationObject
                Comentar.IntroComment()
                Exit Sub
            End If
        End If
    End Sub

End Class
