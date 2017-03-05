package it.filippocrocchini.engine.common.graphics;


import static org.lwjgl.assimp.Assimp.*;

import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_AMBIENT;
import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_DIFFUSE;
import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_SPECULAR;
import static org.lwjgl.assimp.Assimp.aiGetErrorString;
import static org.lwjgl.assimp.Assimp.aiGetMaterialColor;
import static org.lwjgl.assimp.Assimp.aiReleaseImport;
import static org.lwjgl.assimp.Assimp.aiTextureType_NONE;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import org.lwjgl.BufferUtils;
import org.lwjgl.PointerBuffer;
import org.lwjgl.assimp.AIColor4D;
import org.lwjgl.assimp.AIFace;
import org.lwjgl.assimp.AIMaterial;
import org.lwjgl.assimp.AIMesh;
import org.lwjgl.assimp.AIScene;
import org.lwjgl.assimp.AIVector3D;

import it.filippocrocchini.engine.common.resource.Resource;

@Deprecated
public class Model implements Resource{
    public AIScene scene;
    public List<Mesh> meshes;
    public List<Material> materials;
    public String pathToFile;
    
    public Model(String pathToFile) {
    	this.pathToFile = pathToFile;
    	meshes = new ArrayList<>();
    	materials = new ArrayList<>();
    }

    @Override
	public void onRawLoad() throws IOException {
        this.scene = aiImportFile(pathToFile, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);;

        int meshCount = scene.mNumMeshes();
        PointerBuffer meshesBuffer = scene.mMeshes();
        
        for (int i = 0; i < meshCount; ++i) {
            meshes.add(new Mesh(AIMesh.create(meshesBuffer.get(i))));
        }

        int materialCount = scene.mNumMaterials();
        PointerBuffer materialsBuffer = scene.mMaterials();
        
        for (int i = 0; i < materialCount; ++i) {
            materials.add(new Material(AIMaterial.create(materialsBuffer.get(i))));
        }
	}

    @Override
    public void onGlLoad() throws AssertionError {
    	for(Mesh mesh : meshes) {
    		mesh.bindToOpenGL();
    	}
    	//free();
    }

    public void free() {
    	aiReleaseImport(scene);
    	scene = null;
    	meshes = null;
    	materials = null;
    }

    public void glCleanup() {
    	for(Mesh mesh : meshes) {
	    	glDeleteVertexArrays(mesh.vao);
	    	glDeleteBuffers(mesh.vertexArrayBuffer);
	    	glDeleteBuffers(mesh.normalArrayBuffer);
	    	glDeleteBuffers(mesh.elementArrayBuffer);
	    	
	    	System.out.println("Cleaned up Mesh.");
    	}
    }

    public static class Mesh {

        public AIMesh mesh;
        public int vertexArrayBuffer;
        public int normalArrayBuffer;
        public int elementArrayBuffer;
        public int elementCount;
        public int vao;

        
        public double[] triangle = {
                0.0,     0.5, 0.0,
               -0.5,  -0.5, 0.0,
                0.5,    -1.5, 0.0
        };
         
        //the color data (red, green, and blue)
        public double[] color = {
                0.0, 1.0, 0.0, //first vertex color
                1.0, 0.0, 0.0, //second vertex color
                0.0, 0.0, 1.0, //third vertex color
        };
         
        //the order to render the vertices
        public int[] index = {
                0,
                1,
                2,
        };
        
        public Mesh(AIMesh mesh) {
            this.mesh = mesh;
        }
        
