// Ogre-test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreLight.h>
#include <OGRE/OgreColourValue.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreMaterialManager.h>

//Control de FPS
#include "FixedFrameRate.h"

bool g_bKeepRendering= true;

WNDPROC g_ogreWinProc = NULL;
bool g_bUpPressed= false;
bool g_bDownPressed= false;
bool g_bLeftPressed= false; 
bool g_bRightPressed= false;


LRESULT APIENTRY SubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch(uMsg)
   {
		case WM_KEYDOWN:
		  switch (wParam)
		  {
			case VK_ESCAPE:
				g_bKeepRendering= false;
				break;
			case VK_UP:
				g_bUpPressed= true;
				break;
			case VK_DOWN:
				g_bDownPressed= true;
				break;
			case VK_LEFT:
				g_bLeftPressed= true;
				break;
			case VK_RIGHT:
				g_bRightPressed= true;
				break;
		  }
		  break;
		case WM_KEYUP:
			switch (wParam)
			{
			case VK_UP:
				g_bUpPressed= false;
				break;
			case VK_DOWN:
				g_bDownPressed= false;
				break;
			case VK_LEFT:
				g_bLeftPressed= false;
				break;
			case VK_RIGHT:
				g_bRightPressed= false;
				break;
			}
			break;
   }
   //AFTER PROCESSING THE MESSAGE, PASS IT TO OGRE
   return CallWindowProc(g_ogreWinProc, hwnd, uMsg, wParam, lParam);
}

int _tmain(int argc, char* argv[])
{
	//CONFIGURATION
	Ogre::Root *pRoot = new Ogre::Root("plugins.cfg");

 
	//bool bConfigured= pRoot->showConfigDialog();
	
	Ogre::RenderSystem* rs = pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	pRoot->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	//pRoot->saveConfig();

	//INITIALISATION
	pRoot->initialise(true,"MyWindow");
	Ogre::RenderWindow *pWindow= pRoot->getAutoCreatedWindow();

	//HACK: GET WINDOWS MESSAGES BEFORE OGRE DOES
	HWND hwnd;
	pWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
	g_ogreWinProc = (WNDPROC) SetWindowLong(hwnd, GWL_WNDPROC, (LONG) SubclassProc); 

	//SCENE MANAGER
	Ogre::SceneManager *pSceneManager= pRoot->createSceneManager(Ogre::ST_GENERIC,"MyManager");

	//CAMERA
	Ogre::Camera *pCamera= pSceneManager->createCamera("MainCamera");
	pCamera->setNearClipDistance(10.0);
	pCamera->setFarClipDistance(1000.0);
	pCamera->setAspectRatio(4.0/3.0);
	pCamera->setPosition(0.0,20.0,50.0);
	pCamera->lookAt(0.0,0.0,0.0);
	Ogre::Viewport *pViewport= pWindow->addViewport(pCamera);

	//LIGHT
	pSceneManager->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));
	Ogre::Light * pMainLight= pSceneManager->createLight("MainLight");
	pMainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	pMainLight->setPosition(0.0,20.0,0.0);
	pMainLight->setDirection(1.0,0.0,0.0);
	//pMainLight->setSpotlightRange(Ogre::Radian(0.4),Ogre::Radian(1.0),0.9);

	//SCENE OBJECTS
	Ogre::ResourceGroupManager *pRGManager= Ogre::ResourceGroupManager::getSingletonPtr();
	//1. add resource locations
	pRGManager->addResourceLocation("../media/materials/textures","FileSystem","General");
	pRGManager->addResourceLocation("../media/materials/scripts","FileSystem","General");
	pRGManager->addResourceLocation("../media/models","FileSystem","General");
	pRGManager->addResourceLocation("../media/materials/programs/hlsl","FileSystem","General");
	pRGManager->addResourceLocation("../media/RTShaderLib/GLSL","FileSystem","General");
	pRGManager->addResourceLocation("../media/materials/programs/GLSL","FileSystem","General");
	//2. initialise(index) resource groups
	pRGManager->initialiseAllResourceGroups();


	//add instances to the scene manager
	//1.get Root node
	Ogre::SceneNode *pRootNode= pSceneManager->getRootSceneNode();
	//2.create object(s)
	Ogre::Entity *pOgreEntity= pSceneManager->createEntity("penguin.mesh");

	Ogre::Entity *pNinjaEntity= pSceneManager->createEntity("ninja.mesh");

	Ogre::Entity *pWoodEntity= pSceneManager->createEntity("WoodPallet.mesh");


	//3.attach objects to node
	Ogre::SceneNode *pOgreChildNode;
	pOgreChildNode = pRootNode->createChildSceneNode();
	pOgreChildNode->scale(0.1,0.1,0.1);
	pOgreChildNode->attachObject(pOgreEntity);

	Ogre::SceneNode *pNinjaChildNode;
	pNinjaChildNode = pRootNode->createChildSceneNode();
	pNinjaChildNode->setPosition(20.0,0.0,0.0);
	pNinjaChildNode->scale(0.1,0.1,0.1);
	pNinjaChildNode->yaw(Ogre::Radian(1.57));
	pNinjaChildNode->attachObject(pNinjaEntity);

	Ogre::SceneNode *pWoodChildNode;
	pWoodChildNode = pRootNode->createChildSceneNode();
	pWoodChildNode->attachObject(pWoodEntity);


	while (g_bKeepRendering)
	{
		//Inicio control de framerate
		startFrame();

		//Read Windows Messages
		MSG Msg;
		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		//move camera?
		if (g_bLeftPressed)
			pCamera->yaw(Ogre::Radian(0.005));
		if (g_bRightPressed)
			pCamera->yaw(Ogre::Radian(-0.005));
		if (g_bUpPressed)
			pCamera->moveRelative(Ogre::Vector3(0.0,0.0,-0.5));
		if (g_bDownPressed)
			pCamera->moveRelative(Ogre::Vector3(0.0,0.0,0.5));

		//rotate ogre
		pOgreChildNode->yaw(Ogre::Radian(0.001));
		
		//Finalizacion del control de framerate
		endFrame();
		duration();

		//Renderizado del siguiente frame
		pRoot->renderOneFrame();
	}

	return 0;
}

