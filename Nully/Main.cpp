#include "Nully.h"



using namespace Nully;

void main()
{
  NApplicationDesc applicationDesc = {};
  
  applicationDesc.windowDesc.width = 1024;
  applicationDesc.windowDesc.height = 768;
  applicationDesc.windowDesc.isFullScreen = false;
  applicationDesc.windowDesc.name = "Nully";
  applicationDesc.windowDesc.className = "NullyClass";
  applicationDesc.windowDesc.windowAlignment = NWindowAlignment::Center;

  applicationDesc.graphicsDesc.width = applicationDesc.windowDesc.width;
  applicationDesc.graphicsDesc.height = applicationDesc.windowDesc.height;
  applicationDesc.graphicsDesc.hwnd = 0;

  NApplication application;
  if (!application.Initialize(applicationDesc))
  {
    return; // failed to init app
  }

  application.Run();
}
