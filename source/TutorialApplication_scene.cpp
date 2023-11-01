//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
//
// Purpose: Set the scenes. 
//
//
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createObjectGroup1_SphereGroup(void) {
    mNumOfItems = 12;
    mItemGroupRadius = 200;

    for (int i = 0; i < mNumOfItems; ++i) {
        double x, y, z;
        x = y = z = 0;
        double a = i / (double)mNumOfItems * PI * 2;
        x = mItemGroupRadius * cos(a);
        z = mItemGroupRadius * sin(a);

        String ename;
        genNameUsingIndex("item", i, ename);
        Entity* ent = mSceneMgr->createEntity(
            ename, "sphere.mesh");
        ent->setMaterialName("Examples/SceneCubeMap1");
        //ent->setMaterialName("Examples/SceneCubeMap1");

        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        double scaleFactor = 0.2;
        snode->setScale(scaleFactor, scaleFactor, scaleFactor);
        snode->setPosition(x, y, z);
        snode->attachObject(ent);

        const AxisAlignedBox bb = ent->getBoundingBox();
        Real itemSize = bb.getMaximum().x - bb.getMinimum().x;
        snode->translate(0, scaleFactor * itemSize / 2.0, 0);
        mItemArr[i] = snode;
        mItemStatus[i] = ITEM_STATE_INACTIVE;
        //
        //
        //mVelocityArr[0] = Vector3( 1.0, 2.0, 1.0);
        mVelocityArr[i] = -mItemArr[i]->getPosition();
        mVelocityArr[i].normalise();
        mVelocityArr[i].y = 2.0;
        mVelocityArr[i].normalise();
        mVelocityArr[i] = 170 * mVelocityArr[i];
    }
};


//大波浪在大企鵝旁邊
void BasicTutorial_00::createObjectGroup2_WavyCircle( ) 
{   
    //Real == float 用在存3d渲染
    
    int numCubes = 128;
    double L = 255, Pi = 3.141592654;
    for (int i = 0; i < numCubes; ++i)
    {
        String name;
        genNameUsingIndex("c", i, name);
        //先定義好entity 在指定材質
        Entity* ent = mSceneMgr->createEntity(name, "cube.mesh");
        ent->setMaterialName("Examples/SphereMappedRustySteel");
        const AxisAlignedBox bb = ent->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double x = 0, y = 0, z = -125;
        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        snode->attachObject(ent);
        double fx;
        double h;

        fx = i / (double)(numCubes - 1); //in range [0, 1]
        h = (1 + sin(fx * Pi * 8.0)) * 50;
        double wave = (1 + 2 * sin(fx * Pi * 8.0)) * 10;
        double circle_radius = 100 + wave;
        x = circle_radius * cos(fx * Pi * 2);
        z = circle_radius * sin(fx * Pi * 2);
        Real unitF = 1.0 / cubeSize / numCubes * L * 0.8;
        snode->scale(unitF, h / cubeSize, unitF);
        snode->setPosition(x, 50, z);
    }
}

void BasicTutorial_00::createObjectGroup3_Wave()
{
    int numCubes = 128;
    double L = 255;

    for (int i = 0; i < numCubes; ++i)
    {
        String name;
        genNameUsingIndex("d", i, name);
        Entity* ent = mSceneMgr->createEntity(
            name, "cube.mesh");
        ent->setMaterialName("Examples/Chrome");
        const AxisAlignedBox bb = ent->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double x = 0, y = 0, z = 125;
        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        snode->attachObject(ent);
        double fx;
        double h;

        fx = 2 * i / (double)(numCubes - 1); 
        x = fx * L - L / 2.0;
        h = (1 + cos(fx * 3.1415 * 2.0)) * 20;
        Real unitF = 1.0 / cubeSize / numCubes * L * 0.8;
        snode->scale(unitF, h / cubeSize, unitF);
        snode->setPosition(x, 20, z);
    }

}

void BasicTutorial_00::createLights( ) 
{
    mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
    //mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
    mSceneMgr->setShadowTechnique(
        SHADOWTYPE_STENCIL_ADDITIVE); 

    Light *light;
    light = mSceneMgr->createLight("Light1"); 
    light->setType(Light::LT_POINT); 
    light->setPosition(Vector3(150, 250, 100));
    //散射
    light->setDiffuseColour(0.0, 1.0, 0.0);		
    //鏡面反射
    light->setSpecularColour(0.0, 1.0, 0.0);	


    Light* light2;
    //yellow light
    light2 = mSceneMgr->createLight("Light2");
    light2->setType(Light::LT_POINT);
    light2->setPosition(Vector3(-150, 300, 250));
    light2->setDiffuseColour(1.0, 0.0, 0.0);//漫反射
    light2->setSpecularColour(1.0, 0.0, 0.0);//镜面反射

}




