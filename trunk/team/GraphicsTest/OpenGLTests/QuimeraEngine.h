
#ifndef __QUIMERAENGINE__
#define __QUIMERAENGINE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QGraphicsEngine.h"
#include "QResourceManager.h"
#include "QWindow.h"

class QuimeraEngine
{
public:

    static void Initilize(QDeviceContext* pDeviceContext);

    static bool IsInitialized();

    static QuimeraEngine* Get();

    QGraphicsEngine*  Graphics;
    QResourceManager* Resources;
    // QSceneManager* Scenes;

private:

    static QGraphicsEngine* _CreateGraphicsEngine(QDeviceContext* pDeviceContext, QResourceManager* pResourceManager);

    static QResourceManager* _CreateResourceManager();

    static QuimeraEngine* sm_pQuimeraEngine;
    static bool sm_bInitialized;
};

#define QE QuimeraEngine::Get()

#endif // __QUIMERAENGINE__