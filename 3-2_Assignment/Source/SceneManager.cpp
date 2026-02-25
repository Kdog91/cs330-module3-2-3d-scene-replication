///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// ============
// manage the preparing and rendering of 3D scenes - textures, materials, lighting
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

// declaration of global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager *pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 *  SetTransformations()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	// set the scale value in the transform buffer
	scale = glm::scale(scaleXYZ);
	// set the rotation values in the transform buffer
	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	// set the translation value in the transform buffer
	translation = glm::translate(positionXYZ);

	// matrix math for calculating the final model matrix
	modelView = translation * rotationZ * rotationY * rotationX * scale;

	if (NULL != m_pShaderManager)
	{
		// pass the model matrix into the shader
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		// pass the color values into the shader
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene 
 *  rendering
 ***********************************************************/
void SceneManager::PrepareScene()
{
	// only one instance of a particular mesh needs to be
	// loaded in memory no matter how many times it is drawn
	// in the rendered 3D scene

    // Table
    m_basicMeshes->LoadPlaneMesh();

    // Mug parts
    m_basicMeshes->LoadCylinderMesh();   // body, rim, base
    m_basicMeshes->LoadTorusMesh(0.1);      // rim
    m_basicMeshes->LoadExtraTorusMesh1();  //handle
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by 
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
    glm::vec3 scaleXYZ;
    glm::vec3 positionXYZ;

    // =========================
    // TABLE
    // =========================
    scaleXYZ = glm::vec3(20.0f, 1.0f, 12.0f);
    positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);

    SetTransformations(scaleXYZ, 0, 0, 0, positionXYZ);
    SetShaderColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_basicMeshes->DrawPlaneMesh();

    // =========================
// COFFEE MUG (FINAL – PROFESSOR CORRECT)
// =========================

    float mugX = -6.0f;
    float mugHeight = 2.0f;// 4.5f;
    float outerRadius = 1.0f;
    float innerRadius = 0.7f;

    // ---------- OUTER MUG BODY ----------
    scaleXYZ = glm::vec3(outerRadius, mugHeight, outerRadius);
    positionXYZ = glm::vec3(
        mugX,
        0.15,//mugHeight/2,
        0.0f
    );

    SetTransformations(scaleXYZ, 0, 0, 0, positionXYZ);
    SetShaderColor(0.18f, 0.45f, 0.85f, 1.0f);
    m_basicMeshes->DrawCylinderMesh(false, true, true);

    // ---------- INNER HOLLOW (FAKE CUP) ----------
    //scaleXYZ = glm::vec3(innerRadius, mugHeight - 0.5f, innerRadius);
    //positionXYZ = glm::vec3(
    //    mugX,
    //    (mugHeight - 0.5f) / 2.0f + 0.25f,
    //    0.0f
    //);

    //SetTransformations(scaleXYZ, 0, 0, 0, positionXYZ);
    // same color as table to simulate hollow
    //SetShaderColor(1.0f, 1.0f, 1.0f, 1.0f);
    //m_basicMeshes->DrawCylinderMesh();

    // ---------- RIM (FLAT TORUS ON TOP) ----------
    scaleXYZ = glm::vec3(.9, 0.15, .9);// 1.05f, 1.05f, 0.25f);
    positionXYZ = glm::vec3(
        mugX,
        mugHeight + 0.15,
        0.0f
    );

    // rotate to lay flat
    SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
    SetShaderColor(0.22f, 0.52f, 0.9f, 1.0f);
    m_basicMeshes->DrawTorusMesh();

    // ---------- HANDLE (CORRECT WRAP) ----------
    scaleXYZ = glm::vec3(0.5, 0.35, 0.6);// 0.8f, 0.8f, 0.35f);
    positionXYZ = glm::vec3(
        mugX + outerRadius + 0.1f,
        mugHeight / 2.0f,
        0.0f
    );

    // THIS is the correct rotation for a mug handle
    SetTransformations(scaleXYZ, 90.0f, 0.0f, 0.0f, positionXYZ);
    SetShaderColor(0.95f, 0.55f, 0.15f, 1.0f);
    m_basicMeshes->DrawExtraTorusMesh1();

}