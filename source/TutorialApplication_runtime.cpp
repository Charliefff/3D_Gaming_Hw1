//
// 3D Game Programming
// NYCU
// Instructor: Sai-Keung Wong
//
//
// Purpose: Update the game state, 
// including object states, game progress, physics simulation, 
// collision detection, collision response, and etc.
//
//
// The functions will be invoked at the runtime stage.
//
// Example: 
// Handle key events to control the camera.
// Handle key events to set viewports.
// Handle key events to obtain the camera information.
// Handle key events to activate the items, i.e., spheres.
// Update the spheres.
// Update the pets.
// And others
// 
// A key handler handles simple tasks, 
// such as setting the states of game objects. 
//
//

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;

//
// Handle key events for controlling the active camera.
//
// Set the camera position and its lookat position.
//
bool BasicTutorial_00::handleKeyEvents_Camera( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;
    if (arg.key == OIS::KC_1 ) {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(0, 100, 597.32));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0, 0, -0.99));
    }


    if (arg.key == OIS::KC_2 ) {
        flg_handled = true;
        
        mCameraMan->getCamera()
            ->setPosition(Vector3(-151.32, 200, 542.68));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.10, -0.18, -0.98));
    }

    if (arg.key == OIS::KC_3 ) {
        flg_handled = true;
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1000.00, 609.45, 300.24));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47, -0.2));
    }

    if (arg.key == OIS::KC_4 ) {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(-1356.16, 634.32, -964.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.71, -0.44, 0.55));
       //setPosition(Vector3(-1356.16,	634.32,	-964.51));
       //setDirection(Vector3(0.71,	-0.44,	0.55));
    }

    if (arg.key == OIS::KC_5 ) {
        flg_handled = true;
        mCameraMan->getCamera()
            ->setPosition(Vector3(40.39, 155.23, 251.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.02, -0.41, -0.91));
        //setPosition(Vector3(40.39,	155.23,	251.20));
        //setDirection(Vector3(-0.02,	-0.41,	-0.91));
    }

    if (arg.key == OIS::KC_6 ) {
        flg_handled = true;
        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94, 822.63, 30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01, -1.00, -0.05));
       //setPosition(Vector3(19.94,	822.63,	30.79));
       //setDirection(Vector3(-0.01, - 1.00, - 0.05));
    }
    return flg_handled;
}