        public void bindToOpenGL() {
        	//TEMPLOADFUNCTION();

        	
        	
            
        }
        

//		private void TEMPLOADFUNCTION() {
//			//the vertex data (x and y)
//	       
//	         
//	        //convert the vertex data arrays into ByteBuffers using a method I created down below
//	        ByteBuffer vertices = storeArrayInBuffer(triangle);
//	        ByteBuffer colors = storeArrayInBuffer(color);
//	        ByteBuffer indices = storeArrayInBuffer(index);
//	         
//	        //VAO: stores pointers to all of the vbos to keep 'em organized
//	        //VBO: stores data (vertex coordinates, colors, indices, etc.) and a header that contains information about their format
//	         
//	        //tell the GPU to make a single vertex array and store the returned id into the VBO int
//	        vao = glGenVertexArrays();
//	         
//	        //set the current vertex array object
//	        glBindVertexArray(vao);
//	             
//	            //tell the gpu to make a VBO and store its ID in the 'coordVBO' varabile
//	            int coordVBO = glGenBuffers();
//	             
//	            //bind the 'coordVBO' VBO for use
//	            glBindBuffer(GL_ARRAY_BUFFER, coordVBO);
//	                 
//	                //we are currently inside the vertex array so this VBO is associated with 'coordVBO'
//	                //uploads VBO data (in this case, coords) to the GPU, tells some information about the VBO so that it can work as efficiently as possible
//	                //we are using STATIC_DRAW because "The data store contents will be speciﬁed once by the application...
//	                //...and used many times as the source for GL drawing and image speciﬁcation commands."
//	                glBufferData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
//	         
//	                //specifies information about the format of the VBO (number of values per vertex, data type, etc.)
//	                glVertexAttribPointer(0, 3, GL_DOUBLE, false, 0, 0);
//	                 
//	                //enable vertex attribute array 0
//	                glEnableVertexAttribArray(0);
//	             
//	            //create a second VBO for the colors
////	            int colorVBO = glGenBuffers();
//	             
//	            //bind the 'colorVBO' VBO for use
////	            glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//	                 
//	                //uploads VBO data (in this case, colors) to the GPU
////	                glBufferData(GL_ARRAY_BUFFER, colors, GL_STATIC_DRAW);
//	         
//	                //specifies information about the format of the VBO (number of values per vertex, data type, etc.)
////	                glVertexAttribPointer(1, 3, GL_DOUBLE, false, 0, 0);
//	                 
//	                //enable vertex attribute array 1
////	                glEnableVertexAttribArray(1);
//	             
//	            //create a third VBO for the indices (tells the GPU which vertices to render and when)
//	            int indicesVBO = glGenBuffers();
//	             
//	            //bind the 'indicesVBO' for use
//	            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
//	             
//	            //uploads VBO data (in this case, colors) to the GPU
//	                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
//	     
//	            //unbind the last bound VBO
//	            glBindBuffer(GL_ARRAY_BUFFER, 0);
//	 
//	        //unbind the currently bound VAO
//	        glBindVertexArray(0);			
//		}

		 public static ByteBuffer storeArrayInBuffer(double[] array) {
            ByteBuffer buffer = BufferUtils.createByteBuffer(array.length * 8); 
	        for(double i : array) {
	            buffer.putDouble(i);
	        }
	        buffer.position(0);
	        return buffer;
	    }
		     
	    public static ByteBuffer storeArrayInBuffer(int[] array) {
	        ByteBuffer buffer = BufferUtils.createByteBuffer(array.length * 4); 
	        for(int i : array) {
	            buffer.putInt(i);
	        }
	        buffer.position(0);
	        return buffer;
	    }
    }

    public static class Material {

        public AIMaterial mMaterial;
        public AIColor4D mAmbientColor;
        public AIColor4D mDiffuseColor;
        public AIColor4D mSpecularColor;

        public Material(AIMaterial material) {

            mMaterial = material;
            String errorLog;
            
            mAmbientColor = AIColor4D.create();
            if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_AMBIENT, aiTextureType_NONE, 0, mAmbientColor) != 0) {
            	errorLog = aiGetErrorString();
            	System.err.println("Failed to load ambient color.");
                if(errorLog.length() > 0)
                	System.err.println(errorLog);
            }
            
            mDiffuseColor = AIColor4D.create();
            if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_DIFFUSE, aiTextureType_NONE, 0, mDiffuseColor) != 0) {
            	errorLog = aiGetErrorString();
            	System.err.println("Failed to load diffuse color.");
                if(errorLog.length() > 0)
                	System.err.println(errorLog);
            }
            
            mSpecularColor = AIColor4D.create();
            if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_SPECULAR, aiTextureType_NONE, 0, mSpecularColor) != 0) {
            	errorLog = aiGetErrorString();
            	System.err.println("Failed to load specular color.");
                if(errorLog.length() > 0)
                	System.err.println(errorLog);
            }
        }
    }

}
