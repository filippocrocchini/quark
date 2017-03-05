package it.filippocrocchini.engine.common.graphics.shaders;

import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL11.*;

public class Shader {
	private int type;
	private String source;
	private String compileLog;
	private boolean compileStatus = false;
	private int id;
	
	public Shader(int type, String source) {
		this.type = type;
		this.source = source;
		this.id = 0;
	}
	
	public boolean compile() {
		this.id = glCreateShader(type);
        glShaderSource(getId(), source);
        glCompileShader(getId());
        
        if(glGetShaderi(getId(), GL_COMPILE_STATUS) == GL_FALSE) {
        	compileLog = glGetShaderInfoLog(getId());
        	return compileStatus = false;
        }
        return compileStatus = true;
	}
	
	public String getCompileLog() {
		if(compileStatus) return "Compilation OK.";
		return compileLog;
	}

	public int getId() {
		return id;
	}

	public int getType() {
		return type;
	}

	public String getSource() {
		return source;
	}

	public boolean compiled() {
		return compileStatus;
	}
	
	
}
