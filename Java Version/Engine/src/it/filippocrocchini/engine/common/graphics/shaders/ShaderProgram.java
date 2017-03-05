package it.filippocrocchini.engine.common.graphics.shaders;

import java.io.IOException;
import java.nio.FloatBuffer;

import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.lwjgl.BufferUtils;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.resource.Resource;
import static org.lwjgl.opengl.GL20.*;

public class ShaderProgram implements Resource{
	public Shader vertexShader;
	public Shader fragmentShader;
	
	public int programIndex;
	
	public String name;
	//private int vertexAttribute;
	//private int normalAttribute;
	
	private int modelMatrixUniform;
	private int viewMatrixUniform;
	private int projectionMatrixUniform;
	private int viewProjectionMatrixUniform;
	private int normalMatrixUniform;
	private int modelColorUniform;

	/*
	private int lightPositionUniform;
	private int ambientColorUniform;
	private int diffuseColorUniform;
	private int specularColorUniform;
	private FloatBuffer lightPositionBuffer = BufferUtils.createFloatBuffer(3);
	*/
	
	private FloatBuffer modelMatrixBuffer = BufferUtils.createFloatBuffer(4 * 4);
    private FloatBuffer viewMatrixBuffer = BufferUtils.createFloatBuffer(4 * 4);
    private FloatBuffer projectionMatrixBuffer = BufferUtils.createFloatBuffer(4 * 4);
    private FloatBuffer viewProjectionMatrixBuffer = BufferUtils.createFloatBuffer(4 * 4);  
    
    private FloatBuffer normalMatrixBuffer = BufferUtils.createFloatBuffer(4 * 4);
    
    
    public ShaderProgram(String vertexSource, String fragmentSource) {
		this.vertexShader = new Shader(GL_VERTEX_SHADER, vertexSource);
		this.fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentSource);
	}
	