//
// Set the viewport attributes, 
// e.g., background colours, dimensions and locations.
//
bool BasicTutorial_00::handleKeyEvents_Viewport( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;

    if (arg.key == OIS::KC_M ) {
        double viewport_width, viewport_height;
        flg_handled = true;
        //remove orginal view port 
        mWindow->removeViewport(mViewportArr[0]->getZOrder());
        mWindow->removeViewport(mViewportArr[1]->getZOrder());

        // create new view port
        mCamera = mCameraArr[0];
        Ogre::Viewport* vp = mWindow->addViewport(
            mCamera,
            1,
            0,
            0.0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(0, 0.8, 0));
        viewport_height = Ogre::Real(vp->getActualHeight());
        viewport_width = Ogre::Real(vp->getActualWidth());
        mCamera->setAspectRatio(viewport_width / viewport_height);
        vp->setOverlaysEnabled(false);
        mViewportArr[0] = vp;

        mCamera = mCameraArr[1];
        Ogre::Viewport* vp1 = mWindow->addViewport(
            mCamera);
        vp1->setBackgroundColour(Ogre::ColourValue(0, 0, 1));
        viewport_height = Ogre::Real(vp1->getActualHeight());
        viewport_width = Ogre::Real(vp1->getActualWidth());
        mCamera->setAspectRatio(viewport_width / viewport_height);
        vp1->setOverlaysEnabled(false);
        mViewportArr[1] = vp1;
    }

    if (arg.key == OIS::KC_N ) {
        double viewport_width, viewport_height;

        flg_handled = true;
        //remove orginal view port 
        mWindow->removeViewport(mViewportArr[0]->getZOrder());
        mWindow->removeViewport(mViewportArr[1]->getZOrder());

        // create new view port
        mCamera = mCameraArr[1];
        Ogre::Viewport* vp = mWindow->addViewport(
            mCamera,
            1,
            0.75,
            0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(1, 0.8, 0.4, 0.4));
        viewport_height = Ogre::Real(vp->getActualHeight());
        viewport_width = Ogre::Real(vp->getActualWidth());
        mCamera->setAspectRatio(viewport_width / viewport_height);
        vp->setOverlaysEnabled(false);
        mViewportArr[1] = vp;

        mCamera = mCameraArr[0];
        Ogre::Viewport* vp1 = mWindow->addViewport(
            mCamera);
        vp1->setBackgroundColour(Ogre::ColourValue(1, 0, 0));
        viewport_height = Ogre::Real(vp1->getActualHeight());
        viewport_width = Ogre::Real(vp1->getActualWidth());
        mCamera->setAspectRatio(viewport_width / viewport_height);
        vp1->setOverlaysEnabled(false);
        mViewportArr[0] = vp1;
    }

    if (arg.key == OIS::KC_B) {
        flg_handled = true;
        Ogre::Viewport* vp;

        if (mViewportArr[1]->getZOrder() > mViewportArr[0]->getZOrder()) {
            vp = mViewportArr[1];
        }
        else {
            vp = mViewportArr[0];
        }
        double top = vp->getTop();
        double left = vp->getLeft();

        if (left == 0.75 && top == 0) {
            vp->setDimensions(0.75, 0.75, 0.25, 0.25);
        }
        else if (left == 0.75 && top == 0.75) {
            vp->setDimensions(0, 0.75, 0.25, 0.25);
        }
        else if (left == 0 && top == 0.75) {
            vp->setDimensions(0, 0, 0.25, 0.25);
        }
        else if (left == 0.0 && top == 0.0) {
            vp->setDimensions(0.75, 0, 0.25, 0.25);
        }
    }

    return flg_handled;
}

//
// Set the object states for animation or simulation.
// Try not to perform complex tasks in a key handler.
//
bool BasicTutorial_00::handleKeyEvents_Animation( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;
    if ( arg.key == OIS::KC_P ) {
        flg_handled = true;
        if (mFlg_MoveObj == true) {
            mFlg_MoveObj = false;
        }
        else {
            mFlg_MoveObj = true;
        }
    }

    if ( arg.key == OIS::KC_SPACE ) 
    {
        flg_handled = true;
        activateOneItem();
    }
    if ( arg.key == OIS::KC_K ) 
    {
        flg_handled = true;
        //
        //
        //
    }
    return flg_handled;
}

//
// Get the camera position and direction.
// Save them to the log file.
//
bool BasicTutorial_00::handleKeyEvents_GetCameraInformation( const OIS::KeyEvent &arg ) 
{
    bool flg_handled = false;

    stringstream ss;
    if (arg.key == OIS::KC_C ) {

        flg_handled = true;

        //How to clear ss?
        ss.str("");
        ss.clear();

        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camera position?
        //-----------------------------
        // This is incorrect.
        // Vector3 pos = mCamera->getPosition();
        // The controller may have its own 
        // set of attributes to control the camera.
        //
        //We use the controller to get the camera information.
        //-----------------------------
        //
        //
        // The following is correct.
        //
        Vector3 pos = mCameraMan->getCamera()->getPosition(); 
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();

        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";

        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
    }

    return flg_handled;
}


//
// return true if the key event has been handled
//
bool BasicTutorial_00::handleKeyEvents( const OIS::KeyEvent &arg )
{
    bool flg_handled = false;

    //
    // Use the OR operator to turn on the flag
    //
    // Make sure that the same key is not used in
    // two or more functions.
    //
    flg_handled |= handleKeyEvents_GetCameraInformation( arg );
    flg_handled |= handleKeyEvents_Camera( arg );
    flg_handled |= handleKeyEvents_Viewport( arg );
    flg_handled |= handleKeyEvents_Animation( arg );

    return flg_handled;
}

