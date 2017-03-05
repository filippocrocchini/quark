package it.filippocrocchini.engine.common.graphics.model;

import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL11.GL_UNSIGNED_INT;
import static org.lwjgl.opengl.GL11.glDrawElements;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL15.GL_ELEMENT_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL15.glBindBuffer;
import static org.lwjgl.opengl.GL15.glBufferData;
import static org.lwjgl.opengl.GL15.glGenBuffers;
import static org.lwjgl.opengl.GL20.glEnableVertexAttribArray;
import static org.lwjgl.opengl.GL20.glVertexAttribPointer;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;

import java.util.HashMap;
import java.util.Map;

public final class Primitive {
	public static enum Type{
		LINE,
		VECTOR,
		SQUARE,
		PARTICLE
	}	
	private static Map<Primitive.Type, Primitive> primitives = new HashMap<Primitive.Type, Primitive>();
	
	public float[] vertexBufferData;
	public int vertexArrayBuffer;
	public int elementArrayBuffer;
	public int elementCount;
	public int vao;
	
	private int drawMethod = GL_LINES;
	
	public Primitive(float[] vertices, int vertexDrawMethod, int[] indices, int indexDrawMethod, int primitiveDrawMethod) {
		this.drawMethod = primitiveDrawMethod;
		this.vertexBufferData = vertices;
		
		vao = glGenVertexArrays();
		
     	glBindVertexArray(vao);
     	
     	{ // ------  VERTICES  ------
	        vertexArrayBuffer = glGenBuffers();
	        glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer);
	        glBufferData(GL_ARRAY_BUFFER, vertexBufferData, vertexDrawMethod);
	        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	        glEnableVertexAttribArray(0);
     	} // ------  VERTICES  ------
        
        
        { // ------  ELEMENTS  ------
	        elementArrayBuffer = glGenBuffers();
	        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices, indexDrawMethod);
        } // ------  ELEMENTS  ------
        
        glBindVertexArray(0);
        
        elementCount = indices.length;
	}
	
	public static Primitive get(Type type) {
		if(primitives.containsKey(type)) return primitives.get(type);
		Primitive p;
		switch(type) {
			case LINE:
				p = new Primitive(new float[] {0,0,0,0,0,5}, GL_STATIC_DRAW, new int[] {0,1}, GL_STATIC_DRAW, GL_LINES); 
				break;
			case VECTOR:
				p = new Primitive(new float[] {0,0,0,1,1,1}, GL_STREAM_DRAW, new int[] {0,1}, GL_STATIC_DRAW, GL_LINES); 
				break;
			case SQUARE:
				p = new Primitive(new float[] {0,0,0, 1,0,0, 1,1,0, 1,0,0}, GL_STATIC_DRAW, new int[] {0,1,2,3}, GL_STATIC_DRAW, GL_TRIANGLE_FAN); 
				break;
			case PARTICLE:
				p = new Primitive(new float[] {-.5f,-.5f,+.5f, +.5f,-.5f,-.5f, +.5f,+.5f,0, -.5f,+.5f,0}, GL_STATIC_DRAW, new int[] {3,0,2,1}, GL_STATIC_DRAW, GL_TRIANGLE_FAN); 
				break;
			default:
				p = null;
		}
		
		if( p!= null)
			primitives.put(type, p);
		
		return p;
	}
	
	public static void render(Type type) {
		Primitive p = get(type);
		if(p != null) {
			glDisable(GL_CULL_FACE);
			glBindVertexArray(p.vao);
			glDrawElements(p.drawMethod, p.elementCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glEnable(GL_CULL_FACE);
		}
	}
	
	public static void renderVector(float x, float y, float z, float size) {
		Primitive p = get(Type.VECTOR);
		if(p != null) {
			p.vertexBufferData[3] = x * size;
			p.vertexBufferData[4] = y * size;
			p.vertexBufferData[5] = z * size;
			
			glBindVertexArray(p.vao);
			
			glBindBuffer(GL_ARRAY_BUFFER, p.vertexArrayBuffer);
	        glBufferData(GL_ARRAY_BUFFER, p.vertexBufferData, GL_STREAM_DRAW);
	        
			glDrawElements(p.drawMethod, p.elementCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}
