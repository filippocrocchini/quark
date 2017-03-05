package it.filippocrocchini.engine.common.graphics.particles;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;
import static org.lwjgl.opengl.GL31.*;
import static org.lwjgl.opengl.GL33.*;

public class ParticleBatch {
	public static int particleVAB;
	public static int particleEAB;
	public static boolean isInitialized;
	
	public int offsetArrayBuffer;
	public int batchVao;
	
	public int maxParticles;
	public int particleCount = 0;
	
	private boolean initialized;
	
	public static void init() {
		float[] vertices = {-.02f,-.02f,+.02f, +.02f,-.02f,-.02f, +.02f,+.02f,0, -.02f,+.02f,0};
		int[] indices = {3,0,2,1};
		
		particleVAB = glGenBuffers();
	    glBindBuffer(GL_ARRAY_BUFFER, particleVAB);
	    glBufferData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    particleEAB = glGenBuffers();
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, particleEAB);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	    isInitialized=true;
	}
	
	public ParticleBatch() {
	//	this.maxParticles = size;
	}
	
	public void render() {
		if(!isInitialized) {
			init();
		} else {
			if(!initialized) {
				initVAO();
			} else {
				glBindVertexArray(batchVao);
				glDrawElementsInstanced(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0, particleCount);
				glBindVertexArray(0);
			}
		}
		
	}
	
	private void initVAO() {
		batchVao = glGenVertexArrays();
		
		glBindVertexArray(batchVao);
		glBindBuffer(GL_ARRAY_BUFFER, particleVAB);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	    glEnableVertexAttribArray(0);

		offsetArrayBuffer = glGenBuffers();
		glBindBuffer(GL_ARRAY_BUFFER, offsetArrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, new float[] {1,1,1,-1,-1,-1}, GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribDivisor(1,1);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, particleEAB);
		glBindVertexArray(0);
		initialized = true;
	}

	public void setOffsetBuffer(float[] buffer) {
		particleCount = buffer.length/3;
		
		glBindBuffer(GL_ARRAY_BUFFER, offsetArrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, buffer, GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	public void cleanup() {
			glDeleteVertexArrays(batchVao);
	    	glDeleteBuffers(offsetArrayBuffer);
	}
	
	public boolean isInitialized() {
		return initialized;
	}
}