//
// Set the position, status, and velocity of each item.
// 
// 
void BasicTutorial_00::resetItems( ) {
    //
    //
    //
}

//
// Find one item and activate it.
// To activate an item, set its state properly.
//
// The item is pointed to by the small pet 
// rotating about the center pet.
//
// The center pet is at the original, 
// Thus use the position vector of the small pet and the position vector
// of the item (i.e., the sphere). 
// If the angle deviation between these two vectors is smaller than 
// a threshold, pick the item and activate it.
// So, use dot product? do we need to compute the actual angle? 
// use acos?
//
// We will update the item based on the state of the item 
// in the main update function.
//
void BasicTutorial_00::activateOneItem( ) {
    double angle_deviation = READER_DATA::getAimAtSphereAngleDeviation( );

    Vector3 move_position = mMovableObj->getPosition();
    move_position.y = 0;
    for (int i = 0; i < 12; i++) {
        Vector3 pos = mItemArr[i]->getPosition();
        pos.y = 0;
        if (pos.angleBetween(move_position).valueDegrees() < angle_deviation) {
            mItemStatus[i] = ITEM_STATE_ACTIVE;
        }
    }
}

//
// Update the states of objects.
// The states of objects include positions, 
// velocities, colours, materials, etc.
//
void BasicTutorial_00::UpdateMovableObjPosition(bool flg_large)
{
    Vector3 pos = mMovableObj->getPosition();
    pos.x = mRadius*cos(mAngle);
    pos.z = mRadius*sin(mAngle);
    mMovableObj->setPosition(pos);

    Vector3 q = mTargetObj->getPosition();

    q.y = pos.y;
    mMovableObj->lookAt(q, Node::TransformSpace::TS_WORLD);
    mMovableObj->yaw(
        Degree( READER_DATA::getYawAngleDegreeOffset_Pet( ) )
        );
}

//
// Update the states of the spheres.
// In our case, the states include positions and velocities.
// Furthermore, if a sphere position is lower than the floor, 
// set the status of the sphere as ITEM_STATE_DONE. 
//
void BasicTutorial_00::updateSpheres( double time_step )
{
    double mag = 120;
    Vector3 force_gravity = mag*Vector3( 0.0, -1.0, 0.0 );
    double dt = time_step;
    
    for (int i = 0; i < 12; i++) {
        if (mItemStatus[i] == ITEM_STATE_ACTIVE) {
            if (mItemArr[i]->getPosition().y > 0) {
                mVelocityArr[i] += force_gravity * dt;
                mItemArr[i]->setPosition(mItemArr[i]->getPosition() + mVelocityArr[i] * dt);
            }
            else {
                mItemStatus[i] = ITEM_STATE_DONE;
            }
        }
    }
}

//
// Update the pets.
//
// Rotate the two pets and make them look at each other.
// Rotate the small pet in counter-clockwise direction 
// and then clockwise direction. Repeat the process.
//
// dt is the simulation time step size.
//
void BasicTutorial_00::updatePets( double dt )
{
    if (!mFlg_MoveObj) return;
    //¬Ý¤p¥øÃZ
    mTargetObj->lookAt(mMovableObj->getPosition() + Vector3(0, 45, 0), Node::TransformSpace::TS_WORLD);
    mTargetObj->yaw(Degree(180));

    if (mAngularSpeed < mMaxSpeed) {
        mAngularSpeed += mAngularAcceleration * dt;
    }
    mAngle += mAngularSpeed * dt * (mFlg_CounterClockwise ? -1 : 1);
    UpdateMovableObjPosition();
    if (mAngle < -6.26 || mAngle > 6.26) {
        mAngle = mAngularSpeed = 0;
        mFlg_CounterClockwise = mFlg_CounterClockwise ? false : true;
    }
}

//
// Purpose: Update the game state based on the game logic.
//
// return true if everything is normal. 
// return false to quit the program.
// 
// dt is the simulation time step size
//
bool BasicTutorial_00::updateGameState(double dt)
{
    bool flg = true; 

    updatePets( dt );
    updateSpheres( dt );

    return flg;
}
