/*===============================================================================
Copyright (c) 2012-2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of QUALCOMM Incorporated, registered in the United States 
and other countries. Trademarks of QUALCOMM Incorporated are used with permission.
===============================================================================*/

package com.qualcomm.vuforia.samples.VuforiaSamples.app.ImageTargets;


import java.io.IOException;
import java.util.Vector;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;
import android.content.Context;

import com.qualcomm.vuforia.Matrix44F;
import com.qualcomm.vuforia.Renderer;
import com.qualcomm.vuforia.State;
import com.qualcomm.vuforia.Tool;
import com.qualcomm.vuforia.Trackable;
import com.qualcomm.vuforia.TrackableResult;
import com.qualcomm.vuforia.VIDEO_BACKGROUND_REFLECTION;
import com.qualcomm.vuforia.Vuforia;
import com.qualcomm.vuforia.samples.SampleApplication.SampleApplicationSession;
import com.qualcomm.vuforia.samples.SampleApplication.utils.CubeShaders;
import com.qualcomm.vuforia.samples.SampleApplication.utils.LoadingDialogHandler;
import com.qualcomm.vuforia.samples.SampleApplication.utils.SampleApplication3DModel;
import com.qualcomm.vuforia.samples.SampleApplication.utils.SampleUtils;
import com.qualcomm.vuforia.samples.SampleApplication.utils.CubeObject;
import com.qualcomm.vuforia.samples.SampleApplication.utils.Texture;


//////////////

 
// The renderer class for the ImageTargets sample. 
public class ImageTargetRenderer implements GLSurfaceView.Renderer
{
    private static final String LOGTAG = "ImageTargetRenderer";
    
    private SampleApplicationSession vuforiaAppSession;
    private ImageTargets mActivity;
    
    private Vector<Texture> mTextures;
    
    private int shaderProgramID;
    
    private int vertexHandle;
    
    private int normalHandle;
    
    private int textureCoordHandle;
    
    private int mvpMatrixHandle;
    
    private int texSampler2DHandle;
    
    private CubeObject mcubeObject;
    
    //private float kBuildingScale = 12.0f;
    private SampleApplication3DModel mBuildingsModel;
    
    private Renderer mRenderer;
    
    boolean mIsActive = false;
    Context context;
    
    private static final float OBJECT_SCALE_FLOAT = 8.0f;
 
    
    public ImageTargetRenderer(ImageTargets activity,
        SampleApplicationSession session) //throws FileNotFoundException, IOException, ParcelFormatException
    {
    	
        mActivity = activity;
        vuforiaAppSession = session;
    }
    
   
    // Called to draw the current frame.
    @Override
    public void onDrawFrame(GL10 gl)
    {
        if (!mIsActive)
            return;
        
        // Call our function to render content
        renderFrame();
    }
    
    
    // Called when the surface is created or recreated.
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        Log.d(LOGTAG, "GLRenderer.onSurfaceCreated");
        
        initRendering();
        
