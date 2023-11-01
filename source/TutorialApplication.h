//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
/*!
\brief 3D Game Programming
\n
My Name: AA BB CC
\n
My ID: 0123456789
\n
My Email: aaa@cs.nctu.edu.tw
\n Date: 2022/08/17

This is an assignment of 3D Game Programming

REMARK:
You are allowed to delete the functions 
and data members that you do not want to use.
You can define your own data members and functions.
*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "reader_data.h"
#include "SystemParameter.h"

#define PI 3.141592654

struct ViewportDim {
    float left, top, width, height;
};

class BasicTutorial_00 : public BaseApplication
{
protected:
    enum ITEM_STATE{
         ITEM_STATE_INACTIVE = 0,  
         ITEM_STATE_ACTIVE = 1,  
         ITEM_STATE_DONE = 2 
    };
public:
	BasicTutorial_00(void);

    //
protected:
    virtual void initViewportDimensions();
    virtual void createViewports(void);
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void chooseSceneManager(void);
    //
    virtual bool frameStarted(const Ogre::FrameEvent& evt);

	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();
    //
    void createObjectGroup1_SphereGroup();
    void createObjectGroup2_WavyCircle();
    void createObjectGroup3_Wave();
	void createScene_00();
    //
	void createScene_01();

    //
    void createPlaneObjectResource( );
    void createFloor( );
    void createWall( );
    void createLights( );
    void createPets( );
    void createPlane2();
    void createPlane2_cube();


    void updatePets( double time_step );
    void updateSpheres( double time_step );

    
    bool handleKeyEvents_GetCameraInformation( const OIS::KeyEvent &arg );
    bool handleKeyEvents_Camera( const OIS::KeyEvent &arg );
    bool handleKeyEvents_Viewport( const OIS::KeyEvent &arg );
    bool handleKeyEvents_Animation( const OIS::KeyEvent &arg );
    
    
    //


    // return true if the key event has been handled
    //
    bool handleKeyEvents( const OIS::KeyEvent &arg );        
    bool updateGameState(double dt);    // dt time step size
    //
    void resetItems( );
    void activateOneItem( );
    //
    void UpdateMovableObjPosition(bool flg_large = false);
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );

protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
    double mAngle;
    double mRadius;
    double mAngularSpeed;
    double mAngularAcceleration;
    double mMaxSpeed;
    Ogre::SceneNode *mMovableObj;
    Ogre::SceneNode *mTargetObj;
    bool mFlg_MoveObj;
    bool mFlg_CounterClockwise;
    Ogre::Vector3 mVelocity;
    //
    int mNumOfItems;
    Ogre::SceneNode *mItemArr[32];
    ITEM_STATE mItemStatus[32];
    Ogre::Vector3 mVelocityArr[32];
    double mItemGroupRadius;
    //
    ViewportDim mViewportDim[4];
    int mTopViewportIndex;
    int mViewportArrangementIndex;
};

#endif // #ifndef __BasicTutorial_00_h_