//    public ShaderProgram(VertexShader vertex, FragmentShader fragment) {
//		this.vertexShader = vertex;
//		this.fragmentShader = fragment;
//	}
    
	public ShaderProgram(String shaderName) {
		this.name = shaderName;
	}

	@Override
	public void onRawLoad() throws IOException {
		Engine.python.exec("script = parseShaderFromFile('assets/shaders/"+ this.name +".shader')");
		
		if(Engine.python.get("script").__nonzero__()) {
			this.vertexShader = new Shader(GL_VERTEX_SHADER, Engine.python.eval("script.getVertexSource()").asString());
			this.fragmentShader = new Shader(GL_FRAGMENT_SHADER, Engine.python.eval("script.getFragmentSource()").asString());
		} else {
			throw new IOException("Failed parsing '" + this.name + "' shader.");
		}
	}

	@Override
	public void onGlLoad() throws AssertionError{
		
		vertexShader.compile();
		fragmentShader.compile();
		
		if(vertexShader.compiled()) {
			System.out.println("VertexShader compile log: OK");
		} else {
			System.err.println("----------------VERTEX SHADER---------------");
			System.err.println(vertexShader.getSource() + "\n-------------------ERROR--------------------");
			System.err.println(vertexShader.getCompileLog());
            throw new AssertionError("Could not compile Vertex Shader");
		}
		
		if(fragmentShader.compiled()) {
			System.out.println("FragmentShader compile log: OK");
		} else {
			System.err.println("---------------FRAGMENT SHADER--------------");
			System.err.println(fragmentShader.getSource() + "\n-------------------ERROR--------------------");
			System.err.println(fragmentShader.getCompileLog());
            throw new AssertionError("Could not compile Fragment Shader");
		}
		
		programIndex = glCreateProgram();
		
		glBindAttribLocation(programIndex, 0, "position");
        glBindAttribLocation(programIndex, 1, "normal");
        
        glAttachShader(programIndex, vertexShader.getId());
        glAttachShader(programIndex, fragmentShader.getId());
        
        //glBindAttribLocation(programIndex, 0, "aVertex");
        //glBindAttribLocation(programIndex, 1, "color");
        
        glLinkProgram(programIndex);
        
        int linkStatus = glGetProgrami(programIndex, GL_LINK_STATUS);
        String programLog = glGetProgramInfoLog(programIndex);
        
        if (programLog.length() > 0 && programLog.trim().length() > 0) {
            System.err.println(programLog);
        }
        if (linkStatus == 0) {
            throw new AssertionError("Could not link program");
        }
        
        glValidateProgram(programIndex);
        
        programLog = glGetProgramInfoLog(programIndex);
        
        if (programLog.length() > 0 && programLog.trim().length() > 0) {
            System.err.println(programLog);
        }
        
        glDetachShader(programIndex, vertexShader.getId());
        glDetachShader(programIndex, fragmentShader.getId());
        
        
        modelMatrixUniform = glGetUniformLocation(programIndex, "uModelMatrix");
        viewMatrixUniform = glGetUniformLocation(programIndex, "uViewMatrix");
        projectionMatrixUniform = glGetUniformLocation(programIndex, "uProjectionMatrix");
        viewProjectionMatrixUniform = glGetUniformLocation(programIndex, "uViewProjectionMatrix");

        normalMatrixUniform = glGetUniformLocation(programIndex, "uNormalMatrix");
        modelColorUniform = glGetUniformLocation(programIndex, "uColor");

       /* 
        lightPositionUniform = glGetUniformLocationARB(programIndex, "uLightPosition");
        ambientColorUniform = glGetUniformLocationARB(programIndex, "uAmbientColor");
        diffuseColorUniform = glGetUniformLocationARB(programIndex, "uDiffuseColor");
        specularColorUniform = glGetUniformLocationARB(programIndex, "uSpecularColor");
        */
	}
	
	/***
	 * 
	 * @param modelMatrixs
	 * @return True if the modelMatrixUniform "uModelMatrix" has been found.
	 */
	public boolean setModelMatrixUniform(Matrix4f modelMatrix) {
		if(modelMatrixUniform >= 0) {
			glUniformMatrix4fv(modelMatrixUniform, false, modelMatrix.get(modelMatrixBuffer));
			glUniformMatrix4fv(normalMatrixUniform, false, modelMatrix.invert().transpose().get(normalMatrixBuffer));
			return true;
		}
		return false;
	}
	
	/***
	 * 
	 * @param viewMatrix
	 * @return True if the viewMatrixUniform "uViewMatrix" has been found.
	 */
	public boolean setViewMatrixUniform(Matrix4f viewMatrix) {
		if(viewMatrixUniform >= 0) {
			glUniformMatrix4fv(viewMatrixUniform, false, viewMatrix.get(viewMatrixBuffer));
			return true;
		}
		return false;
	}
	
	
	/***
	 * 
	 * @param projectionMatrix
	 * @return True if the projectionMatrixUniform "uProjectionMatrix" has been found.
	 */
	public boolean setProjectionMatrixUniform(Matrix4f projectionMatrix) {
		if(projectionMatrixUniform >= 0) {
			glUniformMatrix4fv(projectionMatrixUniform, false, projectionMatrix.get(projectionMatrixBuffer));
			return true;
		}
		return false;
	}
	
	/***
	 * 
	 * @param viewProjectionMatrix
	 * @return True if the viewProjectionMatrixUniform "uViewProjectionMatrix" has been found.
	 */
	public boolean setViewProjectionMatrixUniform(Matrix4f viewProjectionMatrix) {
		if(viewProjectionMatrixUniform >= 0) {
			glUniformMatrix4fv(viewProjectionMatrixUniform, false, viewProjectionMatrix.get(viewProjectionMatrixBuffer));
			return true;
		}
		return false;
	}
	
	
	/***
	 * 
	 * @param modelColor
	 * @return True if the modelColorUniform "uColor" has been found.
	 */
	public boolean setModelColorUniform(Vector3f modelColor) {
		return setModelColorUniform(modelColor.x, modelColor.y, modelColor.z);
	}
	
	public boolean setModelColorUniform(Color color) {
		return setModelColorUniform(color.r, color.g, color.b);
	}

	/***
	 * 
	 * @param modelColor
	 * @return True if the modelColorUniform "uColor" has been found.
	 */
	public boolean setModelColorUniform(float r, float g, float b) {
		if(modelColorUniform >= 0) {
			glUniform3f(modelColorUniform, r,g,b);
			return true;
		}
		return false;
	}

	public void bind() {
		glUseProgram(programIndex);
	}

	@Override
	public void glCleanup() {
		glDeleteShader(vertexShader.getId());
		glDeleteShader(fragmentShader.getId());
		
		glDeleteProgram(programIndex);
		System.out.println("Cleaned up Shader: " + this.name);
	}

}
