package it.filippocrocchini.engine.common.graphics.model;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import org.lwjgl.BufferUtils;
import org.lwjgl.assimp.AIFace;
import org.lwjgl.assimp.AIMesh;
import org.lwjgl.assimp.AIVector3D;

public class Mesh {
	private String name;
	private AIMesh mesh;
	private int vertexArrayBuffer;
	private int normalArrayBuffer;
	private int elementArrayBuffer;
	private int elementCount;
	private int vao;
    
	public Mesh(AIMesh aiMesh) {
		this.mesh = aiMesh;
		name = aiMesh.mName().dataString();
	}

	public void load() {
		
		vao = glGenVertexArrays();
     	glBindVertexArray(vao);
     	
     	{ // ------  VERTICES  ------
	     	ByteBuffer vertexArrayBufferData = BufferUtils.createByteBuffer(mesh.mNumVertices() * 3 * Float.BYTES);
	        AIVector3D.Buffer vertices = mesh.mVertices();
	        for (int i = 0; i < mesh.mNumVertices(); ++i) {
	         	AIVector3D vert = vertices.get(i);
	         	vertexArrayBufferData.putFloat(vert.x());
	         	vertexArrayBufferData.putFloat(vert.z());
	         	vertexArrayBufferData.putFloat(vert.y());
	        }
	        vertexArrayBufferData.flip();
	        vertexArrayBuffer = glGenBuffers();
	        glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer);
	        glBufferData(GL_ARRAY_BUFFER, vertexArrayBufferData, GL_STATIC_DRAW);
	        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	        glEnableVertexAttribArray(0);
     	} // ------  VERTICES  ------
        
        { // ------  NORMALS  ------
	        
	        ByteBuffer normalArrayBufferData = BufferUtils.createByteBuffer(mesh.mNumVertices() * 3 * Float.BYTES);
	        AIVector3D.Buffer normals = mesh.mNormals();
	        for (int i = 0; i < mesh.mNumVertices(); ++i) {
	         	AIVector3D norm = normals.get(i);
	         	normalArrayBufferData.putFloat(norm.x());
	         	normalArrayBufferData.putFloat(norm.z());
	         	normalArrayBufferData.putFloat(norm.y());
	        }
	        normalArrayBufferData.flip();
	        normalArrayBuffer = glGenBuffers();
	        glBindBuffer(GL_ARRAY_BUFFER, normalArrayBuffer);
	        glBufferData(GL_ARRAY_BUFFER, normalArrayBufferData, GL_STATIC_DRAW);
	        glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
	        glEnableVertexAttribArray(1);
		} // ------  NORMALS  ------
        
        
        
        { // ------  ELEMENTS  ------
	        
	        int faceCount = mesh.mNumFaces();
	        elementCount = faceCount * 3;
	        IntBuffer elementArrayBufferData = BufferUtils.createIntBuffer(getElementCount());
	        AIFace.Buffer facesBuffer = mesh.mFaces();
	        for (int i = 0; i < faceCount; ++i) {
	            AIFace face = facesBuffer.get(i);
	            if (face.mNumIndices() != 3) {
	                 throw new IllegalStateException("AIFace.mNumIndices() != 3");
	            }
	            elementArrayBufferData.put(face.mIndices());
	        }
	        elementArrayBufferData.flip();
	        elementArrayBuffer = glGenBuffers();
	        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferData, GL_STATIC_DRAW);
        } // ------  ELEMENTS  ------
        
        glBindVertexArray(0);
	}

	public void cleanup() {
		glDeleteVertexArrays(vao);
    	glDeleteBuffers(vertexArrayBuffer);
    	glDeleteBuffers(normalArrayBuffer);
    	glDeleteBuffers(elementArrayBuffer);
    	
    	System.out.println("Cleaned up Mesh: " + name);
	}
	
	public int getVao() {
		return vao;
	}

	public int getElementCount() {
		return elementCount;
	}

}
