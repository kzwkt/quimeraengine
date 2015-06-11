# 7 Microsoft Windows® platforms #

As of version 1.1.2, libs11n is known to compile on Win32 platforms. In August 2006 (version 1.2.4), libs11n's author accepted a job which requires that he have a PC running Windows. At that point, it became possible to officially support, or at least partially support, Windows platforms for libs11n.

This section is based on my very limited knowledge of the Win32 development tools – your mileage may vary.

## 7.1 General notes about libs11n under Win32 ##
### 7.1.1 Exports and DLLs ###

We do not currently have libs11n running as a full-featured shared library under Windows. The reason for this is the “unusual” code requirements placed on DLLs by Windows. For example, it is necessary to explicitly flag “exportable” classes so that the Windows linker can make them available to code which wants to use the DLL.

This requirement does not exist on Linux platforms, and therefore the proper exports are not in place in all of the code. The library may compile as a DLL, but will not work correctly because of missing exports.

The “proper” way to add exports to libs11n code is to include <s11n.net/s11n/export.hpp> and use the S11N\_EXPORT\_API macro instead of the Windows-specific declspec(dllexport) marker. On non-Windows platforms the S11N\_EXPORT\_API macro expands to nothing (it is empty). For example:

```
#include <s11n.net/s11n/export.hpp>
...
class S11N_EXPORT_API my_class { ... };
```

There are some open questions about where exactly this export should go for class templates, and whether or not class templates have to be explicitly instantiated in order to properly export them. Initial research suggests that template types must be explicitly instantiated, but this requirement is not reasonable for libs11n, which doesn't know about all client-side types and therefore cannot explicitly instantiate them.

For more information on this problem, please refer to your favourite search engine or this Microsoft web page:

http://msdn2.microsoft.com/en-us/library/twa2aw10.aspx

Until these questions are satisfactorily answered (which at the moment seems impossible), it is unlikely that we will have a working libs11n DLL for Windows platforms. I have attempted to work around the problem by building with the MinGW/Cygwin tools, but so far no luck.

### 7.1.2 Build flags ###

Here is an overview of known build flags which might have to be set in order to compile the libs11n sources under the various Visual C++ environments:

> ● The WIN32 macro must be defined (the exact value is unimportant). It is believed to be defined automatically by the compiler, so this should be a no-op.

> ● The INCLUDES path must point to the top-most include directory shipped with the source tree (normally named include). The implementation files all refer to the public headers using fullyqualified names (e.g., <s11n.net/s11n/foo.hpp>), so they can find the headers as long as your INCLUDES path is set properly. Some exceptional headers are “internal-only” and live in the same directory as the source files. Implementation files include such headers using local-style includes (e.g. #include “foo.hpp”).

> ● Turn precompiled headers OFF. They will not work here.

> ● Make sure that the “C++ Language Extensions” option is turned on (the default), otherwise the code will fail to compile in <windows.h>. Like it or not, the core Windows headers require some Microsoftspecific extensions to the C++ language.

> ● The option to “Keep Unreferenced Data” must be explicitly enabled or classloading will not work. If you get exceptions saying that serializers cannot be loaded (for example) then this is almost certainly the problem. This is a side-effect of the way the classloader works, which requires the creation of anonymous objects at application (or DLL) initialization time in order to register loadable types with their classloader. By default, VC++ wants to strip out those anonymous objects.

The README.WIN32 file which comes with the source tree contains more detailed information about building libs11n on Win32 platforms.

## 7.2 Visual C++ Express ##

In August 2006 the first Win32 release of libs11n was made. It is packaged as a solution (project) file for Visual C++ Express, which is a freely-downloadable C++ compiler for Windows platforms, available from:

http://msdn.microsoft.com/vstudio/express/

Users may need to modify some parts (in particular, the INCLUDES path) to get it to compile on their system. It can, in any case, be used as a starting point for getting libs11n support into client-side applications.