void BasicTutorial_00::createPets( )
{
    Entity *ent2 
        = mSceneMgr
        ->createEntity("Small_penguin", READER_DATA::getMeshName_Pet());
       // ->createEntity( "Robot2", READER_DATA::getMeshName_Pet( ) ); 

    SceneNode *node2 
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode( 
        "Small_PenguinNode2"); 
        
    node2->yaw( 
        Degree( READER_DATA::getYawAngleDegreeOffset_Pet( ) ) 
        );
    
    node2->attachObject( ent2 );


    Entity *ent22 
        = mSceneMgr
        ->createEntity("Large_Penguin", READER_DATA::getMeshName_Pet());
        //->createEntity( "Robot22", READER_DATA::getMeshName_Pet( ) ); 

     //初始化SceneNode
    SceneNode *node22 
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode( 
        "Large_PenguinNode22"); 
    //Enity 綁定 Node
    node22->attachObject( ent22 );
    //大小
    node22->scale(2, 3, 2);
    node22->setPosition(0, 45, 0);

    //調整小企鵝方向位置
    if (READER_DATA::getFlgAutoPlaceObj()) {
        Ogre::LogManager::getSingletonPtr()->logMessage("READER_DATA::getFlgAutoPlaceObj()***");

        AxisAlignedBox bb;
        Real obj_min_y;
        //
        bb = ent2->getBoundingBox();
        //
        //
        //
    }

    mMovableObj = node2;
    mTargetObj = node22;

}

// 
// Create a mesh and assign it a name. 
// After that, we use the mesh name to create entities.
//
void BasicTutorial_00::createPlaneObjectResource( )
{
    Plane plane(Vector3::UNIT_Y, 0); 
    MeshManager::getSingleton().createPlane(
        "plane_object_resource", 						
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
        plane, 
        1500,1500, 	// width, height
        20,20, 		// x- and y-segments
        true, 		// normal
        1, 			// num texture sets
        5,5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
        ); 
}

void BasicTutorial_00::createFloor( )
{
  
    Entity* ent = mSceneMgr->createEntity(
        "FloorEntity", "plane_object_resource"
    );
    ent->setMaterialName("Examples/green");

    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            Vector3(0.0, -35, 0.0))
        ->attachObject(ent);
}


void BasicTutorial_00::createWall( )
{
    Entity *ent = mSceneMgr->createEntity(
        "Background", "plane_object_resource"); 
    //ent->setMaterialName("Examples/BeachStones");
    //ent->setMaterialName("Examples/Rockwall");
    ent->setMaterialName( READER_DATA::getMaterialName_Wall( ) );

    Radian angle(3.141952654/2.0);
    //Radian angle(3.141952654 / 4.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
        Vector3(0.0, 0.0, -750.0),
        Quaternion( angle, axis))
        ->attachObject(ent);
}

void BasicTutorial_00::createPlane2() {


    Plane plane(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane(
        "vv",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1000, 1000, 	// width, height
        20, 20, 		// x- and y-segments
        true, 		// normal
        1, 			// num texture sets
        5, 5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
    );

    Entity* ent = mSceneMgr->createEntity(
        "Plane2", "vv");
    ent->setMaterialName("Examples/green");

    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            Vector3(0.0, 0, 0.0))
        ->attachObject(ent);


}

void BasicTutorial_00::createPlane2_cube() {
    Entity* ent
        = mSceneMgr
        ->createEntity("Large_Cube", "cube.mesh");
    ent->setMaterialName("Examples/SphereMappedRustySteel");

    //->createEntity( "Robot22", READER_DATA::getMeshName_Pet( ) ); 

 //初始化SceneNode
    SceneNode* node22
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            "Large_Cube22");
    //Enity 綁定 Node
    node22->attachObject(ent);
    //大小
    node22->scale(0.2, 0.3, 0.2);
    node22->setPosition(2, 10, 0);

}

//
// Set mSceneMgr = mSceneMgrArr[0];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_00(void) 
{
    mSceneMgr = mSceneMgrArr[0];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // Enjoy modular programming experience
    ////////////////////////////////////////////////////
    createLights( );
    createPets( );
    UpdateMovableObjPosition();
    createPlaneObjectResource( );
    createFloor( );
    createWall( );
    
    //
    createObjectGroup1_SphereGroup();   
    createObjectGroup2_WavyCircle();
    createObjectGroup3_Wave( );
}


//
// Set mSceneMgr = mSceneMgrArr[1];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_01(void)
{
    ////////////////////////////////////////////////////
    mSceneMgr = mSceneMgrArr[1];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    //mSceneMgr->setAmbientLight( ColourValue( 1.0,1.0, 1.0 ) ); 
    mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
    //mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

    
    Light *light = mSceneMgr->createLight("Light1");
    light->setType(Light::LT_POINT);
    light->setPosition(Vector3(100, 150, 250));
    light->setDiffuseColour(0.0, 0.0, 1.0);
    light->setSpecularColour(0.0, 0.0, 1.0);
    
    //ent3->setMaterialName("Examples/green");
    createPlane2();
    createPlane2_cube();

}