        // Call Vuforia function to (re)initialize rendering after first use
        // or after OpenGL ES context was lost (e.g. after onPause/onResume):
        vuforiaAppSession.onSurfaceCreated();
    }
    
    
    // Called when the surface changed size.
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        Log.d(LOGTAG, "GLRenderer.onSurfaceChanged");
        
        // Call Vuforia function to handle render surface size changes:
        vuforiaAppSession.onSurfaceChanged(width, height);
    }
    
    
    // Function for initializing the renderer.
    private void initRendering()
    {
    	mcubeObject = new CubeObject();
        
        mRenderer = Renderer.getInstance();
        
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, Vuforia.requiresAlpha() ? 0.0f
            : 1.0f);
        
        for (Texture t : mTextures)
        {
            GLES20.glGenTextures(1, t.mTextureID, 0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, t.mTextureID[0]);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
            GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA,
                t.mWidth, t.mHeight, 0, GLES20.GL_RGBA,
                GLES20.GL_UNSIGNED_BYTE, t.mData);
        }
        
        shaderProgramID = SampleUtils.createProgramFromShaderSrc(
            CubeShaders.CUBE_MESH_VERTEX_SHADER,
            CubeShaders.CUBE_MESH_FRAGMENT_SHADER);
        
        vertexHandle = GLES20.glGetAttribLocation(shaderProgramID,
            "vertexPosition");
        normalHandle = GLES20.glGetAttribLocation(shaderProgramID,
            "vertexNormal");
        textureCoordHandle = GLES20.glGetAttribLocation(shaderProgramID,
            "vertexTexCoord");
        mvpMatrixHandle = GLES20.glGetUniformLocation(shaderProgramID,
            "modelViewProjectionMatrix");
        texSampler2DHandle = GLES20.glGetUniformLocation(shaderProgramID,
            "texSampler2D");
        
        try
        {
            mBuildingsModel = new SampleApplication3DModel();
            mBuildingsModel.loadModel(mActivity.getResources().getAssets(),
                "ImageTargets/Buildings.txt");
        } catch (IOException e)
        {
            Log.e(LOGTAG, "Unable to load buildings");
        }
        
        // Hide the Loading Dialog
        mActivity.loadingDialogHandler
            .sendEmptyMessage(LoadingDialogHandler.HIDE_LOADING_DIALOG);
        
    }
    
  /*
   *  This method finds the index of a texture name in JSONArray corresponding to  "allTexturesNames" field in JSON file. 
   * Input : texture name and JSONArray corresponding to  "allTexturesNames".
   * Output : index of texture name in input JSONArray.
   *
   */
    private int returnIndex(String name, JSONArray array) {
    	
    	for(int i = 0; i < array.length(); i++) {
    		try {
				if(name.equals(array.getString(i)))
					return i;
			} catch (JSONException e) {
				
				Log.d(LOGTAG, "JSON Exception occured.");
			}
    	}
    	return -1; // if no texture name is given. 
    }
    // The render function.
    
    ImageTargets imgtarget = new ImageTargets(); //Creating instance to obtain various items such as json object,
    // list of texture names and names of all the files in dataset etc which were computed in parseFile() method.
    public static JSONArray ListOfDatasetFiles = null;
    static JSONObject jsonObj = null;
    static JSONArray textureNameList = null;
    
    private void renderFrame()
    {
    	
    	
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
        
        State state = mRenderer.begin();
        mRenderer.drawVideoBackground();
        
        GLES20.glEnable(GLES20.GL_DEPTH_TEST);
        
        // handle face culling, we need to detect if we are using reflection to determine the direction of the culling
       // GLES20.glEnable(GLES20.GL_CULL_FACE);  //$$$$$$$$$$ This was commented.
        GLES20.glCullFace(GLES20.GL_BACK);
        if (Renderer.getInstance().getVideoBackgroundConfig().getReflection() == VIDEO_BACKGROUND_REFLECTION.VIDEO_BACKGROUND_REFLECTION_ON)
            GLES20.glFrontFace(GLES20.GL_CW); // Front camera
        else
            GLES20.glFrontFace(GLES20.GL_CCW); // Back camera
               
       
        String currentDatasetFileName = null;
        
        ListOfDatasetFiles = ImageTargets.DatasetFilesNamesList;  // List to store names of all dataset files present in the device dataset.. 
        JSONArray textureListForAFile = null;    // List to store textures files for each item in dataset.
        
		 jsonObj = ImageTargets.jsonObj;
        int textureIndex1 = 0,textureIndex2 = 0,textureIndex3 = 0; //textureIndex "i" for ith plane for i = 1,2,3
        boolean plane1 = false ,plane2 = false,plane3 = false; 
        textureNameList = ImageTargets.texturesNameList;
        for (int tIdx = 0; tIdx < state.getNumTrackableResults(); tIdx++) 
        {
            TrackableResult result = state.getTrackableResult(tIdx);
            Trackable trackable = result.getTrackable();
            printUserData(trackable);
            Matrix44F modelViewMatrix_Vuforia = Tool
                .convertPose2GLMatrix(result.getPose());
            
            
            
            //Added code starts from here
            
            String textureName1,textureName2,textureName3;
            for ( int i = 0; i < ListOfDatasetFiles.length(); i++) {
            	
            	try {
            		currentDatasetFileName = ListOfDatasetFiles.getString(i);
            		
					if (trackable.getName().equals(currentDatasetFileName)) {
						textureListForAFile = jsonObj.getJSONArray(currentDatasetFileName);
						
						textureName1 = textureListForAFile.getString(0); // Getting texture name for plane 1.
            	    	textureIndex1 = returnIndex(textureName1,textureNameList);
            	    	plane1 = (textureIndex1 != -1);
            	    	
            	    	textureName2 = textureListForAFile.getString(1); // Getting texture name for plane 2.
            	    	textureIndex2 = returnIndex(textureName2,textureNameList);            	    
            	    	plane2 = (textureIndex2 != -1);
            	    	
            	    	textureName3 = textureListForAFile.getString(2); // Getting texture name for plane 3.
            	    	textureIndex3 = returnIndex(textureName3,textureNameList);
            	    	plane3 = (textureIndex3 != -1);
            	   }
				} catch (JSONException e) {
					
					Log.d(LOGTAG, "JSON Exception occured.");
				}
            	
            	
            }
              
             

        /********Here starts the code for Plane 1 over the camera screen.****/
            if (plane1) { //Selecting plane 1 and Plane 2.
            // deal with the modelview and projection matrices
            float[] modelViewMatrix1 = modelViewMatrix_Vuforia.getData();
            float[] modelViewProjection1 = new float[16];
           
            Matrix.translateM(modelViewMatrix1, 0, 20.0f, 0.0f,(float)4.0);
            Matrix.scaleM(modelViewMatrix1, 0, OBJECT_SCALE_FLOAT,
                    OBJECT_SCALE_FLOAT, (float) 0.0); //making last argument 0 from OBJECT_SCALE_FLOAT
            Matrix.multiplyMM(modelViewProjection1, 0, vuforiaAppSession
                .getProjectionMatrix().getData(), 0, modelViewMatrix1, 0);
            
            // activate the shader program and bind the vertex/normal/tex coords
            GLES20.glUseProgram(shaderProgramID);
                 
                    
                GLES20.glVertexAttribPointer(vertexHandle, 3, GLES20.GL_FLOAT,
                    false, 0, mcubeObject.getVertices());
                GLES20.glVertexAttribPointer(normalHandle, 3, GLES20.GL_FLOAT,
                    false, 0, mcubeObject.getNormals());
                GLES20.glVertexAttribPointer(textureCoordHandle, 2,
                    GLES20.GL_FLOAT, false, 0, mcubeObject.getTexCoords());
                
                GLES20.glEnableVertexAttribArray(vertexHandle);
                GLES20.glEnableVertexAttribArray(normalHandle);
                GLES20.glEnableVertexAttribArray(textureCoordHandle);
                
                // activate texture 0, bind it, and pass to shader
                GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
                GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,
                    mTextures.get(textureIndex1).mTextureID[0]);
                GLES20.glUniform1i(texSampler2DHandle, 0);
                
                // pass the model view matrix to the shader
                GLES20.glUniformMatrix4fv(mvpMatrixHandle, 1, false,
                    modelViewProjection1, 0);
                
                // finally draw the teapot
                GLES20.glDrawElements(GLES20.GL_TRIANGLES,
                		mcubeObject.getNumObjectIndex(), GLES20.GL_UNSIGNED_SHORT,               
                		mcubeObject.getIndices());
                
                // disable the enabled arrays
                GLES20.glDisableVertexAttribArray(vertexHandle);
                GLES20.glDisableVertexAttribArray(normalHandle);
                GLES20.glDisableVertexAttribArray(textureCoordHandle);            
                SampleUtils.checkGLError("Render Frame");        
            }
           /************************Plane 1 ends here.************************/    
            
 /********************************Duplicacy starts here.For plane 2****************************************/
               if (plane2) {              
                float[] modelViewMatrix2 = modelViewMatrix_Vuforia.getData();
                float[] modelViewProjection2 = new float[16];

                Matrix.translateM(modelViewMatrix2, 0, 0.0f, -20.0f,(float)4.0);
                Matrix.scaleM(modelViewMatrix2, 0, OBJECT_SCALE_FLOAT,
                		OBJECT_SCALE_FLOAT, (float) 0.0); //making last argument 0 from OBJECT_SCALE_FLOAT
                Matrix.multiplyMM(modelViewProjection2, 0, vuforiaAppSession
                    .getProjectionMatrix().getData(), 0, modelViewMatrix2, 0);
                
                // activate the shader program and bind the vertex/normal/tex coords
                GLES20.glUseProgram(shaderProgramID);           
             
                    GLES20.glVertexAttribPointer(vertexHandle, 3, GLES20.GL_FLOAT,
                        false, 0, mcubeObject.getVertices());
                    GLES20.glVertexAttribPointer(normalHandle, 3, GLES20.GL_FLOAT,
                        false, 0, mcubeObject.getNormals());
                    GLES20.glVertexAttribPointer(textureCoordHandle, 2,
                        GLES20.GL_FLOAT, false, 0, mcubeObject.getTexCoords());
                    
                    GLES20.glEnableVertexAttribArray(vertexHandle);
                    GLES20.glEnableVertexAttribArray(normalHandle);
                    GLES20.glEnableVertexAttribArray(textureCoordHandle);
                    
                    // activate texture 0, bind it, and pass to shader
                    GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
                    GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,
                        mTextures.get(textureIndex2).mTextureID[0]);
                    GLES20.glUniform1i(texSampler2DHandle, 0);
                    
                    // pass the model view matrix to the shader
                    GLES20.glUniformMatrix4fv(mvpMatrixHandle, 1, false,
                        modelViewProjection2, 0);
                    
                    // finally draw the teapot
                    GLES20.glDrawElements(GLES20.GL_TRIANGLES,
                    		mcubeObject.getNumObjectIndex(), GLES20.GL_UNSIGNED_SHORT,               
                    		mcubeObject.getIndices());
                    
                    // disable the enabled arrays
                    GLES20.glDisableVertexAttribArray(vertexHandle);
                    GLES20.glDisableVertexAttribArray(normalHandle);
                    GLES20.glDisableVertexAttribArray(textureCoordHandle);            
                    SampleUtils.checkGLError("Render Frame");  
                
   /*******************************Plane 2 ends here.*****************************************************/
               }
   /******************************** Plane 3 starts here.****************************************/
                    if ( plane3) { //Plane 2 and Plane 3 are selected.                  
                    float[] modelViewMatrix3 = modelViewMatrix_Vuforia.getData();
                    float[] modelViewProjection3 = new float[16];

                    Matrix.translateM(modelViewMatrix3, 0, -20.0f, 0.0f,(float)4.0);
                    Matrix.scaleM(modelViewMatrix3, 0, OBJECT_SCALE_FLOAT,
                    		OBJECT_SCALE_FLOAT, (float) 0.0); //making last argument 0 from OBJECT_SCALE_FLOAT toreduce one dimension.
                    Matrix.multiplyMM(modelViewProjection3, 0, vuforiaAppSession
                        .getProjectionMatrix().getData(), 0, modelViewMatrix3, 0);
                    
                    // activate the shader program and bind the vertex/normal/tex coords
                    GLES20.glUseProgram(shaderProgramID);
                    
                /****Here starts the code for drawing plane(1) over the camera screen.****/
                 
                        GLES20.glVertexAttribPointer(vertexHandle, 3, GLES20.GL_FLOAT,
                            false, 0, mcubeObject.getVertices());
                        GLES20.glVertexAttribPointer(normalHandle, 3, GLES20.GL_FLOAT,
                            false, 0, mcubeObject.getNormals());
                        GLES20.glVertexAttribPointer(textureCoordHandle, 2,
                            GLES20.GL_FLOAT, false, 0, mcubeObject.getTexCoords());
                        
                        GLES20.glEnableVertexAttribArray(vertexHandle);
                        GLES20.glEnableVertexAttribArray(normalHandle);
                        GLES20.glEnableVertexAttribArray(textureCoordHandle);
                        
                        // activate texture 0, bind it, and pass to shader
                        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
                        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,
                            mTextures.get(textureIndex3).mTextureID[0]);
                        GLES20.glUniform1i(texSampler2DHandle, 0);
                        
                        // pass the model view matrix to the shader
                        GLES20.glUniformMatrix4fv(mvpMatrixHandle, 1, false,
                            modelViewProjection3, 0);
                        
                        // finally draw the teapot
                        GLES20.glDrawElements(GLES20.GL_TRIANGLES,
                        		mcubeObject.getNumObjectIndex(), GLES20.GL_UNSIGNED_SHORT,               
                        		mcubeObject.getIndices());
                        
                        // disable the enabled arrays
                        GLES20.glDisableVertexAttribArray(vertexHandle);
                        GLES20.glDisableVertexAttribArray(normalHandle);
                        GLES20.glDisableVertexAttribArray(textureCoordHandle);            
                        SampleUtils.checkGLError("Render Frame");  
                    
   /*******************************Plane 3 ends here.*****************************************************/
                    }
                    
        }  // Outer for ends here.
               GLES20.glDisable(GLES20.GL_DEPTH_TEST);
        
        mRenderer.end();
    }
    
    
    private void printUserData(Trackable trackable)
    {
        String userData = (String) trackable.getUserData();
        Log.d(LOGTAG, "UserData:Retreived User Data	\"" + userData + "\"");
    }
    
    
    public void setTextures(Vector<Texture> textures)
    {
        mTextures = textures;
        
    }
    
}