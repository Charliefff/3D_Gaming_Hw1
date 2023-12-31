//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
//header guard
#ifndef __READER_DATA_H__
#define __READER_DATA_H__

#include <string>

class READER_DATA {
protected:
	
	static std::string mMeshName_Pet;
    static double mYawAngleDegreeOffset_Pet;
    static double mMeshScale_Pet;
    static bool mEnabledAutoPlaceObject;
    //
	static std::string mMaterialName_Floor;
	static std::string mMaterialName_Wall;
    //
    static bool mEnabledShadow;

    static double mAimAtSphereAngleDeviation;
    //
public:
	READER_DATA();
	static void readData();
    //

	static std::string getMeshName_Pet();
    static double getYawAngleDegreeOffset_Pet();
    static double getMeshScale_Pet();
    static bool getFlgAutoPlaceObj();
    //
	static std::string getMaterialName_Floor();
	static std::string getMaterialName_Wall();

    //
    static double getAimAtSphereAngleDeviation( );
    	static bool isEnabledShadow( );
//
static void report();
};

#endif