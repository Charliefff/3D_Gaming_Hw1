//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

//
// Constructor
//
// When an object of BasicTutorial_00 is created, 
// a constructor will be invoked.
// 
// Initialize data members.
//
BasicTutorial_00::BasicTutorial_00(void)
    : mFlg_MoveObj(false)
    , mFlg_CounterClockwise(true)
    , mAngle(0.0)
    , mRadius(SystemParameter::radius)
    , mMaxSpeed(SystemParameter::maxSpeed)
    , mAngularAcceleration(SystemParameter::acceleration)
    , mTopViewportIndex(1)
    , mViewportArrangementIndex(1)
{
    initViewportDimensions( );
}

//
// Set viewport dimension information.
//
void BasicTutorial_00::initViewportDimensions() {
//
// There are four viewports for the second scene, or the scene shown on top.

    mViewportDim[0].left = 0.15;
    mViewportDim[0].top = 0;
    mViewportDim[0].width = 0.3;
    mViewportDim[0].height = 0.3;
    //
    mViewportDim[1].left = 0.15;
    mViewportDim[1].top = 0.15;
    mViewportDim[1].width = 0.5;
    mViewportDim[1].height = 0.25;
    //
    mViewportDim[2].left = 0;
    mViewportDim[2].top = 0.25;
    mViewportDim[2].width = 0.25;
    mViewportDim[2].height = 0.5;
    //
    mViewportDim[3].left = 0.15;
    mViewportDim[3].top = 0.15;
    mViewportDim[3].width = 0.25;
    mViewportDim[3].height = 0.25;
}

//
// chooseSceneManager is invoked in the setup process.
//
//
// Call mRoot->createSceneManager(type, name) 
// to create a scene manager.
//
void BasicTutorial_00::chooseSceneManager()
{
    mSceneMgrArr[0] = mRoot
        ->createSceneManager(ST_GENERIC, "primary");
    mSceneMgrArr[1] = mRoot
        ->createSceneManager(ST_GENERIC, "secondary");
}

//
// Create a camera for mSceneMgrArr[0]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[0] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_00(void)
{
    mSceneMgr = mSceneMgrArr[0];
    mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCamera");
    mCamera->setPosition(Ogre::Vector3(120,300,600));
    mCamera->lookAt(Ogre::Vector3(120,0,0));
    //
    // near clipping distance
    //
    mCamera->setNearClipDistance(5);            
    //
    // create a default camera controller
    //
    mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   
}

//
// Create a camera for mSceneMgrArr[1]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[1] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_01(void)
{
    mSceneMgr = mSceneMgrArr[1];
    mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCamera");
    mCamera->setPosition(Ogre::Vector3(0,350, 0.001));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    //
    mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   
}


//
// Create a viewport for the camera, mCameraArr[0].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//
void BasicTutorial_00::createViewport_00(void)
{
    mCamera = mCameraArr[0];
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    //­I´ºÃC¦â
    vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
    
    double viewport_width = Ogre::Real(vp->getActualWidth());
    double viewport_height = Ogre::Real(vp->getActualHeight());

    mCamera->setAspectRatio( viewport_width/ viewport_height );
    //
    // Store the viewport point vp. 
    // So we can use the pointer later.
    //
    mViewportArr[0] = vp;
}

//
// Create a viewport for the camera, mCameraArr[1].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//

void BasicTutorial_00::createViewport_01(void)
{
    mCamera = mCameraArr[1];

    Ogre::Viewport* vp1 = mWindow->addViewport(
        mCamera,
        1,
        0,
        0.0,
        0.25,
        0.25
        );
    vp1->setBackgroundColour(Ogre::ColourValue(0, 0.8, 0.4, 0.1));
    
    double viewport_width = Ogre::Real(vp1->getActualWidth());
    double viewport_height = Ogre::Real(vp1->getActualHeight());

    mCamera->setAspectRatio( viewport_width/ viewport_height );
    //
    // Make the overlay invisible in this viewport.
    //
    vp1->setOverlaysEnabled(false);
    //
    mViewportArr[1] = vp1;
}

//
// createViewports is invoked in the setup process.
//
void BasicTutorial_00::createViewports(void)
{
    createViewport_00();
    createViewport_01();
}

//
// createCamera is invoked in the setup process.
//
void BasicTutorial_00::createCamera(void) {
    createCamera_00();
    createCamera_01();
    //
    // A controller recieves mouse and keyboard events.
    // In this system, only one controller can be active.
    // and the other controllers are inactive.
    //
    // Set one controller as active.
    // In this case, we set mCameraManArr[0] to be active.
    // mCameraMan is used in the base class, BaseApplication.
    // The mouse and keyboard events are passed to mCameraMan.
    // Thus, we set mCameraMan = mCameraManArr[0] for the main scene.
    //

    // Set mCameraManArr[0] as active.
    mCameraMan = mCameraManArr[0];

    // Set mCameraManArr[1] as active.
    //mCameraMan = mCameraManArr[1];    
}


//
// We invokde the data reader to read parameter values
// which are stored in a text file.
// After that, we use the data reader READER_DATA 
// to access the parameter values.
// 
// At the end of this function, set the active camera.
//
void BasicTutorial_00::createScene( void ) {

    Ogre::LogManager::getSingletonPtr()->logMessage( "DATA_Reader::Read");
    READER_DATA::readData( );
    //
    createScene_00();
    createScene_01();
    //mSceneMgr = mSceneMgrArr[0];  // active SceneManager
    mSceneMgr = mSceneMgrArr[1];    // active SceneManager
    //
    //
    mCamera = mCameraArr[0];        // active camera
    //mCamera = mCameraArr[1];      // active camera
}

//
// keyPressed is invoked when a keyboard key is pressed.
// 
//
// What is stored in arg.key?
// Store its data to the log file 
// and then check the log file, i.e., Ogre.log
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
//
// When we handle the key events, 
// we should set the states of our game objects.
// We will update the game objects in the update function.
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    /////////////////////////////////////////////////////////
    // Convert arg.key to a stringstream object.
    // Then convert the stringstream object as a String object.
    // Finally, save the string object to the log file.
    stringstream ss;
    //
    // Convert arg.key to a String object
    //
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );
    /////////////////////////////////////////////////////////

    bool flg_handled = false;

    flg_handled = handleKeyEvents( arg );
    
    //
    // For the keys that are not handled,
    // call BaseApplication::keyPressed(arg) to handle the events.
    // We need the active controller to handle some key events. 
    //
    // In BaseApplication::keyPressed(),
    // mShutDown = true is set when the ESCAPE key is pressed.
    // Our application will be shut down in the main loop.
    //
    if (!flg_handled) BaseApplication::keyPressed(arg);

    return flg;
}

//
// keyReleased is invoked when a keyboard key is released.
// 
// What is stored in arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
// Store its data to the log file 
// and then check the log file, i.e., Ogre.log
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    //
    // Convert arg.key to a String object
    //
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";

    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

//
// frameStarted( ... ) is invoked each frame
//
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
    bool flg = Ogre::FrameListener::frameStarted(evt);

    if (!flg) return flg;

    flg = updateGameState( evt.timeSinceLastFrame );

    return flg;
}

int main(int argc, char *argv[]) {

    (new BasicTutorial_00)->go( );

    return 0;
}
